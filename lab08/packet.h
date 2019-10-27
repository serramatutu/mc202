#ifndef PACKET_H
#define PACKET_H

#include <stdlib.h>
#include <stdio.h>

#include "abb.h"

#define PACKET_CONTENT_SIZE 8

typedef struct Packet {
    size_t id;
    char * data;
} Packet;

Packet * packetNew(size_t id, const char * data);

void packetFree(Packet * p);

Packet * parsePacket(const char *buf);

Tree * readPackets(FILE * f);

void packetsPrint(Tree * packets);

#endif