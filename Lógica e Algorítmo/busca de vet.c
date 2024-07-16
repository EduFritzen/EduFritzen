#include <stdio.h>
#include <stdlib.h>

int main(){
    int v[10], valor, i;
    for(i=0;i<10;i++){
        printf("Digite a nota do aluno%d: ", i);
        scanf("%d", &v[i]);
    }
    printf("Digite a nota de um aluno: ");
    scanf("%d", &valor);
    for(i=0;i<10;i++){
        if(valor==v[i]){
            break;
        }
    }
    if(i<10){
        printf("Posicao do vetor: %d", i);
    }
    else{
        printf("Posicao do vetor: -1");
    }
    return 0;
}




















