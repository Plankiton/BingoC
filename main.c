#include <stdio.h>
#include <stdlib.h>
#include "cartela.h"

int main(int argc, char *argv[])
{
  char empty = 0;
  if (argc > 1) {
    empty = 1;
  }

  char ** c = Cartela(empty);
  PrintCartela(c);

  if (argc > 1) {
    FILE * cart = fopen("cartelas.bin", "rb");
    if (cart == NULL) {
      puts("Erro ao abrir arquivo!");
      return 1;
    }

    char jog[GAMER_NAME_SIZE];
    openCartela(cart, jog, c);
    puts(jog);
    PrintCartela(c);
    fclose(cart);
  }

  FILE * cart = fopen("cartelas.bin", "wb");
  if (cart == NULL) {
    puts("Erro ao abrir arquivo!");
    return 1;
  }

  saveCartela(cart, "Joao", c);
  fclose(cart);
  return 0;
}
