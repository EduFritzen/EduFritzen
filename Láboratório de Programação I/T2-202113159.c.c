//EDUARDO ADRIANO FRITZEN//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char jogo[3][3];
int i, j, contE=0, contVX=0, contVO=0;

void Tabuleiro(){
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            jogo[i][j]=' ';
        }
    }
}

void ImprimirTabuleiro(){
    printf("\n\t 0   1   2\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(j==0){
                printf("\t");
            }
            if(jogo[i][j]=='X'){
                muda_cor(255, 0, 255, 0, 0, 0);
                printf(" %c ", jogo[i][j]);
                cor_normal();
            }
            else{
                muda_cor(218, 165, 32, 0, 0, 0);
                printf(" %c ", jogo[i][j]);
                cor_normal();
            }
            
            if(j<2){
                printf("|");
            }
            if(j==2){
                printf(" %d", i);
            }
        }
        printf("\n\t-----------\n");
    }
}

int GanhouDiagPrin(char c){
    if(jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c){
        return 1;
    }
    else{
        return 0;
    }
}

int GanhouDiagSecun(char c){
    if(jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c){
        return 1;
    }
    else{
        return 0;
    }
}

int GanhouPLinha(char c){
    if((jogo[0][0]== c && jogo[0][1]== c && jogo[0][2]== c)||(jogo[1][0]== c && jogo[1][1]== c && jogo[1][2]== c)||(jogo[2][0]== c && jogo[2][1]== c && jogo[2][2]== c)){
        return 1;
    }
    else{
        return 0;
    }
}

int GanhouPCol(char c){
    if((jogo[0][0]== c && jogo[1][0]== c && jogo[2][0]== c)||(jogo[0][1]== c && jogo[1][1]== c && jogo[2][1]== c)||(jogo[0][2]== c && jogo[1][2]== c && jogo[2][2]== c)){
        return 1;
    }
    else{
        return 0;
    }
}

int Vitoria(char c){
    int vit;
    vit = GanhouDiagPrin(c) + GanhouDiagSecun(c) + GanhouPCol(c) + GanhouPLinha(c);
    return vit;
}

int Validajogada(int i, int j){
    if(i>=0 && i<3 && j>=0 && j<3 && jogo[i][j]== ' '){
        return 1;
    }
    else
        return 0;
}

int jogadas(char j){
    int cord1, cord2;
    printf("Digite a posicao de sua jogada(linhaXcoluna): ");
    scanf("%d%d", &cord1, &cord2);
    while(Validajogada(cord1, cord2)== 0){
        printf("Opcao invalida. \nDigite a posicao de sua jogada(0X0): ");
        scanf("%d%d", &cord1, &cord2);
    }
    jogo[cord1][cord2] = j;
}

int espvazio(){
    int spcvazio;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(jogo[i][j]== ' '){
                spcvazio++;
            }
        }
    }
    return spcvazio;
}

int jogador(){
    srand(time(NULL));
    return rand() % 2;
}

void jogar(){
    int vitX=0, vitO=0, player=jogador();
    if(player==1){
        printf("O jogador X vai começar.");
    }
    else{
        printf("O jogador O vai começar.");
    }
    
    do{
    ImprimirTabuleiro();
    if(player == 1){
        jogadas('X');
        player = 0;
        vitX= vitX + Vitoria('X');
    }
    else{
        jogadas('O');
        player++;
        vitO= vitO + Vitoria('O');
    }
    }while(vitX==0 && vitO==0 && espvazio()!=0);
    ImprimirTabuleiro();

    if(vitX==1){
        printf("\nVitoria do jogador X!");
        contVX++;
    }
    else if(vitO==1){
        printf("\nVitoria do jogador O!");
        contVO++;
    }
    else{
        printf("\nEmpate!");
        contE++;
    }

}

void estatisticas(){
    printf("\nTotal de vitorias de X: %d.", contVX);
    printf("\nTotal de vitorias de O: %d.", contVO);
    printf("\nTotal de empates: %d.", contE);
}

void cor_normal(void){
  printf("%c[0m", 27);
}
void muda_cor(int rl, int gl, int bl, int rf, int gf, int bf){
  printf("%c[38;2;%d;%d;%d;48;2;%d;%d;%dm", 27, rl, gl, bl, rf, gf, bf);
}

int main(){
    char opc;
    printf("Bem vindo ao jogo da velha:\n");
    do{
    Tabuleiro();
    jogar();
    estatisticas();
    printf("\n\nDeseja continuar:(s ou n) ");
    scanf(" %c", &opc);
    }while(opc == 's');
    return 0;
}

