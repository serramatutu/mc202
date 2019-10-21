/** Lucas Valente Viegas de Oliveira Paes
 * MC202 Turma E
 * Lab 07
*/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "arvore.h"

#define TOKEN_MAX_SIZE 30
#define OPERATORS "+-/*()"

typedef enum TokenType {
    NUMBER, OPERATOR, VARIABLE
} TokenType;

typedef union TokenValue {
    int number;
    char operator;
    char variable;
} TokenValue;

typedef struct Token {
    TokenType type;
    TokenValue value;
} Token;

Tree * parseExpression(const char * expr);

void printExpression(Tree * tree);

#endif