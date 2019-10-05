/* 
Lucas Valente Viegas de Oliveira Paes
RA 220958
MC202 E
*/

#include "map.h"

int main() {
    int pos[2];
    // lê o mapa da entrada
    Map map = mapRead();
    // encontra e entrada do labirinto e marcamos o início da busca uma posição abaixo da entrada
    mapFindEntrance(map, pos); 
    pos[1] += 1;
    // encontra o caminho da entrada até a espada, desviando do inimigo, marcando com '-'
    char avoid[1] = { ENEMY };
    mapFindPath(map, pos, SWORD, avoid, '-'); 
    // salva a posição da espada, pois o método "mapFindPath" sobrescreverá sua posição
    int swordPos[2] = {pos[0], pos[1]};
    // encontra o caminho da espada até o inimigo, marcando com ':'
    mapFindPath(map, pos, ENEMY, "", ':');
    // restaura o caractere da espada
    map.matrix[swordPos[1]][swordPos[0]] = SWORD;
    // troca todos os caracteres de caminho (':' e '-') por '*'
    mapStandardizePath(map, '*', ":-"); 
    // printa o mapa
    mapPrint(map);
    // desaloca o mapa
    mapClear(&map);

    return 0;
}