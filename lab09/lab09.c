/**
 * Lucas Valente Viegas de Oliveira Paes
 * RA 220958
 * MC202 E - LAB09
*/

#define LAB_09

#include <stdio.h>

#include "medianheap.h"

#define NAME_SIZE 5

#define STRING_TO_KEY_BASE (('Z' - 'A' + 1) + ('9' - '0' + 1))

/**
 * Converte um identificador de caixa em um inteiro, usando-o
 * como um número em base 0-Z 
*/
static size_t stringToKey(const char * str) {
    return (size_t)strtoll(str, NULL, STRING_TO_KEY_BASE);
}

static void printMedian(size_t group, MedianHeap * heap) {
    Median median = mHeapPeek(heap);
    
    if (median.present == 1) {
        printf("%lu %s\n", group + 1, (char *)median.first->value);
    }
    else if (median.present == 2) {
        printf("%lu %s %s\n", group + 1, (char *)median.first->value, (char *)median.second->value);
    }
}

int main() {
    size_t groups;
    scanf("%lu", &groups);

    for (size_t group = 0; group < groups; group++) {
        size_t boxes;
        scanf(" %lu\n", &boxes);

        MedianHeap * heap = mHeapNew(boxes, sizeof(char *), NULL);
        if (heap == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t box = 0; box < boxes; box++) {
            if (box % 5 == 0) {
                printMedian(group, heap);
            }

            char boxName[NAME_SIZE];

            fgets(boxName, NAME_SIZE, stdin);
            scanf("\n");

            size_t boxKey = stringToKey(boxName);
            mHeapInsert(heap, boxKey, boxName);
        }

        printMedian(group, heap);

        mHeapFree(heap);
    }

    return EXIT_SUCCESS;
}