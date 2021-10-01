#include <stdio.h>

typedef unsigned char byte;

int abraCartela(
 FILE * file,
 const byte ** cartela,
 const int jogador_id,
 const int cart_id
);

int salveCartela(
 FILE * file,
 const byte ** cartela,
 const int jogador_id,
 const int cart_id 
);

void mostreTitulo(const char * title);
void mostreCartela(const char ** cartela);
void mostreLinha();

byte sortiar(char inicio, char limite);
void popule(byte ** c);

void ordene(byte * vet, byte n);

byte ** Cartela();
byte * Jogador();
