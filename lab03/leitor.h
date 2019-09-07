#ifndef LEITOR_H
#define LEITOR_H

#define MAXCHAR_LNOME 16

typedef struct  {
   char nome[MAXCHAR_LNOME]; // string para o (primeiro) nome do leitor
   int *restituicoes;        // ponteiro para a identificação das restituições
   int *devolucoes;          // ponteiro para a identificação das devoluções
   int num_restituicoes;     // número de restituições registradas
   int num_devolucoes;       // número de devoluções registradas
} Leitor;

/**
 * Esta função recebe como parâmetro o nome do leitor e um inteiro 'e' (nº de
 * livros deixados para empréstimo mais o número de livros a serem devolvidos
 * pelo leitor), e devolve uma variável do tipo Leitor inicializada. Obs.: é
 * necessário alocar memória a ser apontada por 'restituicoes' e 'devolucoes',
 * e inicializar também os campos 'num_restituicoes' e 'num_devolucoes'.
 */
Leitor criar_leitor(const char* nome, int e);

/**
 * Esta função desaloca a memória alocada dentro da função 'criar_leitor'.
 */
void desalocar_memoria(Leitor* leitor);

/**
 * Esta função devolve o campo 'nome' do leitor.
 */
const char* obter_nome(const Leitor* leitor);

/**
 * Esta função registra um novo livro (i.e., adiciona a identificação do livro)
 * no vetor de restituições.
 */
void registrar_restituicao(Leitor* leitor, int i);

/**
 * Esta função registra um novo livro (i.e., adiciona a identificação do livro)
 * no vetor de devoluções.
 */
void registrar_devolucao(Leitor* leitor, int i);

/**
 * Esta função devolve o vetor de restituições.
 */
const int* obter_restituicoes(const Leitor* leitor);

/**
 * Esta função devolve o vetor de devoluções.
 */
const int* obter_devolucoes(const Leitor* leitor);

/**
 * Esta função devolve o número de restituições registradas.
 */
int obter_num_restituicoes(const Leitor* leitor);

/**
 * Esta função devolve o número de devoluções registradas.
 */
int obter_num_devolucoes(const Leitor* leitor);

#endif
