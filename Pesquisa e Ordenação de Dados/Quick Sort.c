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

int part(int *vet, int ini, int fim){
    int pivot = vet[ini];
    int i=ini;
    int j=fim;
    do{
        while(vet[i]<pivot && i<=j){
            i++;
        }
        while(vet[j]>pivot && j>=i){
            j--;
        }
        troca(&vet[i],&vet[j]);
    }while(i<j);
    
    return(i);
}

void quick_sort(int *vet, int ini, int fim){
    if(ini>=fim){
        return;
    }
    int pos=part(vet,ini,fim);

    quick_sort(vet,ini,pos-1);
    quick_sort(vet,pos+1,fim);
}

int main(){
  int x[8]={4,7,3,5,2,6,8,0};
  imprime_vetor(x, 8);
  quick_sort(x, 0, 7);
  imprime_vetor(x, 8);
}