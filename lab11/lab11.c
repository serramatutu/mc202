#define LAB11

#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

void printer(GraphEdge edge) {
    char choice = edge.weight;
    char elevator = choice == 'X' || choice == 'Y' ? 'A' : 'B';

    printf("%c %c\n", elevator, choice);
}

int main() {
    size_t m;
    scanf("%lu", &m);

    for (size_t i = 0; i < m; i++) {
        size_t floors;
        scanf("%lu", &floors);

        Graph * g = graphNew(2 * (floors + 1));

        for (size_t floor = floors; floor > 0; floor--) {
            size_t downA, upA, downB, upB;
            scanf("%lu %lu %lu %lu", &downA, &upA, &downB, &upB);

            graphAddEdge(g, floor, floor - downA, 'X');
            graphAddEdge(g, floor, floor + upA, 'Y');
            graphAddEdge(g, floor, floor - downB, 'W');
            graphAddEdge(g, floor, floor + upB, 'Z');
        }

        GraphEdge * path = graphBreadthFirstSearch(g, floors, 0);
        adjustPathPriority(g, path, floors);

        printf("Cenário #%lu\n", i);
        graphPrintPath(path, &printer, floors, 0);
        
        free(path);
        graphFree(g);
    }
}