#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define STOP 0
#define ESQD 1
#define DIRT 2
#define CIMA 3
#define BAIX 4

#define MURO '#' 
#define COBR '(' 
#define FRUT 'O' 

const int largura = 20;
const int altura = 20;

int fimJogo;
int x, y, frutaX, frutaY, pontos, direcao;

void inicializa();
void desenha();
void entrada();
void logica();
void finaliza();


int main(){
    inicializa();
    while(!fimJogo){
        desenha();
        entrada();
        logica();
        printf("again\n\r");
    }
    finaliza();
}

void inicializa(){ //inicializacao do jogo
    initscr(); //biblioteca ncurses
    time_t tempo; 
    fimJogo = 0; //falso
    direcao = STOP;
    x = largura/2;
    y = altura/2;
    pontos = 0;
    srand(time(&tempo));
    frutaX = rand()% largura +1;
    frutaY = rand()% altura +1;
}

void desenha(){ //apresentacao da interface para o usuario
   
    // ######...########
    // #               #
    // .               .
    // .               .
    // .               .
    // #               #
    // ######...########

    int coluna, linha;
    system("clear");

    for (coluna = 0; coluna <= largura+2; coluna++){ //imprime a primeira linha
        printf("%c", MURO);
    }

    for (linha = 1; linha <= altura+1; linha++){ //imprime o meio do tabuleiro
        
        printf("\n\r");

        for(coluna = 0; coluna <= largura+2; coluna++){
            if(coluna == 0 || coluna == largura+2){ //se for a primeira ou a ultima coluna, imprime muro
                printf("%c", MURO); 
            }else if(coluna == x && linha == y){ //a cobra
                printf("%c", COBR);
            }else if(coluna == frutaX && linha == frutaY){ //a fruta
                printf("%c", FRUT);
            }else{
                printf(" ");
            }
        }

    }

    printf("\n\r");

    for (coluna = 0; coluna <= largura+2; coluna++){ //imprime a ultima linha
        printf("%c", MURO);
    }

    printf("\n\n\r pontos = %d\n\r", pontos);


}

void entrada(){ //captura e os dados do usuario

    //w para cima
    //a para esquerda
    //d para a direita
    //s para baixo
    //x para terminar o jogo

    raw();
    noecho();
    keypad(stdscr, true);

    switch (wgetch(stdscr)){
        case 'w':
            direcao = CIMA;
            break;
        case 'W':
            direcao = CIMA;
            break;
        case 'a':
            direcao = ESQD;
            break;
        case 'A':
            direcao = ESQD;
            break;
        case 'd':
            direcao = DIRT;
            break;
        case 'D':
            direcao = DIRT;
            break;
        case 's':
            direcao = BAIX;
            break;
        case 'S':
            direcao = BAIX;
            break;
        /*case 224:
            switch (getchar()){
                case 72:
                    direcao = CIMA;
                    break;
                case 75:
                    direcao = ESQD;
                    break;
                case 77:
                    direcao = DIRT;
                    break;
                case 80:
                    direcao = BAIX;
                    break;
            }
            break/*/
        case KEY_UP:
            direcao = CIMA;
            break;
        case KEY_LEFT:
            direcao = ESQD;
            break;
        case KEY_RIGHT:
            direcao = DIRT;
            break;
        case KEY_DOWN:
            direcao = BAIX;
            break;
        case 'x':
            direcao = 1;
            break;
        case 'X':
            direcao = 1;
            break; 
    }
}


void logica(){ //executa a logica do jogo

    switch (direcao){
        case CIMA:
            y--;
            break;
        case ESQD:
            x--;
            break;
        case DIRT:
            x++;
            break;
        case BAIX:
            y++;
            break;
        case STOP:
            direcao = rand() % 4 +1;
            break; 
    }

    if(x == 0 || x == largura + 2 || y == 0 || y == altura + 2){ //cobra bateu no muro
        fimJogo = 1;
    }

    if(x == frutaX && y == frutaY){
        pontos = pontos + 10;
        frutaX = rand() % largura +1;
        frutaY = rand() % altura + 1;
    }

}

void finaliza(){ //fincalizacao do jogo
    system("clear");
    printf("\n\n\n\r *** FIM DE JOGO ***\n\n\n\r");
    printf(" Sua pontuação foi: %d\n\n\n\r", pontos);
    endwin();
}
