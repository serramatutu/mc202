#ifndef ARVORE_H
#define ARVORE_H

#include <stdlib.h>

#include "pilha.h"

typedef struct TreeNode TreeNode;
typedef void (*FreeFunction)(void *);
typedef void (*PrintFunction)(const void*);

struct TreeNode {
    char hasData;

    size_t key;
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

TreeNode * treeNewNode(Tree * tree, size_t key, void * data);

void treeFreeNode(Tree * tree, TreeNode * node);

void copyDataToNode(Tree * tree, TreeNode * node, void * data);

char isLeaf(TreeNode * node);

void treeNodePrintInOrder(TreeNode * node, PrintFunction printer, char spacing);

void treePrintInOrder(Tree * tree, PrintFunction printer, char spacing);

char treeInsert(Tree * tree, size_t key, void * data);

char treeEmpty(const Tree * tree);

// Iterators

typedef struct TreeIterator {
    Tree * tree;

    Stack * stack;
} TreeIterator;

TreeIterator treeItBegin(Tree * tree);

char treeItEnd(TreeIterator it);

TreeNode * treeItCurrent(TreeIterator it);

char treeItNext(TreeIterator it);

#endif