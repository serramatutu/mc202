#ifndef HASH_H
#define HASH_H

#include <stdlib.h>

typedef size_t (*HashFunction)(void *, size_t, size_t);

typedef void (*FreeFunction)(void *);

typedef struct Hashmap {
    size_t dataSize;
    FreeFunction freeFn;

    HashFunction hashFn;

    size_t capacity;
    void ** data;

    size_t size;
} Hashmap;

Hashmap * hashmapNew(size_t capacity, HashFunction hashFn, size_t dataSize, FreeFunction freeFn);

void hashmapFree(Hashmap * hm);

#endif