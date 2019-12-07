

#include "grafo.h"

Graph * graphNew(size_t size) {
    Graph * graph = malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->inbound = malloc(sizeof(List *) * size);
    if (graph->inbound == NULL) {
        free(graph);
        return NULL;
    }

    graph->outbound = malloc(sizeof(List *) * size);
    if (graph->outbound == NULL) {
        free(graph->inbound);
        free(graph);
        return NULL;
    }

    graph->size = size;

    for (size_t i = 0; i < size; i++) {
        graph->inbound[i] = listNew(sizeof(GraphEdge), NULL);
        graph->outbound[i] = listNew(sizeof(GraphEdge), NULL);
    }

    return graph;
}

void graphFree(Graph * graph) {
    for (size_t i = 0; i < graph->size; i++) {
        listFree(graph->inbound[i]);
        listFree(graph->outbound[i]);
    }

    free(graph->inbound);
    free(graph->outbound);

    free(graph);
}

void graphAddEdge(Graph * graph, size_t source, size_t dest, size_t weight) {
    if (source == dest) {
        return;
    }

    GraphEdge edge = {
        .weight = weight,
        .destination = dest,
        .source = source  
    };
    listInsert(graph->inbound[dest], &edge);
    listInsert(graph->outbound[source], &edge);
}

List * graphGetOutboundEdges(Graph * graph, size_t node) {
    return graph->outbound[node];
}

List * graphGetInboundEdges(Graph * graph, size_t node) {
    return graph->inbound[node];
}

GraphEdge * graphBreadthFirstSearch(Graph * graph, size_t start, size_t end) {
    char * visited = calloc(graph->size, sizeof(char));
    List * queue = listNew(sizeof(size_t), NULL);
    GraphEdge * path = malloc(graph->size * sizeof(GraphEdge));

    listInsert(queue, &start);
    visited[start] = 1;

    char found = 0;
    while (!listIsEmpty(queue)) {
        size_t currentNode = *((size_t *)listBegin(queue).current->data);
        listRemoveFirst(queue);

        if (currentNode == end) {
            found = 1;
            break;
        }

        for (ListIterator it = listBegin(graph->outbound[currentNode]); !it.end; it = listNext(it)) {
            GraphEdge edge = *((GraphEdge *)it.current->data);
            
            if (visited[edge.destination]) {
                continue;
            }

            visited[edge.destination] = 1;
            path[edge.destination] = edge;
            listInsert(queue, &edge.destination);
        }
    }

    listFree(queue);
    free(visited);
    if (!found) {
        free(path);
        path = NULL;
    }

    return path;
}

void graphPrintPath(GraphEdge * path, PrintFunction printer, size_t start, size_t end) {
    if (path[end].source != start) {
        graphPrintPath(path, printer, start, path[end].source);
    }
    printer(path[end]);
}