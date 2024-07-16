#include <stdio.h>
int main(){
    int t, i, j, soma=0;
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &t);
    int matriz[t][t];
    for(i=0;i<t;i++){
        for(j=0;j<t;j++){
            printf("Digite um valor para a matriz [%d][%d] ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    for(i=0;i<t;i++){
        for(j=0;j<t;j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    for(i=0;i<t;i++){

        soma = soma + matriz[i][i];
    }
    if(soma>10){
        for(i=0;i<t;i++){
            printf("%d ", matriz[i][i]);
        }
    }
}




















