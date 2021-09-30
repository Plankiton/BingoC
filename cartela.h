#include <stdio.h>
#define GAMER_NAME_SIZE 20

typedef unsigned char uchar;
char Casa(char **);
void PrintCartela(char [5][5]);
uchar Randchar(char, char);
uchar ** Cartela(uchar);
void troca(uchar *, uchar *);
void OrgVet(uchar *, uchar n);

int saveCartela(FILE * file, const char *, const uchar **);
