#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arvore.h"

#include "packet.h"

#define _BUF_SIZE 40

Packet * packetNew(size_t id, const char * data) {
    Packet * p = malloc(sizeof(Packet));
    if (p == NULL) {
        return NULL;
    }

    p->data = malloc(sizeof(char) * PACKET_CONTENT_SIZE + 1);
    if (p->data == NULL) {
        free(p);
        return NULL;
    }

    p->id = id;
    strcpy(p->data, data);

    return p;
}

void packetFree(Packet * p) {
    free(p->data);
    free(p);
}

Packet * parsePacket(const char *buf) {
    size_t id;
    char data[PACKET_CONTENT_SIZE];
    sscanf(buf, "%lu%*c%[^\n]8s", &id, data);

    return packetNew(id, data);
}

static void packetTreeFree(void* ptr) {
    free(((Packet *)ptr)->data);
}

Tree * readPackets(FILE * f) {
    Tree * packets = treeNew(sizeof(Packet), &packetTreeFree);

    char buf[_BUF_SIZE];
    while (1) {
        fgets(buf, _BUF_SIZE, f);
        if (buf[0] == '0') {
            break;
        }
        
        Packet * p = parsePacket(buf);
        treeInsert(packets, p->id, p);
        // se inserir, queremos desalocar apenas o pacote e não seu conteúdo string
        // se não inserir, a função packetTreeFree já desaloca a string.
        // (isso tudo pois Tree usa memcpy para copiar o dado para TreeNode)
        free(p);
    }
    
    return packets;
}

static void printPacket(const void * data) {
    Packet * packet = (Packet *)data;

    printf("%s", packet->data);
}

void packetsPrint(Tree * packets) {
    treePrintInOrder(packets, &printPacket, 0);
}