#include <stdio.h>
#include <stdlib.h>
#include "cards.h"

/* funcao simples para impressão do vetor de baralho */
void imprimeBaralhoVetor(int cartas[][2]){
	int i;
	for(i=0; i<TAM_DEQUE; i++)
		printf("[%i %i]", cartas[i][0], cartas[i][1]);
	return;
}

/* funcao simples que preenche o vetor de baralho com as 52 cartas padrao */
void criaBaralho(int cartas[][2]){	
	long int i, j=0;
	NAIPES_T n;
	/* geracao do baralho ordenado */
	for(n=OUROS; n<=BASTOS; n++){
		for(i=1; i<=13; i++){
			cartas[j][VALOR] = i;
			cartas[j][NAIPE] = n;
			j++;
		}
	}
	return;
}

/* funcao que embaralha as cartas de acordo com uma semente para a funcao srand */
/* OBS: o uso da mesma semente irá gerar embaralhamento igual */
void embaralha(int cartas[][2], unsigned int semente){
	int i, j, aux_v, aux_n;
	/* EMBARALHAMENTO */
	srand(semente);
	for(i=0; i<TAM_DEQUE; i++){
		j = (unsigned long int) rand() % TAM_DEQUE;
		aux_v = cartas[i][VALOR];
		aux_n = cartas[i][NAIPE];
		cartas[i][VALOR] = cartas[j][VALOR];
		cartas[i][NAIPE] = cartas[j][NAIPE];
		cartas[j][VALOR] = aux_v;
		cartas[j][NAIPE] = aux_n;
	}
	return;
}

/* funcao que conta os pontos de uma mao (5 cartas) passada para ela. */
/* OBS: a mao deve estar ordenada por valor ascendente. Naipes não precisam estar ordenados */
int contaPontos(CARTA_T *mao){
	int cont=0, flush=0, straight=0, royalStraight=0;
	int cont2=0, i;

	/* verifica Flush */
	for(i = 0; i < MAO-1; i++){
		if(mao[i].naipe == mao[i+1].naipe)
			cont ++;
	}
	if(cont == 4)
		flush = 1; /* é um flush */

	/* verifica Royal Straight */
	if(mao[0].valor == 1 && mao[1].valor == 10 && mao[2].valor == 11 && mao[3].valor == 12 && mao[4].valor == 13)
		royalStraight = 1; /* é um royal straight */

	if(flush && royalStraight) /* mão é um royal straight flush */
		return 100;

	/* verifica Straight simples */
	for(i=0, cont=0; i < MAO-1; i++){
		if(mao[i].valor == (mao[i+1].valor - 1))
			cont ++;
	}
	if(cont == 4)
		straight = 1; /* é um straight simples */

	if(flush && straight) /* mão é um straight flush */
		return 75;

	if(royalStraight || straight) /* mão é um straight */
		return 15;

	if(flush) /* mão é flush */
		return 20;

	/* verifica pares, trincas e quadras */
	i = cont = cont2 = 0;
	while((i < MAO-1) && (mao[i].valor != mao[i+1].valor))
		i++;
	while((i < MAO-1) && (mao[i].valor == mao[i+1].valor)){
		cont++;
		i++;
	}
	while((i < MAO-1) && (mao[i].valor != mao[i+1].valor))
		i++;
	while((i < MAO-1) && (mao[i].valor == mao[i+1].valor)){
		cont2++;
		i++;
	}
	/* se foi encontrada algum par, trinca, four ou full house, é necessário */
	/* fazer cont e cont2 conter numero correto de cartas iguais encontradas */
	if(cont > 0) /* normalizando valor do primeiro contador */
		cont++;
	if(cont2 > 0) /* normalizando valor do segundo contador */
		cont2++;
	/* após normalizaçao, cont e cont2 podem ser usados para verificacao */
	switch(cont+cont2){
		case 5: /* mão é um full house */
			return 25;
		case 4: /* four ou dois pares */
			if(cont == 4 || cont2 == 4)
				return 50;
			else
				return 5;
		case 3: /* trinca */
			return 10;
		case 2: /* par simples */
			return 2;
	}
	return 0;
}

