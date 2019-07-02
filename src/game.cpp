/*
Arquivo responsável pela lógica do jogo, manipulação da matriz peças, formação de peças,
pontuador, etc.
*/

#include "game.h"
#define TAM_TAB 9

// modificar o tipo das peças que formam combinação e um time sleep
int gera_tipo(){
    return (rand() % 9);
}

//vai "Puxando" os elementos de cima da peça até chegar na primeira linha e gerar uma peça nova
void copia_acima(peca_t (*pecas)[TAM_TAB], int i_1, int i_2, int j){
    if(i_2>=0){
            printf("----%d", i_2-1);
        pecas[i_1][j].tipo = pecas[i_2][j].tipo;
        copia_acima(pecas, i_2, i_2-1, j);
    }else{
        pecas[0][j].tipo = gera_tipo();
    }
}

//função que realmente realiza as combinações
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

//verifica combinações na horizontal
int verifica_horizontal(peca_t (*pecas)[TAM_TAB]){
	int sequencia=0, ocorrencia=0;
	for(int i=0; i<TAM_TAB; i++){
		for(int j=0; j<TAM_TAB; j++){
			if(pecas[i][j].tipo == pecas[i][j+1].tipo && j<8){ //vai somando as sequencias
				sequencia++;
			}else{ //quando nao tem mais sequencia
				if(sequencia >= 2){ //verifica se há pelo menos tres em sequencia
				    for(int z=sequencia; z>=0; z--){
				        pecas[i][j-z].remocao = 1; //armazena todas peças que devem ser removidas (pertencentes a combinação)
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

//verifica combinações na vetical
int verifica_vertical(peca_t (*pecas)[TAM_TAB]){
	printf("\n");
	int sequencia=0, ocorrencia=0;
	for(int j=0; j<TAM_TAB; j++){
		for(int i=0; i<TAM_TAB; i++){
			if(pecas[i][j].tipo == pecas[i+1][j].tipo && i<8){ //vai somando as sequencias
				sequencia++;
			}else{ //quando nao tem mais sequencia
				if(sequencia >= 2){ //verifica se há pelo menos tres em sequencia
                        for(int z=sequencia; z>=0; z--){
                            pecas[i-z][j].remocao = 1; //armazena todas peças que devem ser removidas (pertencentes a combinação)
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

//No ato do clique, verifica-se se há alguma peça que abrange as coordenadas clicadas, se houver é retornada sua posição na matriz
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

//Faz a troca entre peças (só os tipos são trocados)
void troca(peca_t (*pecas)[TAM_TAB], coord_t coord_1, coord_t coord_2){
	int aux;
	aux = pecas[coord_1.linha][coord_1.coluna].tipo;
	pecas[coord_1.linha][coord_1.coluna].tipo = pecas[coord_2.linha][coord_2.coluna].tipo;
	pecas[coord_2.linha][coord_2.coluna].tipo = aux;
}

//verifica se são peças próximas
int verifica_valores_posicao(coord_t coord_1, coord_t coord_2){
	return (coord_1.linha == coord_2.linha && (coord_1.coluna == coord_2.coluna+1
                                      || coord_1.coluna == coord_2.coluna-1))
                                      || (coord_1.coluna == coord_2.coluna
                                          && (coord_1.linha == coord_2.linha+1
                                              || coord_1.linha == coord_2.linha-1));
}

//Gerencia a troca, se é possivel (elementos próximos ou troca que resulte em combinação)
int realiza_troca(peca_t (*pecas)[TAM_TAB], coord_t coord_1, coord_t coord_2){
	int movimento=0;
	troca(pecas, coord_1, coord_2); //tenta a troca
	if(verifica_valores_posicao(coord_1, coord_2) == 1){
		if(verifica_horizontal(pecas) == 1 ||
		verifica_vertical(pecas) == 1){ //a troca só ocorre se for uma jogada de valor
			return 1;
		}else{
            printf("Falta combinações");
        }
	}else{
        printf("Valores longes");
	}

	troca(pecas, coord_1, coord_2); //senão é destrocado
	return 0;
}


