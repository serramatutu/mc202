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
    return memcmp(a, b, aBytes) == 0;
}

Hashmap * hashmapNew(size_t capacity, HashFunction hashFn, EqualsFunction equalsFn, size_t dataSize, FreeFunction freeKeyFn, FreeFunction freeValueFn) {
    Hashmap * hm = malloc(sizeof(Hashmap));
    if (hm == NULL) {
        return NULL;
    }

    hm->data = calloc(capacity, sizeof(HashData));
    if (hm->data == NULL) {
        free(hm);
        return NULL;
    }

    hm->dataSize = dataSize;
    hm->capacity = capacity;
    hm->size = 0;

    hm->freeKeyFn = freeKeyFn;
    hm->freeValueFn = freeValueFn;
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

static void hashdataClear(Hashmap * hm, HashData * hd) {
    if (hm->freeKeyFn != NULL) {
        hm->freeKeyFn(hd->key);
    }
    free(hd->key);

    if (hm->freeValueFn != NULL) {
        hm->freeValueFn(hd->value);
    }
    free(hd->value);

    hd->key = NULL;
    hd->value = NULL;
    hd->keyBytes = 0;
}

void hashmapFree(Hashmap * hm) {
    for (size_t i = 0; i < hm->capacity; i++) {
        HashData * hd = hm->data + i;
        if (hd->key != NULL) {
            hashdataClear(hm, hd);
        }
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
    size_t jump = hm->capacity + 1; // n e n+1 são sempre coprimos

    size_t i = 0, pos = hash % hm->capacity;
    while (i < hm->capacity && !empty(hm, pos) && !equals(hm, pos, key, keyBytes)) {
        i++;
        pos = (hash + i * jump) % hm->capacity;
    }

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

    if (!isElement(hm, hd, key, keyBytes)) {
        return 0;
    }

    hashdataClear(hm, hd);

    return 1;
}