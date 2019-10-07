/*
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "lista.h"

#define MM_ALLOCATE 'A'
#define MM_DEALLOCATE 'D'
#define MM_REALLOCATE 'R'
#define MM_PRINT 'P'

typedef unsigned int mm_ptr;
typedef unsigned int mm_size;

typedef struct MemoryManager {
    mm_size capacity;
    List * memory;
} MemoryManager;

/**
 * Instancia um gerenciador de memória
*/
MemoryManager * mmNew(mm_size capacity);

/**
 * Desaloca um gerenciador de memória
*/
void mmFree(MemoryManager * mm);

/**
 * Executa uma operação sobre a memória gerenciada 
*/
int mmDoOperation(MemoryManager * mm, char op, const char * params);

/**
 * Printa um MemoryManager
*/
void mmPrint(const MemoryManager * mm);

/**
 * Aloca a quantidade de memória pedida
*/
int mmAllocate(MemoryManager * mm, mm_size size);

/**
 * Desaloca a quantidade de memória pedida a partir do ponteiro inicial
*/
int mmDeallocate(MemoryManager * mm, mm_ptr ptr, mm_size size);

/**
 * Realoca o segmento de memória pedido
*/
int mmReallocate(MemoryManager * mm, mm_ptr ptr, mm_size currentSize, mm_size newSize);

#endif