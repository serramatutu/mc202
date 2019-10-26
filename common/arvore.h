/** Lucas Valente Viegas de Oliveira Paes
 * MC202 Turma E
 * Lab 07
*/

#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef void (*FreeFunction)(void *);
typedef void (*PrintFunction)(const void*);

struct TreeNode {
    char hasData;
    void * data;

    TreeNode * right;
    TreeNode * left;
};

typedef struct Tree {
    size_t dataSize;
    FreeFunction freeFn;

    TreeNode * root;
} Tree;

Tree * treeNew(size_t dataSize, FreeFunction freeFn);

void treeFree(Tree * tree);

TreeNode * treeNewNode(Tree * tree, void * data);

void treeFreeNode(Tree * tree, TreeNode * node);

void copyDataToNode(Tree * tree, TreeNode * node, void * data);

char isLeaf(TreeNode * node);

void treeNodePrintInOrder(TreeNode * node, PrintFunction printer);

void treePrintInOrder(Tree * tree, PrintFunction printer);

#endif