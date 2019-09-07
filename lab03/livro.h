#ifndef LIVRO_H
#define LIVRO_H

#include "data.h"

#define MAXCHAR_TITULO 101

typedef struct {
   char titulo[MAXCHAR_TITULO];
   Data emprestimo;
} Livro;

/**
 * Esta função recebe como parâmetro o título do livro e a data de devolução e
 * devolve uma variável do tipo Livro inicializada.
 */
Livro criar_livro(const char* titulo, Data emprestimo);

/**
 * Esta função devolve a data de devolução.
 */
Data obter_data_emprestimo(const Livro* livro);

/**
 * Esta função devolve o título.
 */
const char* obter_titulo(const Livro* livro);

#endif
