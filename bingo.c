#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "bingo.h"

const char * bingo = "BINGO";
const int bingo_range[5][2] = {
  { 1, 19}, // B
  {20, 39}, // I
  {40, 59}, // N
  {60, 79}, // G
  {80, 99}, // O
};

void troque(byte * a, byte * b) {
    byte temp = *a;
    *a = *b;
    *b = temp;
}

void ordene(byte * vet, byte n) {
    byte i, j, min;

    byte v[n];
    memcpy(v, vet, n);

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;

        troque(&v[min], &v[i]);
    }

    memcpy(vet, v, n);
}

byte ** Cartela() {
  byte ** c = (byte**) malloc(25 * (sizeof (char)));
  memset(c, 0, 25);
  return c;
}

byte * Jogador() {
  byte * c = malloc(15);
  memset(c, 0, 15);
  return c;
}

void popule(byte ** c) {
  time_t now;
  localtime(&now);
  srand(time(&now));

  byte cartela[5][5];
  memset(cartela[0], 0, 25);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      const byte ini = (byte)bingo_range[j][0], fim = (byte)bingo_range[j][1];

      int c = 0;
      byte value = 0;

      while (strchr((const char*)cartela[i], value))
          value = sorteie(ini, fim);
      cartela[i][j] = value;
    }
  }

  for (int i = 0; i < 5; i++) {
    ordene(&cartela[i], 5);
  }
  memcpy(c, cartela, 25);
}

byte sorteie(char inicio, char limite) {
  return inicio + (rand() % (limite - inicio));
}

void mostreCartela(const char ** cartela) {
  printf("    ");
  for (char j = 0; j < 5; j++)
      printf(" %02c  ", bingo[j]);
  puts("");

  for (char i = 0; i < 5; i++) {
    for (char j = 0; j < 5; j++) {
      if (j == 0) {
        printf(" %i |", i+1);
      }

      byte value = cartela[i][j];
      printf(" %02i |", value);

      if (!((j+1)%5))
          puts("");
    }
  }
}

int salveCartela(
 FILE * file,
 const byte ** cartela,
 const int jogador_id,
 const int cart_id 
) {
  fwrite(&jogador_id, sizeof(int), 1, file);
  fwrite(&cart_id, sizeof(int), 1, file);
  fwrite(cartela, 5, 5, file);
  return ftell(file);
}

int abraCartela(
 FILE * file,
 const byte ** cartela,
 const int jogador_id,
 const int cart_id 
) {
  fread(&jogador_id, sizeof(int), 1, file);
  fread(&cart_id, sizeof(int), 1, file);
  fread(cartela, 5, 5, file);
  return ftell(file);
}

void mostreTitulo(
    const char * title,
) {
  printf(" %010s | %010s\n", "BINGO", title);
  mostreLinha();
}

void mostreLinha() {
  puts  (" -----------------------");
}
