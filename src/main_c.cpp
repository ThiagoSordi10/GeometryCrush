/*
O jogo possui os requisitos:
- Desenho do tabuleiro e peças (de forma randômica)
- Controlador de pontos (cada peça na combinação é um ponto a mais)
- Formação de 3 ou mais peças e remoção das mesmas, com a queda das de cimas em sequência

O arquivo main_c.cpp é responsável pelo inicio do Canvas, desenhando o tabuleiro e peças
*/

#include "GL/glut.h"
#include "GL/freeglut_ext.h" //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "gl_canvas2d.h"
#include "game.h"
#define DIM_TELA 600
#define TAM_TAB 9

//variaveis globais
int clique=0;
coord_t coordnts[2];
int pontuacao=0;
time_t timer1;
time_t timer2;
int iniciar = 0;

peca_t pecas[TAM_TAB][TAM_TAB];
peca_t peca_selecionada;


void jogo(){
    time(&timer2);
    clear(0,0,0);
    char texto[20];

    //Pinta peça selecionada
    color(255, 255, 255);
    rectFill(peca_selecionada.posX-27, peca_selecionada.posY-27, peca_selecionada.posX+27, peca_selecionada.posY+27);

    for(int i=0; i<TAM_TAB;i++){
        for(int j=0; j<TAM_TAB; j++){
            //exibe combinações que foram feitas
            if(pecas[i][j].remocao == 1){
                color(255, 255, 255);
                rectFill(pecas[i][j].posX-27, pecas[i][j].posY-27, pecas[i][j].posX+27, pecas[i][j].posY+27);
            }
            switch(pecas[i][j].tipo){
                case 0:
                   color(0, 0, 200);
                   circleFill(pecas[i][j].posX, pecas[i][j].posY, 25, 90);
                   break;
                case 1:
                   color(200, 0, 0);
                   circleFill(pecas[i][j].posX, pecas[i][j].posY, 25, 90);
                   break;
                case 2:
                   color(0, 200, 0);
                   circleFill(pecas[i][j].posX, pecas[i][j].posY, 25, 90);
                   break;
                case 3:
                    color(0, 0, 200);
                   rectFill(pecas[i][j].posX-25, pecas[i][j].posY-25, pecas[i][j].posX+25, pecas[i][j].posY+25);
                   break;
                case 4:
                    color(200, 0, 0);
                   rectFill(pecas[i][j].posX-25, pecas[i][j].posY-25, pecas[i][j].posX+25, pecas[i][j].posY+25);
                   break;
                case 5:
                    color(0, 200, 0);
                   rectFill(pecas[i][j].posX-25, pecas[i][j].posY-25, pecas[i][j].posX+25, pecas[i][j].posY+25);
                   break;
                case 6:
                    color(0, 0, 200);
                   triangleFill(pecas[i][j].posX, pecas[i][j].posY, 3);
                   break;
                case 7:
                    color(200, 0, 0);
                   triangleFill(pecas[i][j].posX, pecas[i][j].posY, 3);
                   break;
                case 8:
                    color(0, 200, 0);
                   triangleFill(pecas[i][j].posX, pecas[i][j].posY, 3);
                   break;
            }
            //deixa a seleção de combinação um tempo na tela
            if(difftime(timer2, timer1) >= 1.5){
                realiza_combinacao(pecas);
                verifica_horizontal(pecas);
                verifica_vertical(pecas);
                time(&timer1);
            }
            color(10, 10, 10);
            sprintf(texto, "%d", pecas[i][j].tipo);
            text(pecas[i][j].posX, pecas[i][j].posY, texto);
        }
    }
    //exibe textos de detalhes
    color(10, 10, 10);
    sprintf(texto, "Pontuacao: %d", pontuacao);
    text(400, 590, texto);
    text(50, 580, "ESC - sair");
    text(50, 570, "R - resetar");
}

void tela_inicio(){
    clear(0,0,0);
    color(100, 0, 100);
    textInicio(200, 350, "GeometryCrush");
    text(180, 250, "Aperte Enter para iniciar");
    text(180, 230, "ESC para sair");
    text(180, 210, "R para resetar em qualquer momento");
    color(1, 1, 1);
    text(70, 320, "Seu objetivo eh fazer combinacoes de 3 ou mais pecas iguais");
    text(70, 310, "tanto na vertical quanto na horizontal");
}

//Gera o tabuleiro inicial com suas peças
void gera_tabuleiro(){
    int i=0, j=8; //gera novas pecas
    for(int x=60; x<DIM_TELA;x+=60){
        for(int y=60; y<DIM_TELA; y+=60){
            pecas[j][i].posY = y;
            pecas[j][i].posX = x;
            pecas[j][i].tipo = gera_tipo();
            j--;
        }
        i++;
        j=8;
    }
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{
    if(iniciar == 1){
        jogo();
    }else{
        tela_inicio();
    }
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   printf("\nTecla: %d" , key);

   switch(key)
   {
      case 13: //inicia
        if(iniciar == 0){
            iniciar = 1;
        }
        break;
      case 27: //finaliza programa
	     exit(0);
        break;

      case 82: //reset tabuleiro
        gera_tabuleiro();
        break;

	  case 114: //reset tabuleiro
        gera_tabuleiro();
        break;
   }
}
//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou tecla: %d" , key);
}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   y = DIM_TELA - y;

    //caso seja o segundo clique numa peça
   if(clique == 2){
    clique=0;
    realiza_troca(pecas, coordnts[0], coordnts[1]);
    peca_selecionada.posX = -100; //"zera" a peça selecionada
    peca_selecionada.posY = -100;
    time(&timer1);
   }
   if(button == 0 && state == 0){
        coordnts[clique] = procura_tipo(pecas, x, y); //procura a peca clicada
        if(coordnts[clique].linha != -1 && coordnts[clique].coluna != -1){
            peca_selecionada = pecas[coordnts[clique].linha][coordnts[clique].coluna]; //indica peça selecionada
            clique++; //só contabiliza clique se existir peca
        }
   }
}

//primeira jogada é uma analise prévia de combinaççoes no tabuleiro
void primeira_jogada(){
    verifica_horizontal(pecas);
    verifica_vertical(pecas);
    time(&timer1);
}

int main(void)
{
    srand(time(NULL));
   initCanvas(DIM_TELA, DIM_TELA, "GeometryCrush");

   gera_tabuleiro();
    primeira_jogada();
    runCanvas();
}
