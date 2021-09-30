#include <stdio.h>
#include <stdlib.h>
#include "cartela.h"

int main(int argc, char *argv[])
{
  char ** c = Cartela();
  PrintCartela(c);
  return 0;
}
