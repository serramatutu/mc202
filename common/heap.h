#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef char (*GreaterThan)(size_t a, size_t b);

typedef struct HeapValue {
    size_t key;
    void * value;
} HeapValue;

typedef void (*FreeFn)(void*);

typedef struct Heap {
    FreeFn freeFn;
    size_t dataSize;

    GreaterThan greaterThan;
    size_t capacity;

    size_t size;
    HeapValue * values;
} Heap;

Heap * heapNew(size_t capacity, GreaterThan greaterThan, size_t dataSize, FreeFn freeFn);

void heapFree(Heap * heap);

void heapInsert(Heap * heap, size_t key, void * value);

const HeapValue * heapPeek(Heap * heap);

void heapPop(Heap * heap, char shouldFree);

#endif