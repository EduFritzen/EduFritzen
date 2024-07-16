#include <stdio.h>
int main(){
    int num1= 0, num2=0;
    printf(" TRABALHO\n"); 
    printf(" DIGITE O N1: ");
    scanf("%d", &num1);
    printf(" DIGITE O N2: ");
    scanf("%d", &num2);
    int operacao= num1*num1 + num2*num2;
    printf(" A SOMA DOS QUADRADOS DE N1 E N2: ");
    printf("%d", operacao);
    return 0;
}
