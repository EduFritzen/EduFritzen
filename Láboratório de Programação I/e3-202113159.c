#include <stdio.h>
#include <stdlib.h>
int diasqfaltam(int dia, int mes){
    int quantd =360 - (dia + (30 * (mes-1) ) );
    return quantd;
}
int diasqpassaram(int dia, int mes){
    int quantd = dia + (30*(mes-1));
    return quantd;
}

int diasentredatas(int dia1, int mes1, int dia2, int mes2){
    int qdf = diasqfaltam(dia1, mes1);
    int qdp = diasqpassaram(dia2, mes2);
    return qdf+qdp;
}
int main(){
    int dia, mes, ano;

    printf("Digite uma data (dd/mm/aaaa) ");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    int qdp = diasqpassaram(dia, mes);
    printf("Passaram %d dias desde o comeco de %d",qdp, ano);

    int qdf = diasqfaltam (dia, mes);
    printf("\nFaltam %d dias para o fim de %d", qdf, ano);

    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    printf("\n\nDigite uma data (dd/mm/aaaa) ");
    scanf("%d/%d/%d", &dia1, &mes1, &ano1);

    printf("\nDigite uma data (dd/mm/aaaa) ");
    scanf("%d/%d/%d", &dia2, &mes2, &ano2);

    int qde = diasentredatas(dia1, mes1, dia2, mes2);
    printf ("\nEntre os dias %d/%d/%d e %d/%d/%d, existem %d dias", dia1, mes1, ano1, dia2, mes2, ano2, qde);
    return(0);
}
