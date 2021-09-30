#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "cartela.h"

const char * bingo = "BINGO";
const int bingo_range[5][2] = {
  { 1, 19}, // B
  {20, 39}, // I
  {40, 59}, // N
  {60, 79}, // G
  {80, 99}, // O
};

uchar ** Cartela(void) {
  uchar ** c = (uchar**) malloc(25 * (sizeof (char)));

  time_t now;
  localtime(&now);
  srand(time(&now));

  uchar cartela[5][5];
  memset(cartela[0], 0, 25);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      const uchar ini = (uchar)bingo_range[j][0], fim = (uchar)bingo_range[j][1];

      int c = 0;
      uchar value = 0;

      PrintCartela(cartela);
      value = Randchar(ini, fim);
      cartela[i][j] = value;
    }
  }

  memcpy(c, cartela, 25);
  return c;
}

uchar Randchar(char inicio, char limite) {
  return inicio + (rand() % (limite - inicio));
}

void PrintCartela(char cartela[5][5]) {
  for (char j = 0; j < 5; j++)
      printf(" %02c |", bingo[j]);
  puts("");

  for (char i = 0; i < 5; i++) {
    for (char j = 0; j < 5; j++) {
      uchar value = cartela[i][j];
      printf(" %02i |", value);

      if (!((j+1)%5))
          puts("");
    }
  }
}
