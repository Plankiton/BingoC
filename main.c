#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Casa(int **);
int ** Cartela(void);

int main(int argc, char *argv[])
{
  
  return 0;
}

int ** Cartela(void) {
  int ** cartela = (int**)malloc((size_t)5*5);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cartela[i][j] = Casa(cartela);
    }
  }

  return cartela;
}

int RandInt(int limite) {
  unsigned int r = 0;

  srand(time(NULL));
  // Enquanto o valor gerado for 0
  while (!r)
    r = rand();

  // Retorna resto da divisão pelo limite mais 1. (limita o número a esse limite)
  return r % limite+1;
}

int Casa(int ** cartela) {
  int * casa = *cartela, valor = RandInt(99);

  int tem_repetido = 1;
  while (tem_repetido) {
    tem_repetido = 0;
    for (int i = 0; i < 25; i++) {
      if (casa[i] == valor) {
        valor = RandInt(99);
        tem_repetido = 1;
        break;
      }
    }
  }

  return valor;
}
