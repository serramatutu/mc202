#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

#define _getData(i) (*(int*)i)

int main() {
    Hashmap * hm = hashmapNew(50, NULL, NULL, sizeof(int), NULL);

    char op = '\0';

    while (op != 'e') {
        char s[50];
        scanf(" %c %s", &op, s);
        size_t size = strlen(s) + 1;
        int data;
        void * ptr;

        switch (op){
            case 'i': // insert
                scanf(" %d", &data);
                hashmapInsert(hm, s, size, &data);
                break;
            case 'r': // remove
                hashmapRemove(hm, s, size);
                break;
            case 'f': // find
                ptr = hashmapFind(hm, s, size);
                if (ptr == NULL) {
                    printf("NOT FOUND\n");
                }
                else {
                    printf("FOUND %d\n", _getData(ptr));
                }
        }
    }

    hashmapFree(hm);

    return EXIT_SUCCESS;
}