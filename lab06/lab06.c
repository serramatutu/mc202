/* 
Lucas Valente Viegas de Oliveira PAes
RA 220958
MC 202 E
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pilha.h"

/*
OBSERVAÇÕES GERAIS:
1. Fiz uma pilha genérica com void * para reutilizá-la em outros labs.
2. Utilizei '%ms' para leitura de string de tamanho arbitrário e li a documentação
para garantir que não hajam memory leaks.
*/

size_t _top(Stack * s) {
    return *(size_t*)stackTop(s);
}

int greatestPossibleValue(char * sequence, size_t digits) {
    size_t len = strlen(sequence);
    Stack * included = stackNew(sizeof(size_t), NULL);
    if (included == NULL) {
        return 0;
    }

    size_t idx, removed;    
    for (idx = 0, removed = 0; idx < len && removed < digits; idx++) {
        // vamos removendo da pilha de incluídos enquanto os incluídos anteriormente (de maior ordem)
        // são menores que o atual
        while (included->size >0 && sequence[_top(included)] < sequence[idx] && removed < digits) {
            stackPop(included);
            removed++;
        }
        
        if (!stackPush(included, &idx)) {
            stackFree(included);
            return 0;
        }
    }

    char * newSequence = malloc(sizeof(char) * len + 1);
    if (newSequence == NULL) {
        return 0;
    }

    strcpy(newSequence + included->size, sequence + included->size + removed);
    // quando chegar em 0 o size_t dá a volta e o índice explode. o loop decrescente funciona :)
    for (idx = included->size - 1; idx <= included->size; idx--) {
        newSequence[idx] = sequence[_top(included)];
        stackPop(included);
    }
    // corta o resto da sequência caso o restante dos removidos esteja ao final
    newSequence[len - digits] = '\0';
    strcpy(sequence, newSequence);

    free(newSequence);
    stackFree(included);

    return 1;
}

int main() {
    size_t sequences;
    scanf("%lu", &sequences);
    
    for (size_t i=0; i<sequences; i++) {
        char * sequence; 
        size_t digits;
        
        // %ms para ler uma string de tamanho arbitrário, já fazendo a alocação por você.
        // nós continuamos responsáveis pelo free, como diz a documentação.
        // https://stackoverflow.com/questions/38685724/difference-between-ms-and-s-scanf
        scanf(" %ms %lu", &sequence, &digits);
        if (!greatestPossibleValue(sequence, digits)) {
            return EXIT_FAILURE;
        }
        printf("%s\n", sequence);

        free(sequence);
    }

    return EXIT_SUCCESS;
}