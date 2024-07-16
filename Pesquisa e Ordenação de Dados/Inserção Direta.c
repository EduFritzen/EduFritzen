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

void ins_dir(int *vet, int tam){
  int i, j, it=0;
  if(tam<=1){
    return;
  }
  for(int j=1;j<tam;j++){
    i=j-1;
    while(i>=0 && vet[i]>vet[j]){
      troca(&vet[i],&vet[j]);
      i--;
      j--;
    }
  }
}

int main(){
  int x[5]={4,6,6,3,2};
  imprime_vetor(x, 5);
  ins_dir(x, 5);
  imprime_vetor(x, 5);
}