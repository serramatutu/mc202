/*
Lucas Valente Viegas de Oliveira Paes
RA 220958
LAB 10 - MC202 Turma E
*/

#define LAB10

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

char find(size_t * vec, size_t vecSize, size_t elem) {
    for (size_t i = 0; i < vecSize; i++) {
        if (vec[i] == elem) {
            return 1;
        }
    }
    return 0;
}

int main() {
    size_t n;
    scanf("%lu", &n);

    size_t * occurrences = calloc(n, sizeof(size_t));

    Hashmap * tokenPositionMap = hashmapNew(2 * n, NULL, NULL, sizeof(size_t), NULL, NULL);
    
    size_t nTokenSizes = 0;
    size_t * tokenSizes = malloc(sizeof(size_t) * n);

    for (size_t i = 0; i < n; i++) {
        char * buf;
        scanf("%ms", &buf);
        size_t len = strlen(buf);

        if (!find(tokenSizes, nTokenSizes, len)) {
            tokenSizes[nTokenSizes] = len;
            nTokenSizes++;
        }

        hashmapInsert(tokenPositionMap, buf, len, &i);
        free(buf);
    }

    char * text;
    scanf("%ms", &text);
    size_t textLen = strlen(text);

    for (size_t t = 0; t < nTokenSizes; t++) {
        for (size_t i = 0; i < textLen - tokenSizes[t] + 1; i++) {
            void * data = hashmapFind(tokenPositionMap, text + i, tokenSizes[t]);
            if (data != NULL) {
                occurrences[*((size_t *)data)]++;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        printf("%lu\n", occurrences[i]);
    }

    hashmapFree(tokenPositionMap);
    free(tokenSizes);
    free(occurrences);
    free(text);
}