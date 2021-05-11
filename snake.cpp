#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "snake.h"

int main(){
    inicializa();
    while(!fimJogo){
        desenha();
        entrada();
        logica();
    }
    finaliza();
}

void inicializa(){ //inicializacao do jogo
  //  initscr(); biblioteca ncurses
  //  noecho();
    time_t tempo; 
    fimJogo = 0; //falso
    tamanhoRestoCobra = 0;
    direcao = STOP;
    x = largura/2;
    y = altura/2;
    pontos = 0;
    srand(time(&tempo));
    frutaX = rand()% largura +1;
    frutaY = rand()% altura +1;

    for(int cont = 0; cont < 100; cont++){
        restoCobraX[cont] = 0;
        restoCobraY[cont] = 0; 
    }

}

void desenha(){ //apresentacao da interface para o usuario
   
    // ######...########
    // #               #
    // .               .
    // .               .
    // .               .
    // #               #
    // ######...########

    int coluna, linha, flag = 0;
    system("clear");

    for (coluna = 0; coluna <= largura+2; coluna++){ //imprime a primeira linha
        printf("%c", MURO);
    }

    for (linha = 1; linha <= altura+1; linha++){ //imprime o meio do tabuleiro
        
        printf("\n\r");

        for(coluna = 0; coluna <= largura+2; coluna++){
            if(coluna == 0 || coluna == largura+2){ //se for a primeira ou a ultima coluna, imprime muro
                printf("%c", MURO); 
            }else if(coluna == x && linha == y){ //cabeça cobra
                printf("%c", COBR);
            }else if(coluna == frutaX && linha == frutaY){ //a fruta
                printf("%c", FRUT);
            }else{
                for(int cont = 0; cont <tamanhoRestoCobra; cont++){
                    if(restoCobraX[cont] == coluna && restoCobraY[cont] == linha){ //corpo cobra
                        printf("%c", COBR);
                        flag = 1; //verdadeiro
                    }
                }
                if(flag == 0){
                    printf(" ");
                }
                flag = 0; //falso
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

    char comando;
    
    //comando = wgetch(stdscr);
    comando = getchar();
    //comando = cin.get();

    printf("teste1\n\r");

    switch (comando){
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
        case 'x':
            direcao = 1;
            break;getchar();
        case 'X':
            direcao = 1;
            break; 
    }
}


void logica(){ //executa a logica do jogo

    int restoCobraAnteriorX = restoCobraX[0];
    int restoCobraAnteriorY = restoCobraY[0];
    int auxX, auxY;

    restoCobraX[0] = x;
    restoCobraY[0] = y;

    for(int cont = 0; cont < tamanhoRestoCobra; cont++){
        
        auxX = restoCobraX[cont];
        auxY = restoCobraY[cont];

        restoCobraX[cont] = restoCobraAnteriorX;
        restoCobraY[cont] = restoCobraAnteriorY;

        restoCobraAnteriorX = auxX;
        restoCobraAnteriorY = auxY;
    }

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
        fimJogo = 1; //verdadeiro
    }

    for (int cont = 0; cont < tamanhoRestoCobra; cont++){
        if(restoCobraX[cont] == x && restoCobraY[cont] == y){
            fimJogo = 1; //verdadeiro;
        }
    }

    if(x == frutaX && y == frutaY){
        pontos = pontos + 10;
        frutaX = rand() % largura + 1;
        frutaY = rand() % altura + 1;
        tamanhoRestoCobra++;
    }

}

void finaliza(){ //finalizacao do jogo
    //system("clear");
    printf("\n\n\n\r *** FIM DE JOGO ***\n\n\n\r");
    printf(" Sua pontuação foi: %d\n\n\n\r", pontos);
    //endwin();
}
