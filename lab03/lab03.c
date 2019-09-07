// Lucas Valente Viegas de Oliveira Paes - RA 220958
// MC202e

#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "leitor.h"

void le_livros(Livro* livros, int n_livros) {
   char titulo[MAXCHAR_TITULO];
   for (int i=0; i<n_livros; i++) {
      int dia, mes, ano;
      scanf("%d-%d-%d %[^\n] ", &dia, &mes, &ano, titulo);

      Data emprestimo = criar_data(dia, mes, ano);
      livros[i] = criar_livro(titulo, emprestimo);
   }
}

void le_leitores(Leitor* leitores, int n_leitores) {
   char nome[MAXCHAR_LNOME];
   int e, transacao;
   for (int i=0; i<n_leitores; i++) {
      scanf("%s %d ", nome, &e);
      leitores[i] = criar_leitor(nome, e);

      for (int j=0; j<e; j++) {
         scanf("%d ", &transacao);
         if (transacao < 0) {
            registrar_devolucao(&leitores[i], -transacao-1);
         }
         else {
            registrar_restituicao(&leitores[i], transacao-1);
         }
      }
   }
}

int main()
{
   Livro* livros = NULL;
   Leitor* leitores = NULL;

   int n_livros, n_leitores;
   scanf("%d %d ", &n_livros, &n_leitores);

   livros = malloc(n_livros * sizeof(Livro));
   if (livros == NULL)
      exit(1);
   le_livros(livros, n_livros);

   leitores = malloc(n_leitores * sizeof(Leitor));
   if (leitores == NULL)
      exit(1);
   le_leitores(leitores, n_leitores);

   int dia, mes, ano;
   scanf("%d-%d-%d", &dia, &mes, &ano);
   Data thresh = criar_data(dia, mes, ano);

   for (int i=0; i<n_leitores; i++) {
      Leitor* leitor = &leitores[i];
      const int *restituicoes = obter_restituicoes(leitor);
      const int *devolucoes = obter_devolucoes(leitor);

      printf("%s\n", obter_nome(leitor));
      for (int r=0; r<obter_num_restituicoes(leitor); r++) {
         Livro* livro = &livros[restituicoes[r]];
         Data emprestimo = obter_data_emprestimo(livro);
         if (eh_nula(emprestimo) || eh_menor_que(thresh, emprestimo))
            continue;
         printf("Restituição: %s\n", obter_titulo(livro));
      }
      for (int d=0; d<obter_num_devolucoes(leitor); d++) {
         Livro* livro = &livros[devolucoes[d]];
         Data emprestimo = obter_data_emprestimo(livro);
         if (eh_nula(emprestimo) || eh_menor_que(thresh, emprestimo))
            continue;

         printf("Devolução: %s\n", obter_titulo(livro));
      }
   }

   for (int i=0; i<n_leitores; i++)
      desalocar_memoria(&leitores[i]);

   free(livros);
   free(leitores);

   return 0;
}
