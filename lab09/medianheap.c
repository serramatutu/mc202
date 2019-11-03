#include <stdlib.h>
#include "heap.h"

#include "medianheap.h"

static char lt(size_t a, size_t b) {
    return b > a;
}

static void balance(MedianHeap * heap) {
    Heap * remove = heap->upper;
    Heap * insert = heap->lower;
    if (insert->size >= remove->size + 1) {
        remove = heap->lower;
        insert = heap->upper;
    }
    
    if (remove->size - insert->size <= 1) {
        return;
    }

    const HeapValue * val = heapPeek(remove);
    heapInsert(insert, val->key, val->value);
    heapPop(remove, 0);
}

MedianHeap * mHeapNew(size_t capacity, size_t dataSize, FreeFn freeFn) {
    MedianHeap * heap = malloc(sizeof(MedianHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->upper = heapNew(capacity/2 + 1, &lt, dataSize, freeFn);
    if (heap->upper == NULL) {
        free(heap);
        return NULL;
    }
    heap->lower = heapNew(capacity/2 + 1, NULL, dataSize, freeFn);
    if (heap->lower == NULL) {
        free(heap->upper);
        free(heap);
        return NULL;
    }

    return heap;
}

void mHeapFree(MedianHeap * heap) {
    heapFree(heap->upper);
    heapFree(heap->lower);
    free(heap);
}

void mHeapInsert(MedianHeap * heap, size_t key, void * value) {
    const HeapValue * upperValue = heapPeek(heap->upper);

    if (upperValue != NULL && key > upperValue->key) {
        heapInsert(heap->upper, key, value);
    }
    else {
        heapInsert(heap->lower, key, value);
    }

    balance(heap);
}

Median mHeapPeek(MedianHeap * heap) {
    Median m = {
        .present = 0,
    };
    if (heap->lower->size == 0 && heap->upper->size == 0) {
        return m;
    }

    m.present = 1;
    m.first = heapPeek(heap->lower);

    if (heap->upper->size > heap->lower->size) {
        m.first = heapPeek(heap->upper);
    }
    else if (heap->lower->size == heap->upper->size) {
        m.present = 2;
        m.second = heapPeek(heap->upper);
    }
    
    return m;
}

void mHeapPop(MedianHeap * heap);