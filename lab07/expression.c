/** Lucas Valente Viegas de Oliveira Paes
 * MC202 Turma E
 * Lab 07
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arvore.h"

#include "expression.h"

static int _doOperation(char operation, int a, int b) {
    if (operation == '*') 
        return a * b;  
    if (operation == '/') {
        if (b == 0) {
            exit(1);
        }
        return a / b;
    } 
    if (operation == '+') {
        return a + b;
    }
    return a - b;
}

static Token _parseToken(const char * str) {
    Token token;

    if (strlen(str) == 1 && strchr(OPERATORS, str[0]) != NULL) {
        token.type = OPERATOR;
        token.value.operator = str[0];
    }
    else {
        if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-') {
            token.type = NUMBER;
            sscanf(str, "%d", &token.value.number);
        }
        else {
            token.type = VARIABLE;
            sscanf(str, "%c", &token.value.variable);
        }
    }
    
    return token;
}

static const char * _readToken(Token * token, const char * expr) {
    char strToken[TOKEN_MAX_SIZE];
    sscanf(expr, " %s", strToken);

    *token = _parseToken(strToken);

    return expr + strlen(strToken) + 1;
}

#define _getData(node) (*(Token*)(node->data))

static TreeNode * _parseExpressionNodes(Tree * tree, const char ** expr) {
    TreeNode * node = treeNewNode(tree, 0, NULL);
    if (node == NULL) {
        return NULL;
    }

    Token token;
    *expr = _readToken(&token, *expr);

    if (token.type != OPERATOR) {
        copyDataToNode(tree, node, &token);
        return node;
    }

    // operando esquerdo
    node->left = _parseExpressionNodes(tree, expr);

    // operador
    *expr = _readToken(&token, *expr);
    copyDataToNode(tree, node, &token);

    // operando direito
    node->right = _parseExpressionNodes(tree, expr);

    // parênteses restante
    *expr = _readToken(&token, *expr);

    // simplifica se possível
    if (_getData(node->left).type == NUMBER && _getData(node->right).type == NUMBER) {
        Token simplified = {
            .type = NUMBER,
            .value.number = _doOperation(
                _getData(node).value.operator, 
                _getData(node->left).value.number,
                _getData(node->right).value.number
            )
        };
        copyDataToNode(tree, node, &simplified);

        treeFreeNode(tree, node->left);
        treeFreeNode(tree, node->right);
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

Tree * parseExpression(const char * expr) {
    Tree * tree = treeNew(sizeof(char*), NULL);
    if (tree == NULL) {
        return NULL;
    }

    tree->root = _parseExpressionNodes(tree, &expr);

    return tree;
}

static void _printExpressionData(const void * data) {
    Token * token = (Token *)data;

    if (token->type == NUMBER) {
        printf("%d", token->value.number);
    }
    else {
        printf("%c", token->value.operator);
    }
}

void printExpression(Tree * tree) {
    treePrintInOrder(tree, _printExpressionData, 1);
}