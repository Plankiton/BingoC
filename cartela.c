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

void troca(uchar* a, uchar* b) {
    uchar temp = *a;
    *a = *b;
    *b = temp;
}

void OrgVet(uchar * vet, uchar n) {
    uchar i, j, min;

    uchar v[n];
    memcpy(v, vet, n);

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;

        troca(&v[min], &v[i]);
    }

    memcpy(vet, v, n);
}

uchar ** Cartela(uchar empty) {
  uchar ** c = (uchar**) malloc(25 * (sizeof (char)));

  time_t now;
  localtime(&now);
  srand(time(&now));

  uchar cartela[5][5];
  memset(cartela[0], 0, 25);
  if (empty) {
    memcpy(c, cartela, 25);
    return c;
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      const uchar ini = (uchar)bingo_range[j][0], fim = (uchar)bingo_range[j][1];

      int c = 0;
      uchar value = 0;

      while (strchr((const char*)cartela[i], value))
          value = Randchar(ini, fim);
      cartela[i][j] = value;
    }
  }

  for (int i = 0; i < 5; i++) {
    OrgVet(&cartela[i], 5);
  }

  memcpy(c, cartela, 25);
  return c;
}

uchar Randchar(char inicio, char limite) {
  return inicio + (rand() % (limite - inicio));
}

void PrintCartela(char cartela[5][5]) {
  printf("    ");
  for (char j = 0; j < 5; j++)
      printf(" %02c  ", bingo[j]);
  puts("");

  for (char i = 0; i < 5; i++) {
    for (char j = 0; j < 5; j++) {
      if (j == 0) {
        printf(" %i |", i+1);
      }

      uchar value = cartela[i][j];
      printf(" %02i |", value);

      if (!((j+1)%5))
          puts("");
    }
  }
}

int saveCartela(FILE * file, const char * jogador, const uchar ** cartela, int overid) {
  int i;

  fseek(file, -1, SEEK_END);
  if (overid)
    fseek(file, overid, SEEK_SET);

  int jog_size = strlen(jogador);
  fwrite(jogador, 1, jog_size, file);
  for (int i = jog_size; i < GAMER_NAME_SIZE; i++) {
    fputc(0, file);
  }

  fwrite(cartela, 5, 5, file);
  fputc('\n', file);
  return ftell(file) - (5*5 + GAMER_NAME_SIZE);
}

int openCartela(FILE * file, const char * jogador, const uchar ** cartela) {
  char * jog = (char *)jogador;
  char * car = (char *)cartela;

  fread(jog, 1, GAMER_NAME_SIZE, file);
  fread(car, 5, 5, file);

  return ftell(file);
}
