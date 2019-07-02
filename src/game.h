#ifndef __GAME__H__
#define __GAME__H__

#include <stdio.h>
#include <stdlib.h>

#include "GL/glut.h"

//struct de controle para coordenadas de centro das peças e o tipo
struct peca{
	int posX;
	int posY;
	int tipo;
	int remocao = 0;
};

//struct para retornar posição de peça na matriz
struct coord{
    int linha;
    int coluna;
};

typedef struct peca peca_t;
typedef struct coord coord_t;

extern int pontuacao;

int gera_tipo();

coord_t procura_tipo(peca_t (*pecas)[9], int x, int y);

void realiza_combinacao(peca_t (*pecas)[9]);

void troca(peca_t (*pecas)[9], coord_t coord_1, coord_t coord_2);

int verifica_valores_posicao(coord_t coord_1, coord_t coord_2);

int realiza_troca(peca_t (*pecas)[9], coord_t coord_1, coord_t coord_2);

int verifica_horizontal(peca_t (*pecas)[9]);
int verifica_vertical(peca_t (*pecas)[9]);

#endif
