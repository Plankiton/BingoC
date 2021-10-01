#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cartela.h"
#include "bingo.h"

uchar Bingo() {
  uchar in = 0;
  uchar historico[99];
  memset(historico, 0, 99);

  uchar value = 0;

  FILE * logfile = fopen("partidas.txt", "ab");
  if (!logfile) logfile = fopen("partidas.txt", "wb");
  fseek(logfile, 0, SEEK_END);

  FILE * cartf = fopen("carts.bin", "rb");

  int start = 0;
  while (in != 'q') {
    printf(" BINGO - Game\n");
    printf(" ------------------------------------------\n");

    if (value) {
      printf(" A bola sorteada foi %i\n", value);
      fputc(value, logfile);

      int cart_count = 0, equal_count = 0;

      uchar ** cart = Cartela(1);
      uchar jog[GAMER_NAME_SIZE];
      {
        int l = 0;
        int i = 'a'-1;
        fseek(cartf, 0, SEEK_END);
        int cartsize = ftell(cartf);
        fseek(cartf, 0, SEEK_SET);

        while ((l = openCartela(cartf, jog, cart)) && l+(25+GAMER_NAME_SIZE) <= cartsize) {
          const char * c = (const char *)*cart;
          if (strchr(c, value)) cart_count ++;

          equal_count = 0;
          fseek(logfile, start, SEEK_SET);
          for (int i = 0; i < 25; i++) {
            uchar lfc = fgetc(logfile);
            if (strchr(c, lfc)) equal_count ++;
          }

          if (equal_count == 25) break;
        }
      }
      if (cart_count)
        printf(" Ela está em pelo menos %i cartelas \n", cart_count);
      if (equal_count == 25) {
        printf(" BINGOOO!! o jogador %s ganhou com a cartela: \n", jog);
        PrintCartela(cart);
        fputc('\n', logfile);
        break;
      }

      value = 0;

      start++;

      printf(" qualquer tecla - Sortea nova bola\n");
      printf(" q - Sair do jogo\n");
      printf(" ------------------------------------------\n");
      printf(" \n");
      printf(":");
      in = getchar();
      printf("%c:", in);
      if (in == 'q') break;

    }

    while (strchr((const char*)historico, value))
      value = Randchar(1, 99);

    historico[strlen(historico)-1] = value;
  }

  fputc('\n', logfile);
  fclose(logfile);
  fclose(cartf);

  puts("Joao");
  return '0';
}
