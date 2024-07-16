//Eduardo Adriano Fritzen
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct{
    int expo;
    double c;
} monomio;

typedef struct{
    monomio valor[100];
    int quant;
} poli;

double valorpoli(poli p, int x){//calcula o resultado do polinomio
    double y = 0;
    for(int i=0;i<=(p.quant-1);i++){
        y= y + p.valor[i].c*pow(x, p.valor[i].expo);
    }
    return y;
}
void valpoli(){//le o polinomio e o valor de x e recebe o resultado da função acima
    int x;
    poli a;
    printf("Digite uma quantia de monomios: ");
    scanf(" %d", &a.quant);
    for(int i=0;i<=(a.quant-1);i++){
        printf("Digite uma constante para a%d e um expoente para x%d: ", i ,i);
        scanf("%lf %d",&a.valor[i].c,&a.valor[i].expo);

    }
    printf("Digite o valor de x: ");
    scanf(" %d", &x);
    double y=valorpoli(a,x);
    printf("%.2lf", y);    
}

bool somapoli(poli p1, poli p2){
    poli cop2 = p2;
    int f= (p1.quant);
    for(int i=0;i<=(p1.quant-1);i++){
        for(int j=0;j<=(p2.quant-1);j++){
            if(p1.valor[i].expo == p2.valor[j].expo){
                p1.valor[i].c = (p1.valor[i].c) + (p2.valor[j].c);
                cop2.valor[j].c = 0;
            }
        }
    }
    for(int i=0;i<=(p2.quant-1);i++){
        if(cop2.valor[i].c != 0){
            p1.valor[f].expo = cop2.valor[i].expo;
            p1.valor[f].c = cop2.valor[i].c;
            f = f + 1; 
        }
    }
    for(int i=0;i<(f);i++){
        printf("(%.2lfx^%d)",p1.valor[i].c, p1.valor[i].expo);
        if(i<(f-1)){
            printf(" + ");
        }
    }
    p1.quant=f;
    return true;
}

bool subpoli(poli p1, poli p2){
    poli cop2 = p2;
    int f= (p1.quant);
    for(int i=0;i<=(p1.quant-1);i++){
        for(int j=0;j<=(p2.quant-1);j++){
            if(p1.valor[i].expo == p2.valor[j].expo){
                p1.valor[i].c = (p1.valor[i].c) - (p2.valor[j].c);
                cop2.valor[j].c = 0;
            }
        }
    }
    for(int i=0;i<=(p2.quant-1);i++){
        if(cop2.valor[i].c != 0){
            p1.valor[f].expo = cop2.valor[i].expo;
            p1.valor[f].c = -cop2.valor[i].c;
            f = f + 1; 
        }
    }
    for(int i=0;i<(f);i++){
        printf("(%.2lfx^%d)",p1.valor[i].c, p1.valor[i].expo);
        if(i<(f-1)){
            printf(" + ");
        }
    }
    return true;
}   

bool multipoli(poli p1, poli p2){
    if((p1.quant*p2.quant)>100){
        return false;
    }
    poli aux;
    int a=0,k=0;
    for(int i=0;i<=(p1.quant-1);i++){
        for(int j=0;j<=(p2.quant-1);j++){
            aux.valor[a].c= (p1.valor[i].c)*(p2.valor[j].c);
            aux.valor[a].expo =(p1.valor[i].expo)+(p2.valor[j].expo);
            a++;
        }
    }
    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            if(i!=j){
                if(aux.valor[i].expo==aux.valor[j].expo){
                aux.valor[i].c=aux.valor[i].c + aux.valor[j].c;
                aux.valor[j].expo=99;
                }            
            }
        }
    }
    for(int i=0;i<a;i++){
        if(aux.valor[k].expo!=99){
            p1.valor[i].c= aux.valor[k].c;
            p1.valor[i].expo= aux.valor[k].expo;
            k++;
            printf("(%.2lfx^%d)",p1.valor[i].c, p1.valor[i].expo);
            if(i<(a-1)){
                printf(" + ");
            }
        }
        else{
            k++;
            i--;
            a--;
        }
    }
    return true;
}

void somasubmultpoli(int r){
    poli a, b;
    int res;
    printf("Digite uma quantia de monomios: ");
    scanf(" %d", &a.quant);
    for(int i=0;i<=(a.quant-1);i++){
        printf("Digite uma constante para a%d e um expoente para x%d: ", i, i);
        scanf("%lf %d",&a.valor[i].c,&a.valor[i].expo);
    }
    printf("Digite uma quantia de monomios: ");
    scanf(" %d", &b.quant);
    for(int i=0;i<=(b.quant-1);i++){
        printf("Digite uma constante para a%d e um expoente para x%d: ", i, i);
        scanf("%lf %d",&b.valor[i].c,&b.valor[i].expo);
    }
    if(r==1){
        res=somapoli(a,b);
    }
    else if(r==2){
        res=subpoli(a,b);
    }
    else if(r==3){
        res=multipoli(a,b);    
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

int main()
{
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
/*Professor, a minha parte 2 está incompleta. Creio que fiz a estrutura de forma errada, não usei ponteiros nos
polinomios. Para implementar as funções funcionou certinho, mas para fazer a calculadora é impossível sem.
Não dá mais tempo de eu fazer toda a parte 2 do zero, então eu vou enviar assim, pois parte do trabalho está
de forma correta, gostaria de ser parcialmente avaliado por essa parte para não zera-lo.*/