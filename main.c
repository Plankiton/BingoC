#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bingo.h"


FILE * ijogadorf,
  * icartelaf,
  * ocartelaf,
  * ojogadorf;

int i;
byte in,
  menu = '0',
  ** cartela,
  jogador[20],
  jogador[20],
  bol_history[99];

int main(int argc, char *argv[])
{

  ocartelaf = fopen("carts.bin", "wb");
  ojogadorf = fopen("jogadors.txt", "wb");
  cartela = Cartela(1);

  while (in != 'q') {
    system("clear");
    ocartelaf = fopen("carts.bin", "ab");
    icartelaf = fopen("carts.bin", "rb");
    ojogadorf = fopen("jogadors.txt", "ab");
    ijogadorf = fopen("jogadors.txt", "rb");

    switch (menu) {
      case '0':
        printf(" BINGO - Menu Principal\n");
        printf(" ------------------------------------------\n");
        printf(" 1 - Criar cartelaelas\n");
        printf(" 2 - Ver cartelaelas\n");
        printf(" 3 - Atribuir cartelaelas\n");
        printf(" 4 - jogadorar Bingo!\n");
        printf(" q - Sair do jogadoro\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");
        break;
      case '1':
        printf(" BINGO - Criação de cartelaela\n");
        printf(" ------------------------------------------\n");
        if (strlen((char *)jogador) == 0) {
          menu = '3';
          printf(" Voce não tem jogadoradores cadastrados, indo pra tela de criação\n");
          getchar();
          printf(" ------------------------------------------\n");
          continue;
        }

        cartela = Cartela(0);
        mostreCartela((const char**)cartela);
        printf(" \n");
        printf(" s - Salvar cartelaela\n");
        printf(" n - Descartelaar cartela\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogadoro\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");

        in = getchar();
        if (in == '\0' || in == '\n') continue;

        if (in == 's')
          salveCartela(ocartelaf, (const byte **)cartela, (char *)jogador);
        else if (in == 'n')
          menu = '0';
        else {
          i = 'a'-1;
          fseek(ijogadorf, 0, SEEK_SET);
          while (fgets((char *)jogador, 20, ijogadorf))
            if (jogador[0] != '\n')
              if (++i == in) break;

          if (in != i) {
            printf(" erro ao selecionar jogadorador");
          }
        }

        break;
      case '2':
        printf(" BINGO - Cartelas cadastradas\n");
        printf(" ------------------------------------------\n");
        i = 'a'-1;
        fseek(icartelaf, 0, SEEK_END);
        int cartelasize = ftell(icartelaf);

        fseek(icartelaf, 0, SEEK_SET);
        int l = 0;
        while ((l = abraCartela(icartelaf, (const byte **)cartela, (char *)jogador)) && l+(25+20) <= cartelasize) {
          printf(" %c %s \n", ++i, jogador);
          mostreCartela((const char **)cartela);
          printf("\n");
        }

        if (i == 'a'-1)
          printf(" Não há cartelaelas registrados\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogadoro\n");
        printf(" ------------------------------------------\n");
        printf("\n");
        printf(":");
        break;
      case '3':
        printf(" BINGO - jogadoradores\n");
        printf(" ------------------------------------------\n");

        i = 'a'-1;
        fseek(ijogadorf, 0, SEEK_SET);
        while (fgets((char *)jogador, 20, ijogadorf))
          if (jogador[0] != '\n')
            printf(" %c - %s\n", ++i, jogador);

        if (i == 'a'-1)
          printf(" Não há jogadoradores registrados\n");

        printf(" > Escolha um para criar uma cartelaela\n\n");
        printf(" s - Criar jogadorador\n");
        printf(" 0 - Voltar ao menu principal\n");
        printf(" q - Sair do jogadoro\n");
        printf(" ------------------------------------------\n");
        printf(" \n");
        printf(":");

        memset(jogador, 0, 20);
        memset(jogador, 0, 20);

        in = getchar();

        if (in == 's') {
          printf("Digite o nome do jogadorador:");
          scanf("%s", jogador);
          fputs((const char *)jogador, ojogadorf);
          fputc('\n', ojogadorf);
        }
        else if (in == 'n')
          menu = '0';
        else {
          i = 'a'-1;
          fseek(ijogadorf, 0, SEEK_SET);
          while (fgets((char *)jogador, 20, ijogadorf)) 
            if (jogador[0] != '\n')
              if (++i == in)
                break;

          printf(" ------------------------------------------\n");
          printf("Usando jogadorador %s\n", jogador);
          getchar();
          printf(" ------------------------------------------\n");
          menu = '1';
        }

        break;
      case '4':
        in = Bingo();
        break;
    }

    in = getchar();
    if (in == '\0' || in == '\n') continue;

    switch (in) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
        menu = in;
        break;
    }

    fclose(icartelaf);
    fclose(ijogadorf);

    fclose(ocartelaf);
    fclose(ojogadorf);
  }
  return 0;
}
