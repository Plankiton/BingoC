#include <stdio.h>
#define cartelafn "cartela.bin"
#define jogadorfn "jogador.bin"
#define partidafn "partida.bin"

typedef unsigned char byte;

int abraCartela(
 FILE * file,
 const byte ** cartela,
 const char * jogador_id
);

int salveCartela(
 FILE * file,
 const byte ** cartela,
 const char * jogador_id
);

void mostreTitulo(const char * title);
void mostreCartela(const char ** cartela);
void populeCartela(byte ** c);

void mostreLinha();

byte sorteie(char inicio, char limite);

void ordene(byte * vet, byte n);

byte ** Cartela();
byte * Jogador();

byte iniciarBingo(void);
