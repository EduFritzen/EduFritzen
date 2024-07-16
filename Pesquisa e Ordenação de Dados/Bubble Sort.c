#include <stdio.h>

void imprime_vetor(int *vet, int tam){
  for (int i=0; i<tam; i++){
    printf("%i ", vet[i]);
  }
  printf("\n");
}

void troca(int *x, int *y){
  int aux;
  aux = *x;
  *x=*y;
  *y=aux;
}

void bubble_source(int *vet, int tam){
    int flag, j=0;
    do{
        flag = 0;
        for(int i=1;i<tam-j;i++){
            if(vet[i-1]>vet[i]){
                troca(&vet[i-1], &vet[i]);
                flag = 1;
            }
        }
        j++;
    }while(flag==1);
}

int main(){
  int x[6]={4,6,1,3,2,7};
  imprime_vetor(x, 6);
  bubble_source(x, 6);
  imprime_vetor(x, 6);
}