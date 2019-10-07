/*
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>

/**
 * Nó genérico de uma lista duplamente ligada.
*/
typedef struct ListNode {
    struct ListNode * prev;
    struct ListNode * next;

    void * data;
} ListNode;

/**
 * Função de desalocação do dado genérico armazenado pela lista
*/
typedef void (*freeData)(void *);

/**
 * Lista duplamente ligada 
*/
typedef struct List {
    freeData freeFn;

    unsigned int len;
    unsigned int dataSize;

    ListNode * first;
} List;

/**
 * Cria uma lista
*/
List * listNew(unsigned int dataSize, freeData freeFn);

/**
 * Desaloca uma lista
*/
void listFree(List * l);

/**
 * Insere no início da lista
*/
ListNode * listInsert(List * l, void* data);

/**
 * Insere o dado após o nó passado
*/
ListNode * listInsertAfter(List * l, ListNode * node, void * data);

/**
 * Insere o dado antes do nó passado
*/
ListNode * listInsertBefore(List * l, ListNode * node, void * data);

/**
 * Remove o nó da lista
*/
void listRemove(List * l, ListNode * node);

#endif
