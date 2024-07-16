//Eduardo Adriano Fritzen
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double resvalpoli(double a1[12], double var){//calcula o resultado do polinomio
    double y=0;
    for(int i=0; i<=a1[0]; i++){
        y = y + a1[i+1]*pow(var,i);
    }
    return y;
}
void valpoli(){//le o polinomio e o valor de x e recebe o resultado da função acima 
    double poli1[12], x, y;
    printf("Digite o grau do polinomio: ");
    scanf("%lf", &poli1[0]);
    for(int i=0; i<=poli1[0]; i++){
        printf("Digite o valor do coeficiente a%d(x^%d): ", i, i);
        scanf("%lf", &poli1[i+1]);
    } 
    printf("Digite o valor de x: ");
    scanf("%lf", &x);
    y= resvalpoli(poli1,x);
    printf("O resulto do valor do polinomio eh: %.2lf", y);
}

void imprimepoli(double p[12], double p2[12]){//imprime o polinomio
    int n;
    if(p[0]>p2[0]){
        n=p[0];
    }
    else{
        n=p2[0];
    }
    for(int j=0;j<=n;j++){
        printf("(%.2lfx^%d)",p[j+1],j);
        if(j<n){
            printf("+");
        }
    }
}

double somapoli(double a[12],double b[12]){//soma os polinomios
    int i;
    if(a[0]>=b[0] && a[0]<=10 && b[0]<=10){
        for(i=0;i<=b[0];i++){
            a[i+1]=a[i+1]+b[i+1];
        }
        imprimepoli(a,b);
        return true;
    }
    else if(a[0]<b[0] && a[0]<=10 && b[0]<=10){
        for(i=0;i<=a[0];i++){
            a[i+1]=a[i+1]+b[i+1];
        }
        for(i=(a[0]+1);i<=b[0];i++){
            a[i+1]=b[i+1];
        }
        imprimepoli(a,b);       
        return true;
    }
    else{
        return false;
    }
}

double subpoli(double a[12],double b[12]){//subtrai polinomios
    int i;
    if(a[0]>=b[0] && a[0]<=10 && b[0]<=10){
        for(i=0;i<=b[0];i++){
            a[i+1]=a[i+1]-b[i+1];
        }
        imprimepoli(a,b);
        return true;
    }
    else if(a[0]<b[0] && a[0]<=10 && b[0]<=10){
        for(i=0;i<=a[0];i++){
            a[i+1]=a[i+1]-b[i+1];
        }
        for(i=(a[0]+1);i<=b[0];i++){
            a[i+1]=-b[i+1];
        }
        imprimepoli(a,b);        
        return true;
    }
    else{
        return false;
    }
}

double multipoli(double a[12],double b[12]){//multiplica os polinomios
    if((a[0]+b[0])>10){
        return false;
    }
    double aux[12],soma[12];
    int i, j, gA, gB;
    for(i=0;i<12;i++){
        soma[i]=0;
    }
    gA=a[0]+1;
    gB=b[0]+1;
    for(i=1;i<=gA;i++){
        for(j=1;j<=gB;j++){
            if((i+j)==2){
                aux[1]=a[i]*b[j];
            }
            else if((i+j)==3){
                aux[2]=(a[i]*b[j])+soma[2];
                soma[2]=aux[2];
            }
            else if((i+j)==4){
                aux[3]=(a[i]*b[j])+soma[3];
                soma[3]=aux[3];          
            }
            else if((i+j)==5){
                aux[4]=(a[i]*b[j])+soma[4];
                soma[4]=aux[4];           
            }
            else if((i+j)==6){
                aux[5]=(a[i]*b[j])+soma[5];
                soma[5]=aux[5];
            }
            else if((i+j)==7){
                aux[6]=(a[i]*b[j])+soma[6];
                soma[6]=aux[6];
            }
            else if((i+j)==8){
                aux[7]=(a[i]*b[j])+soma[7];
                soma[7]=aux[7];
            }
            else if((i+j)==9){
                aux[8]=(a[i]*b[j])+soma[8];
                soma[8]=aux[8];
            }
            else if((i+j)==10){
                aux[9]=(a[i]*b[j])+soma[9];
                soma[9]=aux[9];
            }
            else if((i+j)==11){
                aux[10]=(a[i]*b[j])+soma[10];
                soma[10]=aux[10];
            }
            else if((i+j)==12){
                aux[11]=(a[i]*b[j])+soma[11];
                soma[11]=aux[11];
            }            
        }
    }
    for(j=0;j<=(a[0]+b[0]);j++){
        a[j+1]=aux[j+1];
        printf("(%.2lfx^%d)",a[j+1],j);
        if(j<(a[0]+b[0])){
            printf("+");
        }
    }
    return true;
}

void somasubmultpoli(int r){//le os dois polinomios e escolhe entre as tres operações e retorna se foi possivel realizar a operação
    double poli1[12], poli2[12];
    int res;
    printf("Digite o grau do polinomio: ");
    scanf("%lf", &poli1[0]);
    for(int i=0; i<=poli1[0]; i++){
        printf("Digite o valor do coeficiente a%d(x^%d): ", i, i);
        scanf("%lf", &poli1[i+1]);
    }    
    printf("Digite o grau do segundo polinomio: ");
    scanf("%lf", &poli2[0]);
    for(int i=0; i<=poli2[0]; i++){
        printf("Digite o valor do coeficiente a%d(x^%d) do segundo polinomio: ", i, i);
        scanf("%lf", &poli2[i+1]);
    }
    if(r==1){
        res= somapoli(poli1,poli2);
    }
    else if(r==2){
        res= subpoli(poli1,poli2);
    }
    else if(r==3){
        res= multipoli(poli1,poli2);
    }
    if(res==0){
        printf("\nNao eh possivel fazer a operacao.");
    }
    else{
        printf("\nOperacao feita com sucesso.");
    }
}

int escolheopc(){//faz o usuario escolher entre as 4 funções
    int r;
    printf("Ola, bem-vindo ao programa. Essa eh a calculadora de polinomios.\nPara escrever uma funcao e atribuir valor a variavel, digite 0.\nPara a soma(1),subtracao(2) ou multiplicacao(3) de dois polinomios. ");
    scanf("%d", &r);
    return r;
}

int main(){
    int res= escolheopc();
    if(res==0){
        valpoli();
    }
    else if(res>=1 && res<=3){
        somasubmultpoli(res);
    }
    else{
        printf("Opcao invalida.");
    }
    return 0;
}