/*
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#include <stdio.h>

#include "memorymanager.h"

struct _MemoryData {
    mm_ptr addr;
    mm_size len;
};
typedef struct _MemoryData _MemoryData;

/**
 * Extrai um MemoryData de um nó de lista genérico
*/
#define _getData(node) ((_MemoryData*)node->data)

MemoryManager * mmNew(mm_size capacity) {
    MemoryManager * mm = malloc(sizeof(MemoryManager));
    if (mm == NULL) {
        return NULL;
    }

    mm->memory = listNew(sizeof(_MemoryData), NULL);
    if (mm->memory == NULL) {
        free(mm);
        return NULL;
    }

    mm->capacity = capacity;
    _MemoryData firstNode = {
        .addr = 0,
        .len = capacity
    };
    listInsert(mm->memory, &firstNode);

    return mm;
}

void mmFree(MemoryManager * mm) {
    listFree(mm->memory);
    free(mm);
}

int mmDoOperation(MemoryManager * mm, char op, const char * params) {
    mm_ptr ptr;
    mm_size size, newSize;

    switch (op) {
        case MM_PRINT:
            mmPrint(mm);
            break;

        case MM_ALLOCATE:
            sscanf(params, "%u", &size);
            mmAllocate(mm, size);
            break;
        
        case MM_DEALLOCATE:
            sscanf(params, "%u %u", &ptr, &size);
            return mmDeallocate(mm, ptr, size);
            break;

        case MM_REALLOCATE:
            sscanf(params, "%u %u %u", &ptr, &size, &newSize);
            return mmReallocate(mm, ptr, size, newSize);
            break;
    }
    return 1;
}

void mmPrint(const MemoryManager * mm) {
    printf("heap:\n");
    if (mm->memory->len == 0) {
        return;
    }
    
    ListNode * n = mm->memory->first;
    do
    {
        _MemoryData * data = _getData(n);
        printf("%u %u\n", data->addr, data->len);
        n = n->next;
    } while (n != mm->memory->first);
}

/**
 * Concatena o nó com o anterior caso seja possível
*/
static void _normalizeNodeWithPrev(MemoryManager * mm, ListNode * node) {
    _MemoryData * data = _getData(node);
    _MemoryData * prevData = _getData(node->prev);

    if (prevData->addr + prevData->len == data->addr) {
        prevData->len += data->len;

        listRemove(mm->memory, node);
    }
    else if (data->addr < _getData(mm->memory->first)->addr) {
        mm->memory->first = node;
    }
}

/**
 * Compacta a lista de memória de um MemoryManager dado um nó recém inserido
*/
static void _normalizeNode(MemoryManager * mm, ListNode * node) {
    if (_getData(node)->len == 0) {
        listRemove(mm->memory, node);
    }
    else {
        ListNode * next = node->next;
        _normalizeNodeWithPrev(mm, node);
        _normalizeNodeWithPrev(mm, next);
    }
}

int mmAllocate(MemoryManager * mm, mm_size size) {
    ListNode * current = mm->memory->first;
    _MemoryData * data = _getData(current);
    ListNode * bestFit = current;
    _MemoryData * bestFitData = data;
    for (unsigned int i = 0; i < mm->memory->len; i++) {
        int delta = (int)data->len - size;
        if (delta >= 0 && delta < (int)bestFitData->len - size) {
            bestFit = current;
            bestFitData = data;
        }
        current = current->next;
        data = _getData(current);
    }

    bestFitData->addr += size;
    bestFitData->len -= size;

    _normalizeNode(mm, bestFit);

    return 1;
}

int mmDeallocate(MemoryManager * mm, mm_ptr ptr, mm_size size){
    _MemoryData newData = {
        .addr = ptr,
        .len = size
    };

    ListNode * current = mm->memory->first;
    if (current == NULL) {
        ListNode * insertedNode = listInsert(mm->memory, &newData);
        return insertedNode == NULL ? 0 : 1;
    }

    _MemoryData * data = _getData(current);
    while (data->addr < ptr && current->next != mm->memory->first) {
        current = current->next;
        data = _getData(current);
    }

    ListNode * insertedNode;
    if (data->addr < ptr) {
        insertedNode = listInsertAfter(mm->memory, current, &newData);
    }
    else {
        insertedNode = listInsertBefore(mm->memory, current, &newData);
    }

    if (insertedNode == NULL) {
        return 0;
    }
    _normalizeNode(mm, insertedNode);

    return 1;
}

int mmReallocate(MemoryManager * mm, mm_ptr ptr, mm_size currentSize, mm_size newSize){
    ListNode * current = mm->memory->first;
    if (current == NULL) {
        mmDeallocate(mm, ptr + newSize, currentSize - newSize);
        return 1;
    }
    _MemoryData * data = _getData(current);
    while (data->addr < ptr && current->next != mm->memory->first) {
        current = current->next;
        data = _getData(current);
    }

    int delta = (int)newSize - currentSize;
    if (delta > 0) {
        // if (data->addr < ptr || delta > (int)data->len || ptr + newSize > mm->capacity) {
        if (ptr + newSize > mm->capacity || // se a expansão excede a capacidade
            data->addr < ptr ||  // se não há mais blocos livres após ptr
            ptr + currentSize < data->addr || // se há algo alocado entre ptr e o próximo bloco livre
            delta > (int)data->len) { // se não cabe no próximo bloco livre

            if (!mmDeallocate(mm, ptr, currentSize)) {
                return 0;
            }
            return mmAllocate(mm, newSize);
        }

        data->addr += delta;
        data->len -= delta;
        _normalizeNode(mm, current);
    }
    else {
        mmDeallocate(mm, ptr + newSize, currentSize - newSize);
    }

    return 1;
}