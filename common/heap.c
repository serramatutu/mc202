#include "heap.h"

#include <stdlib.h>
#include <string.h>

#define PARENT(index) ((index - 1) / 2)
#define LEFT(index) (index * 2 + 1)
#define RIGHT(index) (index * 2 + 2)

static char gt(size_t a, size_t b) {
    return a > b;
}

static void swap(HeapValue * a, HeapValue * b) {
    HeapValue t = *a;
    *a = *b;
    *b = t;
};

static size_t largestChild(Heap * heap, size_t index) {
    size_t left = LEFT(index), 
        right = RIGHT(index);
    if (left >= heap->size) {
        return index;
    }

    if (right < heap->size && heap->greaterThan(heap->values[right].key, heap->values[left].key)) {
        return right;
    }
    return left;
}

static void ascend(Heap * heap, size_t index) {
    while (index > 0 && heap->greaterThan(heap->values[index].key, heap->values[PARENT(index)].key)) {
        swap(heap->values + index, heap->values + PARENT(index));
        index = PARENT(index);
    }
}

static void descend(Heap * heap, size_t index) {
    while (index < heap->size) {
        size_t largest = largestChild(heap, index);
        if (largest <= index || heap->greaterThan(heap->values[index].key, heap->values[largest].key)) {
            break;
        }

        swap(heap->values + index, heap->values + largest);
        index = largest;
    }
}

Heap * heapNew(size_t capacity, GreaterThan greaterThan, size_t dataSize, FreeFn freeFn) {
    Heap * heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }

    heap->values = malloc(sizeof(HeapValue) * capacity);
    if (heap->values == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;

    heap->dataSize = dataSize;
    heap->freeFn = freeFn;

    if (greaterThan == NULL) {
        heap->greaterThan = &gt;
    }
    else {
        heap->greaterThan = greaterThan;
    }

    return heap;
}

void heapFree(Heap * heap) {
    while (heap->size > 0) {
        heapPop(heap, 1);
    }
    free(heap->values);
    free(heap);
}

void heapInsert(Heap * heap, size_t key, void * value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->values = realloc(heap->values, sizeof(HeapValue) * heap->capacity);
        if (heap->values == NULL) {
            exit(1);
        }
    }

    HeapValue * val = heap->values + heap->size;
    heap->size++;

    val->value = malloc(heap->dataSize);
    if (val->value == NULL) {
        exit(1);
    }
    memcpy(val->value, value, heap->dataSize);

    val->key = key;

    ascend(heap, heap->size - 1);
}

const HeapValue * heapPeek(Heap * heap) {
    if (heap->size == 0) {
        return NULL;
    }

    return heap->values;
}

void heapPop(Heap * heap, char shouldFree) {
    if (heap->size == 0) {
        return;
    }

    if (shouldFree && heap->freeFn != NULL) {
        heap->freeFn(heap->values[0].value);
    }
    free(heap->values[0].value);

    heap->size--;

    if (heap->size >= 1) {
        heap->values[0] = heap->values[heap->size];
        descend(heap, 0);
    }
}