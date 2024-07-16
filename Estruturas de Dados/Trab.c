#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

void tutorial(){
    printf("Poker Square é um jogo de cartas, a cada rodada o jogador recebe 5 cartas e\nprecisa coloca-las em um tabuleiro 5x5. Depois da quinta rodada, haverá uma\nrodada bônus onde o jogador poderá, se quiser, trocar de posição duas cartas. \nAo acabar as jogadas, será contado a pontuação considerando linhas, \ncolunas e diagonais(principal e secundária).\n");
}

void carta_mao(int cartas[][2], CARTA_T mao[5], int j){
    int i;
    for(i=0;i<5;i++){
        mao[i].valor= cartas[j][0];
        mao[i].naipe= cartas[j][1];
        j++;    
    }
    return;
}

void imprime_mao(CARTA_T mao[5]){
    int i;
    printf("Sua mao:\n");
    for(i=0;i<5;i++){
        printf(" %i %i  | ", mao[i].valor, mao[i].naipe);
    }
    printf("\n\n");
    return;
}

void zera_matriz(CARTA_T tab[5][5]){
    int i, j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            tab[i][j].valor=0;
            tab[i][j].naipe=0;
        }
    }
    return;
}

void imprime_matriz(CARTA_T tab[5][5]){
    int i, j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(tab[i][j].valor==0){
                printf("[     ]");
            }
            else{
                printf("[%2i %2i]", tab[i][j].valor, tab[i][j].naipe);
            }    
        }
        printf("\n");
    }
    printf("\n");
    return;    
}

void rodada(int j){
    if(j==0){
        printf("Primeira rodada:\n");
    }
    else if(j==5){
        printf("Segunda rodada:\n");    
    }
    else if(j==10){
        printf("Terceira rodada:\n");    
    }
    else if(j==15){
        printf("Quarta rodada:\n");    
    }
    else if(j==20){
        printf("Quinta rodada:\n");    
    }
}

void coloca_carta(CARTA_T mao[5], CARTA_T tab[5][5]){
    int i, j, aux=0;
    while(aux<5){
        imprime_mao(mao);
        inicio:
        printf("Digite a posicao para a carta %d de sua mao(x y): ", aux);
        scanf(" %d %d", &i, &j);
        if(tab[i][j].valor==0 && i<5 && j<5){
            tab[i][j].valor=mao[aux].valor;
            tab[i][j].naipe=mao[aux].naipe;
        }
        else{
            printf("\nPosicao invalida.\n");
            goto inicio;    
        }
        imprime_matriz(tab);
        aux++;
    }
    return;
}

void troca(CARTA_T tab[5][5]){
    int a, b, c, d, auxv, auxn, i;
    char p;
    aqui:
    printf("Deseja realizar as duas trocas de cartas?(s/n) ");
    scanf(" %c", &p);
    if(p=='n'||p=='N'){
        return;
    }
    else if(p!='n'&&p!='s'){
        printf("Opção inválida.");
        goto aqui;
    }
    for(i=0;i<2;i++){
        printf("\nDigite as duas posições para a troca(x y)(k l): ");
        scanf(" %d %d %d %d", &a, &b, &c, &d);
        auxv=tab[a][b].valor;
        auxn=tab[a][b].naipe;
        tab[a][b].valor=(tab[c][d].valor);
        tab[a][b].naipe=(tab[c][d].naipe);
        tab[c][d].valor=auxv;
        tab[c][d].naipe=auxn;
        imprime_matriz(tab);
    }
    return;
}

void preenche_mao(CARTA_T mao[5], CARTA_T tab[5][5], int k, int opc){
    int i;
    if(opc==0){
        for(i=0;i<5;i++){
        mao[i].valor=tab[i][k].valor;
        mao[i].naipe=tab[i][k].naipe;
        }
    }
    else if(opc==1){
        for(i=0;i<5;i++){
        mao[i].valor=tab[k][i].valor;
        mao[i].naipe=tab[k][i].naipe;
        }        
    }
    else if(opc==2){
        for(i=0;i<5;i++){
        mao[i].valor=tab[i][i].valor;
        mao[i].naipe=tab[i][i].naipe;
        }
    }
    else if(opc==3){
        for(i=0;i<5;i++){
        mao[i].valor=tab[i][4-i].valor;
        mao[i].naipe=tab[i][4-i].naipe;
        }
    }
}

void ordena_vet(CARTA_T mao[5]){
    int i, j, auxv, auxn;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(mao[i].valor > mao[j].valor){
                auxv= mao[i].valor;
                mao[i].valor= mao[j].valor;
                mao[j].valor= auxv;
                auxn= mao[i].naipe;
                mao[i].naipe= mao[j].naipe;
                mao[j].naipe= auxn;
            }
        }
    }
}

int pontos(CARTA_T *mao, CARTA_T tab[5][5]){
    int pontos=0, i, j;
    for(i=0;i<2;i++){
        for(j=0;j<5;j++){
            preenche_mao(mao, tab, j, i);
            ordena_vet(mao);
            pontos= pontos + contaPontos(mao);
        }
    }
    for(i=2;i<4;i++){
        preenche_mao(mao, tab, 0, i);
        ordena_vet(mao);
        pontos= pontos + contaPontos(mao);        
    }
    return pontos;    
}

int main(){
	int cartas[TAM_DEQUE][2], j=0, pontuacao, a;
    printf("Digite um valor para a semente:" );
    scanf("%d", &a);
	CARTA_T mao[5], tab[5][5];
    tutorial();
	criaBaralho(cartas);
	embaralha(cartas, a);
    zera_matriz(tab);
    while(j<25){
        carta_mao(cartas, mao, j);
        imprime_matriz(tab);
        rodada(j);
        coloca_carta(mao, tab);
        j=j+5;
    }
    troca(tab);
    pontuacao= pontos(mao, tab);
	printf("Sua pontuação é de: %d!!! pontos.\n", pontuacao);
	exit(0);
}