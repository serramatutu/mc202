#ifndef PILHA_H
#define PILHA_H

typedef struct StackNode {
    void* data;
    void* next;
} StackNode;

typedef void (*FreeFunction)(void*);

typedef struct Stack {
    size_t dataSize;
    size_t size;
    FreeFunction freeFn;

    StackNode * top;
} Stack;

void * stackTop(Stack * s);

void stackPop(Stack * s);

StackNode * stackPush(Stack * s, void * data);

Stack * stackNew(unsigned int dataSize, FreeFunction freeFn);

void stackFree(Stack * s);

#endif