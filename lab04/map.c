/* 
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

/**
 * Lê um mapa de tamanho m x n da entrada, gravando sua entrada em pos e
 * retornando o mapa lido
*/
Map mapRead() {
    Map map;
    scanf("%d %d", &map.m, &map.n);
    map.matrix = malloc(map.m * sizeof(char*));
    if (map.matrix == NULL) {
        exit(1);
    }

    for (int i = 0; i < map.m; i++) {
        scanf(" ");
        map.matrix[i] = malloc(map.n * sizeof(char));
        if (map.matrix[i] == NULL) {
            exit(1);
        }

        for (int j = 0; j < map.n; j++) {
            scanf("%c", &map.matrix[i][j]);
        }
    }

    return map;
}

/**
 * Encontra a entrada de um mapa, colocando suas coordenadas em pos 
*/
void mapFindEntrance(const Map map, int pos[2]) {
    pos[1] = 0;
    for (int j = 0; j < map.n; j++) {
        if (map.matrix[0][j] == ENTRANCE) {
            pos[0] = j;
            return;
        }
    }
}

/**
 * Conjunto ordenado de movimentos possíveis para se fazer em um mapa
*/
const int _moves[4][2] = {
    {1, 0}, // direita
    {0, 1}, // baixo
    {-1, 0},// esquerda
    {0, -1} // cima
};

/**
 * Encontra o caminho desviando de avoid a partir de pos até o símbolo target em map, deixando-o
 * marcado com pathMarker. Retorna 0 se não obteve sucesso e 1 se teve sucesso.
*/
int mapFindPath(Map map, int pos[2], char target, const char * avoid, char pathMarker) {
    char val = map.matrix[pos[1]][pos[0]];

    // se é parede, se é entrada, se deve desviar ou se já passou por ali, este não é um caminho válido
    if (val == WALL || val == pathMarker || val == ENTRANCE || strchr(avoid, val))
        return 0;
    // se encontrou
    if (val == target)
        return 1;
    
    // marca que passou por pos com pathMarker. isso evita que a recursão nunca acabe
    map.matrix[pos[1]][pos[0]] = pathMarker;

    for (int i = 0; i < 4; i++) {
        pos[0] += _moves[i][0];
        pos[1] += _moves[i][1];

        if (mapFindPath(map, pos, target, avoid, pathMarker)) {
            return 1;
        }

        // desfaz o movimento se deu errado
        pos[0] -= _moves[i][0];
        pos[1] -= _moves[i][1];
    }
    
    // desmarca o caminho pois não encontrou target por aqui
    map.matrix[pos[1]][pos[0]] = val;

    return 0;
}

/**
 * Troca todos os pathMarkers presentes por um standardPathMarker
*/
void mapStandardizePath(Map map, char standardPathMarker, const char * pathMarkers) {
    for (int i = 0; i < map.m; i++) {
        for (int j = 0; j < map.n; j++) {
            // se a posição atual é um caminho marcado, coloca o caractere padrão
            if (strchr(pathMarkers, map.matrix[i][j])) {
                map.matrix[i][j] = standardPathMarker;
            }
        }
    }
}

/**
 * Escreve um mapa na saída.
*/
void mapPrint(const Map map) {
    for (int i = 0; i < map.m; i++) {
        for (int j = 0; j < map.n; j++) {
            printf("%c", map.matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Desaloca um mapa. 
*/
void mapClear(Map * map) {
    for (int i = 0; i < map->m; i++) {
        free(map->matrix[i]);
    }
    free(map->matrix);
    map->m = 0;
    map->n = 0;
}