#include "hash.h"

static size_t stdHashFunction(const void * data, size_t bytes, size_t max) {
    const unsigned char * charData = (const unsigned char *)data;
    size_t hash = charData[0];
    for (size_t i = 1; i < bytes; i++) {
        hash = (hash * 256 + charData[i]) % max;
    }
    return hash;
};

Hashmap * hashmapNew(size_t capacity, HashFunction hashFn, size_t dataSize, FreeFunction freeFn) {
    Hashmap * hm = malloc(sizeof(Hashmap));
    if (hm == NULL) {
        return NULL;
    }

    hm->data = malloc(capacity * dataSize);
    if (hm->data == NULL) {
        free(hm);
        return NULL;
    }

    hm->capacity = capacity;
    hm->size = 0;

    hm->freeFn = freeFn;
    if (hashFn == NULL) {
        hashFn = &stdHashFunction;
    }
    hm->hashFn = hashFn;

    return hm;
}

void hashmapFree(Hashmap * hm) {
    for (size_t i = 0; i < hm->size; i++) {
        if (hm->freeFn != NULL) {
            hm->freeFn(hm->data[i]);
        }
        free(hm->data[i]);
    }
    free(hm->data);

    free(hm);
}