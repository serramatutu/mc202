#define LAB11

#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

// TODO: remove dis
static void printAdjacencies(Graph * g) {
    for (size_t floor = 0; floor < g->size; floor++) {
        List * out = graphGetOutboundEdges(g, floor);
        printf("%lu: ", floor);
        
        for (ListIterator it = listBegin(out); !it.end; it = listNext(it)) {
            GraphEdge edge = *((GraphEdge*)it.current->data);
            printf("%lu ", edge.destination);
        }

        printf("\n");
    }
}

int main() {
    size_t m;
    scanf("%lu", &m);

    for (size_t i = 0; i < m; i++) {
        size_t floors;
        scanf("%lu", &floors);

        Graph * g = graphNew(floors);

        for (size_t floor = 0; floor < floors; floor++) {
            size_t downA, upA, downB, upB;
            scanf("%lu %lu %lu %lu", &downA, &upA, &downB, &upB);

            // insere na ordem reversa de prioridade, pois o grafo 
            // insere no começo das listas de adjacência
            graphAddEdge(g, floor, floor + upB);
            graphAddEdge(g, floor, floor - downB);
            graphAddEdge(g, floor, floor +upA);
            graphAddEdge(g, floor, floor - downA);
        }

        graphFree(g);
    }
}