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

    size_t len;
    size_t dataSize;

    ListNode * first;
} List;

/**
 * Cria uma lista
*/
List * listNew(size_t dataSize, freeData freeFn);

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
 * Remove o primeiro nó da lista se a lista não estiver vazia
*/
char listRemoveFirst(List * l);

/**
 * Remove o nó da lista
*/
void listRemove(List * l, ListNode * node);

/**
 * Checa se a lista é vazia
*/
char listIsEmpty(List * l);

/**
 * Obtém o tamanho da lista 
*/
size_t listSize(List * l);

/**
 * Iterador em uma lista duplamente ligada 
*/
typedef struct ListIterator {
    List * list;
    ListNode * current;

    char direction;
    size_t pos;

    char end;
} ListIterator;


#define ITERATOR_FORWARD 1
#define ITERATOR_REVERSE -1

/**
 * Obtém um iterador da lista 
*/
ListIterator listBegin(List * list);

/**
 * Obtém um iterador reverso da lista 
*/
ListIterator listRBegin(List * list);

/**
 * Obtém o próximo iterador da lista
*/
ListIterator listNext(ListIterator it);

#endif
