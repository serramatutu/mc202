#ifndef PROFESSOR_H
#define PROFESSOR_H

#define MAXCHAR_PNOME 30 // nº máximo de carateres para o nome do professor
#define MAXCHAR_CODIGO 6 // nº máximo de carateres para o código da disciplina

typedef struct {
	char nome[MAXCHAR_PNOME];
	float salario;
	char disciplina[MAXCHAR_CODIGO];
} Professor;

/**
 * Esta função recebe como parâmetro o conjunto de variáveis que abstraem um
 * TAD Professor e devolve uma variável do tipo Professor inicializada com tais
 * parâmetros.
 */
Professor criar_professor(const char nome[], float salario, const char disciplina[]);

/**
 * Esta função recebe como parâmetro uma variável do tipo Professor e aplica
 * o aumento salarial conforme a porcentagem também dada como parâmetro. Daí,
 * a função devolve a variável do tipo Professor já atualizada.
 */
Professor aplicar_aumento(Professor professor, float porcentagem);

/**
 * Esta função recebe como parâmetro uma variável do tipo Professor e uma string
 * (denominada por 'nome'), que tem o papel de retorno da função. Daí, a função
 * realiza uma cópia do campo 'nome' da variável do tipo Professor para a
 * string 'nome'.
 */
void obter_nome(Professor professor, char nome[]);

/**
 * Esta função recebe como parâmetro uma variável do tipo Professor e devolve
 * uma cópia do campo 'salario' do mesmo.
 */
float obter_salario(Professor professor);

/**
 * Esta função recebe como parâmetro uma variável do tipo Professor e uma string
 * (denominada por 'disciplina'), que tem o papel de retorno da função. A função
 * realiza então uma cópia do campo 'disciplina' da variável do tipo Professor
 * para a string 'disciplina'.
 */
void obter_disciplina(Professor professor, char disciplina[]);

#endif
