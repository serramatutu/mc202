#include <stdlib.h>
#include <stdio.h>

typedef struct MemoryData {
    int addr;
    int len;
} MemoryData;

#include "lista.h"

MemoryData getData(ListNode * node) {
    return *(MemoryData*)node->data;
}

// OBS: fiz a lista genérica para poder reutilizá-la em outros labs e for fun :)
int main() {
    List * l = NULL;
    l = listNew(sizeof(MemoryData), NULL);
    if (l == NULL) {
        return EXIT_FAILURE;
    }

    int n;
    scanf("%d ", &n);
    for(int i=0; i<n; i++) {
        MemoryData data;
        scanf("%d %d ", &data.addr, &data.len);

        listInsert(l, &data);
    }

    ListNode* current = l->first;
    for (int i=0; i<l->len; i++) {
        MemoryData data = getData(current);
        printf("Data %d: %d %d", i, data.addr, data.len);
        current = current->next;
    }

    listFree(l);

    return EXIT_SUCCESS;
}