#include "hash.h"

static size_t stdHashFunction(const void * data, size_t bytes, size_t max) {
    const unsigned char * charData = (const unsigned char *)data;
    size_t hash = charData[0];
    for (size_t i = 1; i < bytes; i++) {
        hash = (hash * 256 + charData[i]) % max;
    }
    return hash;
};

static char stdEqualsFunction(const void * a, size_t aBytes, const void * b, size_t bBytes) {
    if (aBytes != bBytes) {
        return 0;
    }
    return memcmp(a, b, aBytes);
}

static size_t jumpHash(Hashmap * hm, void * data, size_t bytes) {
    return (hm->hashFn(data, bytes, hm->capacity) * HASH_COPRIME_FACTOR) % hm->capacity;
}

Hashmap * hashmapNew(size_t capacity, HashFunction hashFn, EqualsFunction equalsFn, size_t dataSize, FreeFunction freeFn) {
    Hashmap * hm = malloc(sizeof(Hashmap));
    if (hm == NULL) {
        return NULL;
    }

    // garante que a capacidade é sempre co-primo de HASH_COPRIME_FACTOR
    capacity = (capacity / HASH_COPRIME_FACTOR + 1) * HASH_COPRIME_FACTOR + 1;
    hm->data = malloc(capacity * sizeof(HashData));
    if (hm->data == NULL) {
        free(hm);
        return NULL;
    }

    hm->dataSize = dataSize;
    hm->capacity = capacity;
    hm->size = 0;

    hm->freeFn = freeFn;
    if (hashFn == NULL) {
        hashFn = &stdHashFunction;
    }
    hm->hashFn = hashFn;

    if (equalsFn == NULL) {
        equalsFn = stdEqualsFunction;
    }
    hm->equalsFn = equalsFn;

    return hm;
}

void hashmapFree(Hashmap * hm) {
    for (size_t i = 0; i < hm->size; i++) {
        if (hm->freeFn != NULL) {
            hm->freeFn(hm->data[i].key);
        }
        free(hm->data[i].key);
    }
    free(hm->data);

    free(hm);
}

static char empty(Hashmap * hm, size_t pos) {
    return hm->data[pos].key == NULL;
}

static char equals(Hashmap * hm, size_t pos, void * key, size_t keyBytes) {
    return hm->equalsFn(key, keyBytes, hm->data[pos].key, hm->data[pos].keyBytes);
}

static char isElement(Hashmap * hm, HashData * hd, void * key, size_t keyBytes) {
    return hd->key != NULL && hm->equalsFn(key, keyBytes, hd->key, hd->keyBytes);
}

static HashData * find(Hashmap * hm, void * key, size_t keyBytes) {
    size_t hash = hm->hashFn(key, keyBytes, hm->capacity);
    size_t jump = jumpHash(hm, key, keyBytes);

    size_t i = 0;
    while (i < hm->capacity && !empty(hm, hash + i * jump) && equals(hm, hash + i * jump, key, keyBytes)) {
        i++;
    }

    size_t pos = hash + i * jump;

    return hm->data + pos;
}

char hashmapInsert(Hashmap * hm, void * key, size_t keyBytes, void * value) {
    HashData * hd = find(hm, key, keyBytes);

    if (isElement(hm, hd, key, keyBytes)) {
        return 0;
    }
    
    hd->key = malloc(keyBytes);
    if (hd->key == NULL) {
        return 0;
    }
    memcpy(hd->key, key, keyBytes);
    hd->keyBytes = keyBytes;

    hd->value = malloc(hm->dataSize);
    if (hd->value == NULL) {
        free(hd->key);
        return 0;
    }
    memcpy(hd->value, value, hm->dataSize);

    hm->size++;

    return 1;
}

void * hashmapFind(Hashmap * hm, void * key, size_t keyBytes) {
    HashData * hd = find(hm, key, keyBytes);

    if (!isElement(hm, hd, key, keyBytes)) {
        return NULL;
    }

    return hd->value;
}

char hashmapRemove(Hashmap *hm, void * key, size_t keyBytes) {
    HashData * hd = find(hm, key, keyBytes);

    if (!isElement(hd, key, keyBytes)) {
        return 0;
    }

    if (hm->freeFn != NULL) {
        hm->freeFn(hd->value);
    }
    free(hd->value);
    free(hd->key);

    hd->key = NULL;
    hd->value = NULL;
    hd->keyBytes = 0;

    return 1;
}