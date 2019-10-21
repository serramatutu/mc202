/** Lucas Valente Viegas de Oliveira Paes
 * MC202 Turma E
 * Lab 07
*/

#include "arvore.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Tree * treeNew(size_t dataSize, FreeFunction freeFn) {
    Tree * tree = malloc(sizeof(Tree));
    if (tree == NULL) {
        return NULL;
    }

    tree->dataSize = dataSize;
    tree->freeFn = freeFn;
    tree->root = NULL;

    return tree;
}

void treeFree(Tree * tree) {
    treeFreeNode(tree, tree->root);
    free(tree);
}

void copyDataToNode(Tree * tree, TreeNode * node, void * data) {
    if (node->hasData && tree->freeFn != NULL) {
        tree->freeFn(node->data);
    }

    if (data != NULL) {
        node->hasData = 1;
        memcpy(node->data, data, tree->dataSize);
    }
    else {
        node->hasData = 0;
    }
}

TreeNode * treeNewNode(Tree * tree, void * data) {
    TreeNode * node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(tree->dataSize);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }

    node->hasData = 0;
    copyDataToNode(tree, node, data);

    node->right = NULL;
    node->left = NULL;

    return node;
}

void treeFreeNode(Tree * tree, TreeNode * node) {
    if (node == NULL) {
        return;
    }

    if (node->hasData && tree->freeFn != NULL) {
        tree->freeFn(node->data);
    }
    free(node->data);

    treeFreeNode(tree, node->right);
    treeFreeNode(tree, node->left);
    free(node);
}

char isLeaf(TreeNode * node) {
    return node->left == NULL && node->right == NULL;
}

void treeNodePrintInOrder(TreeNode * node, PrintFunction printer) {
    if (node == NULL) {
        return;
    }
    
    if (!isLeaf(node)) {
        printf("( ");
    }

    treeNodePrintInOrder(node->left, printer);
    if (node->left != NULL) {
        printf(" ");
    }
    printer(node->data);
    if (node->right != NULL) {
        printf(" ");
    }

    treeNodePrintInOrder(node->right, printer);

    if (!isLeaf(node)) {
        printf(" )");
    }
}

void treePrintInOrder(Tree * tree, PrintFunction printer) {
    treeNodePrintInOrder(tree->root, printer);
}