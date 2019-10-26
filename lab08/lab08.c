/** Lucas Valente Viegas de Oliveira Paes
 * RA 220958
 * MC202 E
 * Lab 02
*/

#include <stdlib.h>
#include <stdio.h>

#include "packet.h"

/** Observação:
 * reutilizei a árvore que fiz no Lab 07 para este lab. Por isso, alguns métodos
 * podem estar "sobrando" e não foram utilizados.
*/

int main() {
    Tree * packets = readPackets(stdin);
    packetsPrint(packets);
    printf("\n");
    treeFree(packets);

    return EXIT_SUCCESS;
}