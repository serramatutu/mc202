#ifndef DATA_H
#define DATA_H

typedef struct {
   int dia;
   int mes;
   int ano;
} Data;

/**
 * Esta função devolve uma variável do tipo Data inicializada com os parâmetros
 * dados.
 */
Data criar_data(int dia, int mes, int ano);

/**
 * Esta função devolve o valor 1 (true) se o valor da 'data' é nulo; caso
 * contrário, devolve o valor 0 (false).
 */
int eh_nula(Data data);

/**
 * Esta função devolve o valor 1 (true) se o valor da 'data1' é menor que o
 * valor da 'data2'; caso contrário, devolve o valor 0 (false).
 */
int eh_menor_que(Data data1, Data data2);

#endif
