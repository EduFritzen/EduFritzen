int [] vet;
int [] pilha;
int top;
int ini;
int fim;
int n=65;

void setup()
{
  size(1000, 800);
  colorMode(RGB,255);
  frameRate(24);  
  vet = new int[n];
  for(int i = 0; i < vet.length; i++)
  {
    vet[i] = int(random(height));
  }
  ini = 0;
  fim = vet.length-1;
  pilha= new int[fim - ini + 1];
  top = -1;
  pilha[++top] = ini;
  pilha[++top] = fim;
}
void draw()
{
  background(0);
  int deltaX = width/n;
   for(int i=0; i < vet.length; i++){
    if(i<fim){
      fill(95,158,160); 
    }
    else{
      fill(60,179,0);
    }
    rect(i*deltaX, height - vet[i], deltaX, vet[i]); 
  }  
  if(top >= 0) 
  {
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
  else
  {
    noLoop();
  }
}

int particiona(int arr[], int low, int high)
{
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
