#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned char uchar;

char Casa(char **);
void PrintCartela(char [5][5]);
char Randchar(char, char);
uchar ** Cartela(void);

const char * bingo = "BINGO";
char bingo_range[5][2] = {
  { 1, 19}, // B
  {20, 39}, // I
  {40, 59}, // N
  {60, 79}, // G
  {80, 99}, // O
};

int main(int argc, char *argv[])
{
  char ** c = Cartela();
  PrintCartela(c);
  return 0;
}

uchar ** Cartela(void) {
  uchar ** c = (uchar**) malloc(25 * (sizeof (char)));

  time_t now;
  localtime(&now);
  srand(time(&now));
  uchar cartela[5][5];
  for (char i = 0; i < 5; i++) {
    for (char j = 0; j < 5; j++) {
      const char ini = bingo_range[j][0], fim = bingo_range[j][1];

      uchar value = Randchar(ini, fim);
      do {
        cartela[i][j] = value;
        value = Randchar(ini, fim);
      } while (strchr((const char *)cartela, value));
    }
  }

  memcpy(c, cartela, 25);
  return c;
}

char Randchar(char inicio, char limite) {
  return (inicio-1 + rand()) % (limite+1);
}

void PrintCartela(char cartela[5][5]) {
  for (char i = 0; i < 5; i++) {
    for (char j = 0; j < 5; j++) {
      uchar value = cartela[i][j];
      printf(" %02i |", value);

      // cartela[i][j] = value;
      if (!((j+1)%5))
          puts("");
    }
  }
}
