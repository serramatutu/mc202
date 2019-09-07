// Lucas Valente Viegas de Oliveira Paes - RA 220958
// MC202e

#include "data.h"

Data criar_data(int dia, int mes, int ano)
{
   Data d = {
       .dia = dia,
       .mes = mes,
       .ano = ano
   };
   return d;
}

int eh_nula(Data data)
{
   return data.dia + data.mes + data.ano == 0;
}

int eh_menor_que(Data data1, Data data2)
{
   if (data1.ano > data2.ano)
      return 0;
   if (data1.mes > data2.mes)
      return 0;
   if (data1.dia > data2.dia)
      return 0;
   return 1;
}
