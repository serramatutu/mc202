#include <stdio.h>

#include "aluno.h"
#include "professor.h"

#define MAX_M 100 // nº máximo de professores
#define MAX_N 200 // nº máximo de alunos

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n);

int main()
{
    /** ***********************************************************************
    *          ATENÇÃO: A função principal não deve ser modificada!           *
    *********************************************************************** **/

   Professor professores[MAX_M];  // vetor para o conjunto de professores
   Aluno alunos[MAX_N];           // vetor para o conjunto de alunos

   char nome[MAXCHAR_PNOME], disciplina[MAXCHAR_CODIGO];
   float salario, desempenho;
   int registro_academico, num_disciplinas;

   int m, n;

   scanf("%d", &m); // lê o nº de professores

   for (int i = 0; i < m; ++i) { // segue com a leitura dos professores
      scanf(" %s %f %s", nome, &salario, disciplina);
      professores[i] = criar_professor(nome, salario, disciplina);
   }

	scanf("%d", &n);  // lê o nº de alunos

   for (int i = 0; i < n; ++i) { // segue com a leitura dos alunos

      scanf("%d %f %d", &registro_academico, &desempenho, &num_disciplinas);
      alunos[i] = criar_aluno(registro_academico, desempenho);

      while (num_disciplinas > 0) {
         scanf(" %s", disciplina);
         alunos[i] = adicionar_disciplina(alunos[i], disciplina);
         num_disciplinas -= 1;
      }
   }

	processar_aumento(professores, alunos, m, n); // processa a bonificação

   for (int i = 0; i < m; ++i) { // segue com a impressão da saída
      obter_nome(professores[i], nome);
      printf("%s %.2f\n", nome, obter_salario(professores[i]));
   }

	return 0;
}

/**
 * Esta função recebe como parâmetro um conjunto de variáveis que abstraem a
 * entrada do problema e realiza a bonificação salarial dos professores
 * conforme especificado no enunciado da tarefa.
 */

void processar_aumento(Professor professores[], Aluno alunos[], int m, int n) {
   for (int professor=0; professor<m; professor++) {
      char disciplina[MAXCHAR_CODIGO];
      obter_disciplina(professores[professor], disciplina);

      float pior_desempenho = 20.0;
      for (int aluno=0; aluno<n; aluno++) {
         if (!validar_matricula(alunos[aluno], disciplina))
            continue;

         float desempenho = obter_desempenho(alunos[aluno]);
         
         if (desempenho < pior_desempenho)
            pior_desempenho = desempenho;
      }

      float porcentagem;
      if (pior_desempenho > 10.0 || pior_desempenho < 8.5) // turma sem aluno
         porcentagem = 0;
      else if (pior_desempenho == 10.0)
         porcentagem = 0.15;
      else if (pior_desempenho >= 9.0)
         porcentagem = 0.10;
      else if (pior_desempenho >= 8.5)
         porcentagem = 0.05;
      
      professores[professor] = aplicar_aumento(professores[professor], porcentagem);
   }
}
