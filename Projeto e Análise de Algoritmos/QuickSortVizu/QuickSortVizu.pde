int tam=65;
int [] vet = new int [tam];
PFont text;
int top;
int ini=0;
int fim;
int [] pilha;

void setup(){
  size(1200, 600);
  text = createFont("Arial",32,true);
  for(int i = 0; i < tam; i++){
    vet[i] = int(random(5,height));
  }
  ini = 0;
  fim = vet.length-1;
  pilha= new int[fim - ini + 1];
  top = -1;
  pilha[++top] = ini;
  pilha[++top] = fim;
  frameRate(10);
}

void draw(){
  makeRectangles();
  if(top >= 0){
    fim = pilha[top--];
    ini = pilha[top--];
     int prt = particiona(vet, ini, fim);
     if (prt  - 1 > ini) {
        pilha[++top] = ini;
        pilha[++top] = prt  - 1;
    }
    if (prt  + 1 < fim) {
        pilha[++top] = prt  + 1;
        pilha[++top] = fim;
    }
  }
  else{
    textFont(text,32);
    fill(0);
    text("O VETOR ESTÁ ORDENADO!   :)",20,100);
    noLoop();
  }  
}

int particiona(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) 
    {
      if (arr[j] <= pivot) 
      {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void makeRectangles(){
  background(240);
  int deltaX = width/tam;
  for(int i=0; i<vet.length; i++){
    if(i<fim){
      fill(0,255,255);
    }
    else{
      fill(255,255,255);
    }
    rect(i*deltaX, height - vet[i], deltaX, vet[i]); // posx, posy, largura, altura 
  }
}
