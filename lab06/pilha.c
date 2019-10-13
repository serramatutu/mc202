/* 
Lucas Valente Viegas de Oliveira PAes
RA 220958
MC 202 E
*/

#include <stdlib.h>
#include <string.h>

#include "pilha.h"

void stackPop(Stack * s) {
    if (s->top == NULL)
        return;

    if (s->freeFn != NULL) {
        s->freeFn(s->top->data);
    }
    free(s->top->data);

    StackNode * next = s->top->next;
    free(s->top);
    s->top = next;
    s->size--;
}

StackNode * stackPush(Stack * s, void * data) {
    StackNode * newNode = malloc(sizeof(StackNode));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->data = malloc(s->dataSize);
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    memcpy(newNode->data, data, s->dataSize);
    newNode->next = s->top;
    s->top = newNode;
    s->size++;

    return newNode;
}

Stack * stackNew(unsigned int dataSize, FreeFunction freeFn) {
    Stack * s = malloc(sizeof(Stack));
    if (s == NULL) {
        return NULL;
    }
    s->dataSize = dataSize;
    s->freeFn = freeFn;
    s->top = NULL;
    s->size = 0;

    return s;
}

void stackFree(Stack * s) {
    while (s->top != NULL) {
        stackPop(s);
    }
    free(s);
}
