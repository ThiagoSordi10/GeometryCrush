/*
Arquivo respons�vel pela l�gica do jogo, manipula��o da matriz pe�as, forma��o de pe�as,
pontuador, etc.
*/

#include "game.h"
#define TAM_TAB 9

// modificar o tipo das pe�as que formam combina��o e um time sleep
int gera_tipo(){
    return (rand() % 9);
}

//vai "Puxando" os elementos de cima da pe�a at� chegar na primeira linha e gerar uma pe�a nova
void copia_acima(peca_t (*pecas)[TAM_TAB], int i_1, int i_2, int j){
    if(i_2>=0){
            printf("----%d", i_2-1);
        pecas[i_1][j].tipo = pecas[i_2][j].tipo;
        copia_acima(pecas, i_2, i_2-1, j);
    }else{
        pecas[0][j].tipo = gera_tipo();
    }
}

//fun��o que realmente realiza as combina��es
void realiza_combinacao(peca_t (*pecas)[TAM_TAB]){
    for(int i=0; i<TAM_TAB; i++){
		for(int j=0; j<TAM_TAB; j++){
                if(pecas[i][j].remocao == 1){
                    copia_acima(pecas, i, i-1, j);
                    pontuacao++;
                    pecas[i][j].remocao = 0;
                    i=0;
                    j=0;
                }
		}
    }
}

//verifica combina��es na horizontal
int verifica_horizontal(peca_t (*pecas)[TAM_TAB]){
	int sequencia=0, ocorrencia=0;
	for(int i=0; i<TAM_TAB; i++){
		for(int j=0; j<TAM_TAB; j++){
			if(pecas[i][j].tipo == pecas[i][j+1].tipo && j<8){ //vai somando as sequencias
				sequencia++;
			}else{ //quando nao tem mais sequencia
				if(sequencia >= 2){ //verifica se h� pelo menos tres em sequencia
				    for(int z=sequencia; z>=0; z--){
				        pecas[i][j-z].remocao = 1; //armazena todas pe�as que devem ser removidas (pertencentes a combina��o)
				    }
				    ocorrencia = 1;
				}
				sequencia=0;
			}
		}
		sequencia=0;
	}
	return ocorrencia;
}

//verifica combina��es na vetical
int verifica_vertical(peca_t (*pecas)[TAM_TAB]){
	printf("\n");
	int sequencia=0, ocorrencia=0;
	for(int j=0; j<TAM_TAB; j++){
		for(int i=0; i<TAM_TAB; i++){
			if(pecas[i][j].tipo == pecas[i+1][j].tipo && i<8){ //vai somando as sequencias
				sequencia++;
			}else{ //quando nao tem mais sequencia
				if(sequencia >= 2){ //verifica se h� pelo menos tres em sequencia
                        for(int z=sequencia; z>=0; z--){
                            pecas[i-z][j].remocao = 1; //armazena todas pe�as que devem ser removidas (pertencentes a combina��o)
                        }
                        ocorrencia = 1;
				}
				sequencia=0;
			}
		}
		sequencia=0;
	}
	return ocorrencia;
}

//No ato do clique, verifica-se se h� alguma pe�a que abrange as coordenadas clicadas, se houver � retornada sua posi��o na matriz
coord_t procura_tipo(peca_t (*pecas)[TAM_TAB], int x, int y){
    coord_t coord;
    for(int i=0; i<TAM_TAB; i++){
        for(int j=0; j<TAM_TAB; j++){
            if(pecas[i][j].posX >= x-25 && pecas[i][j].posX <= x+25 && pecas[i][j].posY >= y-25 && pecas[i][j].posY <= y+25){
                coord.linha = i;
                coord.coluna = j;
                return coord;
            }
        }
    }
    coord.linha = -1;
    coord.coluna = -1;
    return coord;
}

//Faz a troca entre pe�as (s� os tipos s�o trocados)
void troca(peca_t (*pecas)[TAM_TAB], coord_t coord_1, coord_t coord_2){
	int aux;
	aux = pecas[coord_1.linha][coord_1.coluna].tipo;
	pecas[coord_1.linha][coord_1.coluna].tipo = pecas[coord_2.linha][coord_2.coluna].tipo;
	pecas[coord_2.linha][coord_2.coluna].tipo = aux;
}

//verifica se s�o pe�as pr�ximas
int verifica_valores_posicao(coord_t coord_1, coord_t coord_2){
	return (coord_1.linha == coord_2.linha && (coord_1.coluna == coord_2.coluna+1
                                      || coord_1.coluna == coord_2.coluna-1))
                                      || (coord_1.coluna == coord_2.coluna
                                          && (coord_1.linha == coord_2.linha+1
                                              || coord_1.linha == coord_2.linha-1));
}

//Gerencia a troca, se � possivel (elementos pr�ximos ou troca que resulte em combina��o)
int realiza_troca(peca_t (*pecas)[TAM_TAB], coord_t coord_1, coord_t coord_2){
	int movimento=0;
	troca(pecas, coord_1, coord_2); //tenta a troca
	if(verifica_valores_posicao(coord_1, coord_2) == 1){
		if(verifica_horizontal(pecas) == 1 ||
		verifica_vertical(pecas) == 1){ //a troca s� ocorre se for uma jogada de valor
			return 1;
		}else{
            printf("Falta combina��es");
        }
	}else{
        printf("Valores longes");
	}

	troca(pecas, coord_1, coord_2); //sen�o � destrocado
	return 0;
}


