#include <stdio.h>
#include <string.h>
void exercicio(){
    int n, i;
    char msg[50];
    printf("Digite uma mensagem: ");
    scanf("%s", &msg);
    n=strlen(msg);
    for(i=0; i<=n-1; i++){
        if(msg[i]=='a'){
            msg[i]='x';
        }
        if(msg[i]=='e'){
            msg[i]='y';
        }
        if(msg[i]=='i'){
            msg[i]='w';
        }
        if(msg[i]=='o'){
            msg[i]='k';
        }
        if(msg[i]=='u'){
            msg[i]='z';
        }
    }
    printf("%s", msg);
}


void exercicio2(){
    int n, i, soma=0;
    char msg[50];
    printf("Digite uma mensagem: ");
    scanf("%s", &msg);
    n=strlen(msg);
    for(i=0; i<=n-1; i++){
        if(msg[i]=='a'||msg[i]=='e'||msg[i]=='i'||msg[i]=='o'||msg[i]=='u'){
            soma= soma + 1;
        }
    }
    printf("O numero de vogais: %d", soma);
}


int main(){
    int n1, i,j,z,soma=0;
    int matriz[i][j];
    printf("Digite o tamanho da matriz:(n1 x n2) ");
    scanf("%d", &n1);
    for(i=0;i<n1;i++){
        for(j=0;j<n1;j++){
            printf("Matriz[%d][%d]", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    for(z=0;z<n1;z++){
        printf("%d", matriz[z][z]);
    }
    for(z=0;z<n1;z++){
        soma=(soma+matriz[z][z]);
        printf("%d", soma);
    }

}





















