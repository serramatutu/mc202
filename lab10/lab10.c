#define LAB10

#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define _getData(i) (*(int*)i)

int main() {
    Hashmap * hm = hashmapNew(50, NULL, NULL, sizeof(int), NULL);

    char op = '\0';

    while (op != 'e') {
        char s[50];
        scanf("%c %s", &op, s);
        size_t size = strlen(s);
        int data;

        switch (op){
            case 'i':
                scanf("%d", &data);
                hashmapInsert(hm, s, size, &data);
                break;
            case 'r':
                hashmapRemove(hm, s, size);
                break;
            case 'f':
                printf("%d", _getData(hashmapFind(hm, s, size)));
        }
    }

    hashmapFree(hm);

    return EXIT_SUCCESS;
}