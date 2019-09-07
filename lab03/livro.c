// Lucas Valente Viegas de Oliveira Paes - RA 220958
// MC202e

#include <string.h>

#include "livro.h"

Livro criar_livro(const char* titulo, Data emprestimo)
{
   Livro livro = {
       .emprestimo = emprestimo
   };
   strcpy(livro.titulo, titulo);
   return livro;
}

Data obter_data_emprestimo(const Livro* livro)
{
   return livro->emprestimo;
}

const char* obter_titulo(const Livro* livro)
{
   return livro->titulo;
}
