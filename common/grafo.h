#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>

#include "lista.h"

typedef struct GraphEdge {
    size_t weight;
    size_t destination;
    size_t source;
} GraphEdge;

typedef struct Graph {
    size_t size;

    List ** inbound;
    List ** outbound;
} Graph;

Graph * graphNew(size_t size);

void graphFree(Graph * graph);

void graphAddEdge(Graph * graph, size_t source, size_t dest, size_t weight);

List * graphGetOutboundEdges(Graph * graph, size_t node);

List * graphGetInboundEdges(Graph * graph, size_t node);

List * graphBreadthFirstSearch(Graph * graph, size_t start, size_t end);

#endif