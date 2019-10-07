/*
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#include <stdlib.h>
#include <stdio.h>

#include "memorymanager.h"

#define BUF_SIZE 50

/* 
Observação:
Fiz uma lista genérica com void * para usá-la de novo em futuros labs
e só for fun pra aprender mais sobre C. Espero que não tenha problema ter feito assim :)
*/
int main() {
    unsigned int ops;
    mm_size memorySize;
    scanf("%u %u", &ops, &memorySize);

    MemoryManager * mm = mmNew(memorySize);
    if (mm == NULL) {
        return EXIT_FAILURE;
    }

    for (unsigned int i=0; i<ops; i++) {
        char op;
        char params[BUF_SIZE];

        scanf(" %c", &op);
        if (op != MM_PRINT) {
            scanf(" %[^\n]s", params);
        }
        if (!mmDoOperation(mm, op, params)) {
            return EXIT_FAILURE;
        }
    }

    mmFree(mm);

    return EXIT_SUCCESS;
}