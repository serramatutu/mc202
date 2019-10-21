/** Lucas Valente Viegas de Oliveira Paes
 * MC202 Turma E
 * Lab 07
*/

#include <stdlib.h>
#include <stdio.h>

#include "expression.h"
#include "arvore.h"

#define BUF_SIZE 2000

int main() {
    int m;
    scanf("%d ", &m);

    char * buf = malloc(sizeof(char) * BUF_SIZE);

    for (int i = 0; i < m; i++) {
        fgets(buf, BUF_SIZE, stdin);

        Tree * tree = parseExpression(buf);
        if (tree == NULL) {
            return EXIT_FAILURE;
        }

        printExpression(tree);
        printf(" \n");

        treeFree(tree);
    }

    free(buf);

    return EXIT_SUCCESS;
}