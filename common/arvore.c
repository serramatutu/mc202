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

TreeNode * treeNewNode(Tree * tree, size_t key, void * data) {
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

    node->key = key;

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

void treeNodePrintInOrder(TreeNode * node, PrintFunction printer, char spacing) {
    if (node == NULL) {
        return;
    }
    
    if (spacing && !isLeaf(node)) {
        printf("( ");
    }

    treeNodePrintInOrder(node->left, printer, spacing);
    if (spacing && node->left != NULL) {
        printf(" ");
    }
    printer(node->data);
    if (spacing && node->right != NULL) {
        printf(" ");
    }

    treeNodePrintInOrder(node->right, printer, spacing);

    if (spacing && !isLeaf(node)) {
        printf(" )");
    }
}

void treePrintInOrder(Tree * tree, PrintFunction printer, char spacing) {
    treeNodePrintInOrder(tree->root, printer, spacing);
}

static char _nodeInsert(Tree * tree, TreeNode ** root, TreeNode * node) {
    while (*root != NULL) {
        if ((*root)->key == node->key) {
            return 0;
        }

        TreeNode ** next = &(*root)->left;        
        if (node->key > (*root)->key) {
            next = &(*root)->right;
        }

        root = next;
    }

    *root = node;
    return 1;
}

char treeInsert(Tree * tree, size_t key, void * data) {
    TreeNode * node = treeNewNode(tree, key, data);
    if (node == NULL) {
        return 0;
    }

    char result = _nodeInsert(tree, &tree->root, node);
    if (!result) {
        treeFreeNode(tree, node);
        // free(node);
    }
    return result;
}

char treeEmpty(const Tree * tree) {
    return tree->root == NULL;
}

TreeIterator treeItBegin(Tree * tree) {
    TreeIterator it = {
        .tree = tree,
        .stack = stackNew(sizeof(TreeNode *), NULL)
    };

    TreeNode * current = tree->root;
    while (current != NULL) {
        stackPush(it.stack, &current);
        current = current->left;
    }
    
    return it;
}

char treeItEnd(TreeIterator it) {
    if (it.stack->size > 0) {
        return 0;
    }

    stackFree(it.stack);
    return 1;
}

TreeNode * treeItCurrent(TreeIterator it) {
    return (TreeNode *)stackTop(it.stack);
}

char treeItNext(TreeIterator it) {
    if (it.stack->size == 0) {
        return 0;
    }

    TreeNode * current = treeItCurrent(it);
    if (current->right != NULL) {
        
    }

    return 1;
}