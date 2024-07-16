int tam=65;
int [] vet = new int [tam];
int step=1;
PFont text;


void setup(){
  size(1200, 600);
  text = createFont("Arial",32,true);
  for(int i = 0; i < tam; i++){
    vet[i] = int(random(5,height));
  }
  frameRate(1);
}

void draw(){
  makeRectangles();
  if(step < tam){
    for (int ini = 0; ini< tam-1; ini = ini + 2*step){
        int meio, fim;
        if(ini+step<tam) 
          meio = ini + step - 1;
        else 
          meio = tam -1;
        
        if(ini+2*step<tam) 
          fim = ini + 2*step - 1;
        else 
          fim = tam -1;
        
        merge(vet, ini, meio, fim);
    }
    step = 2*step;
  }
  else{
    textFont(text,32);
    fill(0);
    text("O VETOR ESTÁ ORDENADO!   :)",20,100);
    noLoop();
  }  
}

void merge(int vet[], int esq, int meio, int dir){ // MergeSort iterativo
      int n1 = meio - esq + 1;
      int n2 = dir - meio;
      int L[] = new int[n1];
      int R[] = new int[n2];
      for (int i = 0; i < n1; i++){
          L[i] = vet[esq + i];
      }
      for (int i = 0; i < n2; i++){
          R[i] = vet[meio + 1+ i];
      }
      int i = 0, j = 0, k = esq;
      while (i < n1 && j < n2){
          if (L[i] <= R[j]){
              vet[k] = L[i];
              i++;
          }
          else{
              vet[k] = R[j];
              j++;
          }
          k++;
      }
      while (i < n1){
          vet[k] = L[i];
          i++;
          k++;
      }
      while (j < n2){
          vet[k] = R[j];
          j++;
          k++;
      }
}

void makeRectangles(){
  background(240);
  int deltaX = width/tam;
  for(int i=0; i<vet.length; i++){
    if(i<step){
      fill(0,255,255);
    }
    else{
      fill(255,255,255);
    }
    rect(i*deltaX, height - vet[i], deltaX, vet[i]); // posx, posy, largura, altura 
  }
}
