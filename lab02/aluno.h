#ifndef ALUNO_H
#define ALUNO_H

#define MAX_DISCIPLINA 5 // nº máximo de disciplinas
#define MAXCHAR_CODIGO 6 // nº máximo de carateres para o código da disciplina

typedef struct {
   int registro_academico;
   float desempenho;
   int num_disciplinas;
   char disciplinas[MAX_DISCIPLINA][MAXCHAR_CODIGO];
} Aluno;

/**
 * Esta função recebe como parâmetro o conjunto mínimo de variáveis que compõem
 * um TAD Aluno e devolve uma variável do tipo Aluno inicializada com tais
 * parâmetros. Obs.: é necessário inicializar também o campo 'num_disciplinas'.
 */
Aluno criar_aluno(int registro_academico, float desempenho);

/**
 * Esta função recebe como parâmetro a cópia de uma variável do tipo Aluno e
 * adiciona uma nova disciplina (também dada como parâmetro) a lista atual de
 * disciplinas cursadas pelo aluno. Por fim, a função devolve a variável do
 * tipo Aluno já atualizada.
 */
Aluno adicionar_disciplina(Aluno aluno, const char disciplina[]);

/**
 * Esta função recebe como parâmetro a cópia de uma variável do Aluno e devolve
 * o campo 'desempenho' do mesmo.
 */
float obter_desempenho(Aluno aluno);

/**
 * Esta função recebe como parâmetro a cópia de uma variável do tipo Aluno e
 * uma string (chamada 'disciplina'). Daí, a função realiza uma verificação
 * para determinar se o aluno está matriculado na disciplina. Caso afirmativo,
 * a função devolve o valor 1 (true); caso contrário, a função devolve o
 * valor 0 (false).
 */
int validar_matricula(Aluno aluno, const char disciplina[]);

#endif
