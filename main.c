#include <stdio.h>
#include <stdlib.h>
#include "cartela.h"


int main(int argc, char *argv[])
{
  FILE * ocartf = fopen("carts.bin", "wb");
  FILE * ojogf = fopen("jogs.txt", "wb");
  FILE * ijogf;
  FILE * icartf;
  FILE * link;
  FILE * ilink;

  int i;
  uchar ** cur_cart = Cartela(1);
  uchar cur_jog[GAMER_NAME_SIZE];
  uchar jog[GAMER_NAME_SIZE];
  memset(cur_jog, 0, GAMER_NAME_SIZE);
  memset(jog, 0, GAMER_NAME_SIZE);

  uchar in;

  uchar menu = '0', last_menu = '0';
  char jog_sel;
  while (in != 'q') {
    link = fopen("jogcart.bin", "ab");
    ilink = fopen("jogcart.bin", "rb");
    icartf = fopen("carts.bin", "rb");
    ojogf = fopen("jogs.txt", "ab");
    ijogf = fopen("jogs.txt", "rb");

    printf("\n\n");
    switch (menu) {
      case '0':
        printf(" BINGO\n");
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
        if (strlen(cur_jog) == 0) {
          menu = '3';
          continue;
        }

        printf(" ------------------------------------------\n");
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
        menu = '5';
        continue;
        break;
      case '3':
        printf(" ------------------------------------------\n");

        i = 'a'-1;
        fseek(ijogf, 0, SEEK_SET);
        while (fgets(cur_jog, GAMER_NAME_SIZE, ijogf))
          if (cur_jog[0] != '\n')
            printf(" %c - %s\n", ++i, cur_jog);

        if (i == 'a'-1)
          printf(" Não há jogadores registrados\n");

        printf(" s - Criar jogador\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogo\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");
        break;
      case '4':
        break;
      case '5':
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
        if (last_menu != '2')
          printf(" ! Se a cartela já possuir jogador, esta ação não afetará em nada");
        printf(" ------------------------------------------\n");
        printf("\n");
        printf(":");
        break;
    }

    in = getchar();
    if (in == '\0' || in == '\n') continue;

    switch (in) {
      case 's':
        switch (menu) {
          case '1':
            ocartf = fopen("carts.bin", "ab");
            saveCartela(ocartf, cur_jog, cur_cart, 0);
            fclose(ocartf);
            break;
          case '3':
            printf("Digite o nome do jogador:");
            scanf("%s", cur_jog);
            fputs((const char *)cur_jog, ojogf);
            fputc('\n', ojogf);
            puts(cur_jog);
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
              jog_sel = i;
              menu = '5';
            }
            break;
          case '3':
            printf("Usando Usuário %s\n", cur_jog);
            getchar();
            menu = '1';
            break;
        }
    }
    last_menu = menu;

    fclose(icartf);
    fclose(ojogf);
    fclose(ijogf);
    fclose(link);
    fclose(ilink);
  }
  return 0;
}
