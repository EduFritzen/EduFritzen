//EDUARDO ADRIANO FRITZEN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct{ 
    int baralho[12];
    int n_da_maior_carta;
    int proximo_do_baralho;
    int tabuleiro[4][4];
} threes;

void cor_normal(void){ //volta a cor original 
    printf("%c[0m", 27);
}

void muda_cor(int rl, int gl, int bl, int rf, int gf, int bf){ //muda a cor pra (R,G,B)
    printf("%c[38;2;%d;%d;%d;48;2;%d;%d;%dm", 27, rl, gl, bl, rf, gf, bf);
}

int aleatorio_entre(int i, int f){ //gera e retorna um numero aleatorio entre x e y
    int n= i+(rand()%((f-i)+ 1));
    return n;
}

void desenha_tabuleiro(int m[4][4]){ //imprime o tabuleiro 
    printf("\n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(m[i][j]!=0){
                if(m[i][j]==1){
                    muda_cor(0, 0, 250, 0, 0, 0);
                    printf("[%4d]",m[i][j]);  
                    cor_normal();
                }
                else if(m[i][j]==2){
                    muda_cor(250, 0, 0, 0, 0, 0);
                    printf("[%4d]",m[i][j]);  
                    cor_normal();
                }                
                else{
                    printf("[%4d]",m[i][j]);
                }
            }
            else{
                printf("[    ]");
            }
        }
        printf("\n");
    }
}

void zera_matriz(int tabuleiro[4][4]){ //preenche o tabuleiro com zeros
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tabuleiro[i][j]=0;
        }
    }
}

void cria_baralho(int baralho[12]){ // cria o baralho com os valores iniciais
    for(int i=0;i<4;i++){
        baralho[i]=1;
        baralho[i+4]=2;
        baralho[i+8]=3;
    }
}

void moveW(int m[4][4]){ //executa o movimento para cima(W)
    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if((m[i][j] > 2) && (m[i][j] == m[i-1][j]) || m[i-1][j] == 0){
                m[i-1][j] = m[i-1][j] + m[i][j];
                m[i][j] = 0;
            }
            if(m[i][j] == 2 && m[i-1][j] == 1 || m[i][j] == 1 && m[i-1][j] == 2){
                m[i-1][j] = m[i-1][j] + m[i][j];
                m[i][j] = 0;
            }
        }
    }
}

void moveS(int m[4][4]){ //executa o movimento para baixo(S)
    for(int i = 2; i >= 0; i--){
        for(int j = 3; j >= 0; j--){
            if((m[i][j] > 2) && (m[i][j] == m[i+1][j]) || m[i+1][j] == 0){
                m[i+1][j] = m[i+1][j] + m[i][j];
                m[i][j] = 0;
            }
            if(m[i][j] == 2 && m[i+1][j] == 1 || m[i][j] == 1 && m[i+1][j] == 2){
                m[i+1][j] = m[i+1][j] + m[i][j];
                m[i][j] = 0;
            }
        }
    }
}

void moveA(int m[4][4]){ //executa o movimento para a esquerda(A)
    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){
            if((m[i][j] > 2) && (m[i][j] == m[i][j-1]) || m[i][j-1] == 0){
                m[i][j-1] = m[i][j-1] + m[i][j];
                m[i][j] = 0;
            }
            if(m[i][j] == 2 && m[i][j-1] == 1 || m[i][j] == 1 && m[i][j-1] == 2){
                m[i][j-1] = m[i][j-1] + m[i][j];
                m[i][j] = 0;
            }
        }
    }
}

void moveD(int m[4][4]){ //executa o movimento para a direita(D)
    for(int i = 0; i < 4; i++){
        for(int j = 2; j >= 0; j--){
            if((m[i][j] > 2) && (m[i][j] == m[i][j+1]) || m[i][j+1] == 0){
                m[i][j+1] = m[i][j+1] + m[i][j];
                m[i][j] = 0;
            }
            if(m[i][j] == 2 && m[i][j+1] == 1 || m[i][j] == 1 && m[i][j+1] == 2){
                m[i][j+1] = m[i][j+1] + m[i][j];
                m[i][j] = 0;
            }
        }
    }
}

bool valida_jogo(int m[4][4]){ //percorre o tabuleiro e retorna se ainda existe uma jogada possivel
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(m[i][j]==0){
                return 1;
            }
            else{
                continue;
            }
        }
    }
    return 0;
}

void intro_jogo(){ //mostra o manual do jogo
    char a;
    printf("Ola, bem vindo ao jogo Threes.\nO objetivo do jogo eh combinar cartas para conseguir numeros maiores. \nPara movimentar o tabuleiro, digite w(mover para cima), s(mover para baixo), a(mover para esquerda) e d(mover para direita).\nQuando nao houver mais movimentos possiveis o jogo acaba.\n\nDeseja continuar? (s ou n) ");
    scanf(" %c", &a);
    if(a=='n'){
        exit(0);
    }
}

int maior_n(int m[4][4]){ //percorre a matriz e retorna o maior N do tabuleiro
    int cont=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(m[i][j]>cont){
                cont=m[i][j];
            }
        }
    }
    cont=log10(cont/3)/log10(2);
    return cont;
}

void troca(int *a, int *b){
    int aux=*a;
    *a=*b;
    *b=aux;
}

void embaralha_vetor(int numero, int jogo[12]){ //embaralha as cartas
    for(int i=0;i<numero;i++){
        int j=aleatorio_entre(0,11);
        if(i!=j){
            troca(&jogo[i],&jogo[j]);
        }
    }
}

int proxima_carta(threes *jogo){ //calcula a proxima carta
  if (jogo->n_da_maior_carta >= 4 && aleatorio_entre(1, 21) == 21) {
    // carta bônus
    return 3*pow(2, aleatorio_entre(1, jogo->n_da_maior_carta-3));
  }
  // carta normal
  if (jogo->proximo_do_baralho == 0) { // o proximo_do_baralho serve como indice do vetor
    // no inicio do baralho -> embaralha
    embaralha_vetor(12, jogo->baralho);
  }
  int carta = jogo->baralho[jogo->proximo_do_baralho];
  jogo->proximo_do_baralho++;
  if (jogo->proximo_do_baralho >= 12) {
    jogo->proximo_do_baralho = 0;
  }
  return carta;
}

void botaCarta(threes *jogo){ //coloca a proxima carta do baralho 
    for(;;){
        int a=aleatorio_entre(0,3);
        int b=aleatorio_entre(0,3);
        if(jogo->tabuleiro[a][b]==0){
            jogo->tabuleiro[a][b] = proxima_carta(jogo);
            break;
        }
        else{
            continue;
        }
    }
}

void cartas_iniciais(int tabuleiro[4][4]){ //coloca as nove cartas iniciais do tabuleiro
    int cont=0;
    while(cont<9){
        int lin = rand() % 4;
        int col = rand() % 4;
        if (tabuleiro[lin][col]==0){
            tabuleiro[lin][col]=aleatorio_entre(1,3);
            cont++;
        }
    }
}

void pontos(int m[4][4]){ //calcula a pontuacao do final da partida
    int aux, ponto=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(m[i][j]==1||m[i][j]==2){
                
            }
            else{
                aux=m[i][j];
                aux=log10(aux/3)/log10(2);
                ponto=ponto+pow(3,aux+1);
            }
        }
    }
    printf("Sua pontuacao eh: %d. Parabens!!!", ponto);
}

char movimento(char jogada){ //pede a jogada para o usuario e se for compativel com wasd, a função retorna a jogada
    do{
    printf("\nMovimento:");
    scanf(" %c", &jogada);
    }while(jogada!='w'&&jogada!='s'&&jogada!='a'&&jogada!='d');
    return jogada;
}

int main()
{
    srand(time(NULL));
    threes jogo;
    jogo.proximo_do_baralho=0;
    zera_matriz(jogo.tabuleiro);
    cria_baralho(jogo.baralho);
    cartas_iniciais(jogo.tabuleiro);
    intro_jogo();
    desenha_tabuleiro(jogo.tabuleiro);
    char jogada;
    do{
        jogo.n_da_maior_carta= maior_n(jogo.tabuleiro);
        jogada=movimento(jogada);
        if(jogada=='w'){
            moveW(jogo.tabuleiro);
        }
        else if(jogada=='s'){
            moveS(jogo.tabuleiro);
        }
        else if(jogada=='a'){
            moveA(jogo.tabuleiro);
        }
        else if(jogada=='d'){
            moveD(jogo.tabuleiro);
        }
        botaCarta(&jogo);
        desenha_tabuleiro(jogo.tabuleiro);
    }while(valida_jogo(jogo.tabuleiro)!=0);
    pontos(jogo.tabuleiro);
    return 0;
}