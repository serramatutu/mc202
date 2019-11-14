#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>

#define HASH_COPRIME_FACTOR 3

typedef size_t (*HashFunction)(const void * data, size_t bytes, size_t max);

typedef void (*FreeFunction)(void *);

typedef char (*EqualsFunction)(const void * a, size_t aBytes, const void * b, size_t bBytes);

typedef struct HashData {
    void * key;
    size_t keyBytes;

    void * value;
} HashData;

typedef struct Hashmap {
    FreeFunction freeFn;
    size_t dataSize;

    HashFunction hashFn;
    EqualsFunction equalsFn;

    size_t capacity;
    HashData * data;

    size_t size;
} Hashmap;

Hashmap * hashmapNew(size_t capacity, HashFunction hashFn, EqualsFunction equalsFn, size_t dataSize, FreeFunction freeFn);

void hashmapFree(Hashmap * hm);

char hashmapInsert(Hashmap * hm, void * key, size_t keyBytes, void * value);

void * hashmapFind(Hashmap * hm, void * key, size_t keyBytes);

char hashmapRemove(Hashmap *hm, void * key, size_t keyBytes);

#endif