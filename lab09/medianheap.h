#ifndef MEDIAN_HEAP_H
#define MEDIAN_HEAP_H

#include "heap.h"

typedef struct Median {
    unsigned char present;

    const HeapValue * first;
    const HeapValue * second;
} Median;

typedef struct MedianHeap {
    Heap * upper;
    Heap * lower;
} MedianHeap;

MedianHeap * mHeapNew(size_t capacity, size_t dataSize, FreeFn freeFn);

void mHeapFree(MedianHeap * heap);

void mHeapInsert(MedianHeap * heap, size_t key, void * value);

Median mHeapPeek(MedianHeap * heap);

void mHeapPop(MedianHeap * heap);

#endif