//Arquivo cabeçalho, *livraria local
#ifndef SNAKE_HEADER_
#define SNAKE_HEADER_

#define STOP 0
#define ESQD 1
#define DIRT 2
#define CIMA 3
#define BAIX 4

#define MURO '#' 
#define COBR 'O' 
#define FRUT '@' 

const int largura = 20;
const int altura = 20;

int fimJogo;
int x, y, frutaX, frutaY, pontos, direcao;
int restoCobraX[100], restoCobraY[100];
int tamanhoRestoCobra;

void inicializa();
void desenha();
void entrada();
void logica();
void finaliza();

#endif
