#include <stdio.h>
#include <stdlib.h>
#include "cartela.h"

uchar ** cur_cart;

uchar cur_jog[GAMER_NAME_SIZE];
uchar jog[GAMER_NAME_SIZE];
uchar bol_history[99];

FILE * ijogf;
FILE * icartf;
FILE * ocartf;
FILE * ojogf;

int i;
uchar in, menu = '0', last_menu = '0';

int main(int argc, char *argv[])
{
  memset(cur_jog, 0, GAMER_NAME_SIZE);
  memset(jog, 0, GAMER_NAME_SIZE);

  ocartf = fopen("carts.bin", "wb");
  ojogf = fopen("jogs.txt", "wb");
  cur_cart = Cartela(1);

  while (in != 'q') {
    ocartf = fopen("carts.bin", "ab");
    icartf = fopen("carts.bin", "rb");
    ojogf = fopen("jogs.txt", "ab");
    ijogf = fopen("jogs.txt", "rb");

    switch (menu) {
      case '0':
        printf(" BINGO - Menu Principal\n");
        printf(" ------------------------------------------\n");
        printf(" 1 - Criar cartelas\n");
        printf(" 2 - Ver cartelas\n");
        printf(" 3 - Atribuir cartelas\n");
        printf(" 4 - Jogar Bingo!\n");
        printf(" q - Sair do jogo\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");
        break;
      case '1':
        printf(" BINGO - Criação de cartela\n");
        printf(" ------------------------------------------\n");
        if (strlen(cur_jog) == 0) {
          menu = '3';
          printf(" Voce não tem jogadores cadastrados, indo pra tela de criação\n");
          getchar();
          printf(" ------------------------------------------\n");
          continue;
        }

        cur_cart = Cartela(0);
        PrintCartela(cur_cart);
        printf(" \n");
        printf(" s - Salvar cartela\n");
        printf(" n - Descartar cartela\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogo\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");
        break;
      case '2':
        printf(" BINGO - Cartelas cadastradas\n");
        printf(" ------------------------------------------\n");
        i = 'a'-1;
        fseek(icartf, 0, SEEK_END);
        int cartsize = ftell(icartf);

        fseek(icartf, 0, SEEK_SET);
        int l = 0;
        while ((l = openCartela(icartf, jog, cur_cart)) && l+(25+GAMER_NAME_SIZE) <= cartsize) {
          printf(" %c %s \n", ++i, jog);
          PrintCartela(cur_cart);
          printf("\n");
        }

        if (i == 'a'-1)
          printf(" Não há cartelas registrados\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogo\n");
        printf(" ------------------------------------------\n");
        printf("\n");
        printf(":");
        break;
      case '3':
        printf(" BINGO - Jogadores\n");
        printf(" ------------------------------------------\n");

        i = 'a'-1;
        fseek(ijogf, 0, SEEK_SET);
        while (fgets(cur_jog, GAMER_NAME_SIZE, ijogf))
          if (cur_jog[0] != '\n')
            printf(" %c - %s\n", ++i, cur_jog);

        if (i == 'a'-1)
          printf(" Não há jogadores registrados\n");

        printf(" > Escolha um para criar uma cartela");
        printf(" s - Criar jogador\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogo\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");
        break;
      case '4':
        break;
    }

    in = getchar();
    if (in == '\0' || in == '\n') continue;

    switch (in) {
      case 's':
        switch (menu) {
          case '1':
            saveCartela(ocartf, cur_jog, cur_cart, 0);

            memset(cur_jog, 0, GAMER_NAME_SIZE);
            memset(jog, 0, GAMER_NAME_SIZE);
            break;
          case '3':
            memset(cur_jog, 0, GAMER_NAME_SIZE);
            memset(jog, 0, GAMER_NAME_SIZE);
            printf("Digite o nome do jogador:");
            scanf("%s", cur_jog);
            fputs((const char *)cur_jog, ojogf);
            fputc('\n', ojogf);
            break;
        }
        break;

      case 'n':
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
        menu = in;
        break;
      default:
        switch (menu) {
          case '1':
            i = 'a'-1;
            fseek(ijogf, 0, SEEK_SET);
            while (fgets(cur_jog, GAMER_NAME_SIZE, ijogf))
              if (cur_jog[0] != '\n')
                if (++i == in) break;
            if (in != i) {
              printf(" erro ao selecionar jogador");
            } else {
              menu = '5';
            }
            break;
          case '3':
            i = 'a'-1;
            fseek(ijogf, 0, SEEK_SET);
            while (fgets(cur_jog, GAMER_NAME_SIZE, ijogf)) 
              if (cur_jog[0] != '\n')
                if (++i == in)
                  break;

            printf(" ------------------------------------------\n");
            printf("Usando jogador %s\n", cur_jog);
            getchar();
            printf(" ------------------------------------------\n");
            menu = '1';
            break;
        }
    }
    last_menu = menu;

    fclose(icartf);
    fclose(ijogf);

    fclose(ocartf);
    fclose(ojogf);
  }
  return 0;
}
