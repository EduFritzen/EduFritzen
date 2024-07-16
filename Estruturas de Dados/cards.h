#ifndef CARDS_H

#define TAM_DEQUE	52
#define SEMENTE		1
#define VALOR		0
#define	NAIPE		1
#define MAO		5

typedef enum {OUROS, ESPADAS, COPAS, BASTOS} NAIPES_T;

/* tipo a ser usado para a fila correspondente a mao do usuario */
typedef struct n {
	int valor;
	int naipe;
} CARTA_T;

void imprimeBaralhoVetor(int cartas[][2]);
void criaBaralho(int cartas[][2]);
void embaralha(int cartas[][2], unsigned int semente);
int contaPontos(CARTA_T *mao);


#define CARDS_H
#endif
