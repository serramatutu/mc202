#include <stdlib.h>
#include <string.h>

#include "lista.h"

ListNode * _newNode(void* data, unsigned int dataSize) {
    // aloca um novo nó
    ListNode * newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->next = NULL;
    newNode->prev = NULL;

    // aloca a memória necessária para armazenar o dado passado
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    // copia o dado passado para o novo nó
    memcpy(newNode->data, data, dataSize);

    return newNode;
}

void _freeNode(List * l, ListNode * node) {
    // se o tipo armazenado tiver função customizada de desalocação, é preciso chamá-la
    if (l->freeFn != NULL) { 
        l->freeFn(node->data);
    }
    free(node);
}

void listFree(List * l) {
    if (l->first == NULL) {
        free(l);
        return;
    }

    ListNode * current = l->first;
    do {
        ListNode * next = current->next;
        _freeNode(l, current);
        current = next;
    } while (current != l->first);

    free(l);
}

List * listNew(unsigned int dataSize, freeData freeFn) {
    List * l = malloc(sizeof(List));
    l->first = NULL;
    l->dataSize = dataSize;
    l->freeFn = freeFn;
    return l;
}

ListNode * listInsert(List * l, void* data) {
    ListNode * newNode = _newNode(data, l->dataSize);
    if (newNode == NULL) {
        return NULL;
    }

    l->len++;

    if (l->first == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else {
        newNode->next = l->first;
        newNode->prev = l->first->prev;
        newNode->prev->next = newNode;
        l->first->prev = newNode;
    }
    l->first = newNode;

    return newNode;
}

ListNode * listInsertAfter(List * l, ListNode * node, void* data) {
    ListNode * newNode = _newNode(data, l->dataSize);
    if (newNode == NULL) {
        return NULL;
    }

    l->len++;

    newNode->next = node->next;
    node->next = newNode;
    newNode->prev = node;
    newNode->next->prev = newNode;

    return newNode;
}

void listRemoveNode(List * l, ListNode * node) {
    l->len--;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    // no caso de o nó ser o primeiro da lista
    if (node == l->first) {
        if (node->prev == node) { // se a lista só tem esse nó
            l->first = NULL;
        }
        else {
            l->first = node->prev;
        }
    }

    _freeNode(l, node);
}