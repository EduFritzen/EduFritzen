#include <stdio.h>
int main(){
    int vetor[5],i, j, aux=0;
    for(i=0;i<5;i++){
        printf("Digite o numero %d do vetor: ", i);
        scanf("%d", &vetor[i]);
    }
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(vetor[i]<vetor[j]){
                aux = vetor[i];
                vetor[i]=vetor[j];
                vetor[j]=aux;
            }
        }
    }
    for (i=0;i<5;i++){
        printf("\nvetor(%d) = %d", i, vetor[i]);
    }


    return 0;
}






















