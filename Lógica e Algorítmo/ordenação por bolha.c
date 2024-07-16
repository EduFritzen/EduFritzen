#include <stdio.h>
int main(){
    int vetor[5],i, j, aux=0;
    for(i=0;i<5;i++){
        printf("Digite o numero %d do vetor: ", i);
        scanf("%d", &vetor[i]);
    }
    for(i=1;i<5;i++){
        for(j=0;j<5-1;j++){
            if(vetor[j]>vetor[j+1]){
                aux = vetor[j];
                vetor[j]=vetor[j+1];
                vetor[j+1]=aux;
            }
        }
    }
    for (i=0;i<5;i++){
        printf("\nvetor(%d) = %d", i, vetor[i]);
    }


    return 0;
}






















