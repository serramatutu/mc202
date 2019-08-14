#include <stdio.h>

unsigned long long fatorial(unsigned int n)
{
   unsigned long long fat = 1;

   while (n > 1) {
      fat *= n--;
   }

   return fat;
}

int main()
{
   unsigned int n;
   
   scanf("%d", &n);

   if (n <= 20) { // calcula o fatorial para n <= 20

      unsigned long long fat = fatorial(n);

      printf("%u! = %llu\n", n, fat);
   }
   else {
      printf("%u! = \"integer overflow\"\n", n);
   }

   return 0;
}
