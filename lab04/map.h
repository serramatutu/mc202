/* 
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#define FREE ' '
#define WALL '#'
#define ENTRANCE 'E'
#define SWORD 'S'
#define ENEMY 'M'

typedef struct Map {
    int m, n;
    char ** matrix;
} Map;

Map mapRead();

void mapFindEntrance(const Map map, int pos[2]);

int mapFindPath(Map map, int pos[2], char target, const char * avoid, char pathMarker);

void mapStandardizePath(Map map, char standardPathMarker, const char * pathMarkers);

void mapPrint(const Map map);

void mapClear(Map * map);

#endif