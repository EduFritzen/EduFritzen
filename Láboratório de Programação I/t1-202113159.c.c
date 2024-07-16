//Eduardo Adriano Fritzen
#include <stdio.h>
#include <stdlib.h>
//escolakids
int diasdepascoakids(int a){
    int x, y, z, k, w;
    x=a%19;
    y=a%4;
    z=a%7;
    k=(19*x+25)%30;
    w=(2*y+4*z+6*k+5)%7;
    if (k+w+22 > 31){
        return k+w-9;
    }
    else {
        return k+w+22;
    }
}

int mesdepascoakids(int a){
    int x, y, z, k, w;
    x=a%19;
    y=a%4;
    z=a%7;
    k=(19*x+25)%30;
    w=(2*y+4*z+6*k+5)%7;
    if (k+w+22 > 31){
        return 4;
    }
    else {
        return 3;
    }
}
//só matemática
int diadepascoasomat(int A){
    int a,b,c,d,e,m,n,Dia;

    if(A>=1583 && A<=1699){
        m=22;
        n=2;
    }
    else if(A>=1700 && A<=1799){
        m=23;
        n=3;
    }
    else if(A>=1800 && A<=1899){
        m=23;
        n=4;
    }
    else if(A>=1900 && A<=2099){
        m=24;
        n=5;
    }
    else if(A>=2100 && A<=2199){
        m=24;
        n=6;
    }
    a=A%19;
    b=A%4;
    c=A%7;
    d=(19*a+m)%30;
    e=(2*b+4*c+6*d+n)%7;
    if (22+d+e > 31){
        Dia= d+e-9;
    }
    else {
        Dia= 22+d+e;
    }
    if(Dia==26 && 22+d+e>31){
        Dia=19;
    }
    else if(Dia ==25 && d==28 && e==6 && a>10 && 22+d+e>31){
        Dia=18;
    }
    return Dia;
}

int mesdepascoasomat(int A){
    int a,b,c,d,e,m,n;

    if(A>=1583 && A<=1699){
        m=22;
        n=2;
    }
    else if(A>=1700 && A<=1799){
        m=23;
        n=3;
    }
    else if(A>=1800 && A<=1899){
        m=23;
        n=4;
    }
    else if(A>=1900 && A<=2099){
        m=24;
        n=5;
    }
    else if(A>=2100 && A<=2199){
        m=24;
        n=6;
    }
    a=A%19;
    b=A%4;
    c=A%7;
    d=(19*a+m)%30;
    e=(2*b+4*c+6*d+n)%7;
    if (22+d+e > 31){
        return 4;
    }
    else {
        return 3;
    }
}
//ufrgs
int diapascoaufrgs(int A){
    int a,b,c,d,e,x,y, Dia;
    if(A>=1582 && A<=1599){
        x=22;
        y=2;
    }
    else if(A>=1600 && A<=1699){
        x=22;
        y=2;
    }
    else if(A>=1700 && A<=1799){
        x=23;
        y=3;
    }
    else if(A>=1800 && A<=1899){
        x=24;
        y=4;
    }
    else if(A>=1900 && A<=2099){
        x=24;
        y=5;
    }
    else if(A>=2100 && A<=2199){
        x=24;
        y=6;
    }
    else if(A>=2200 && A<=2299){
        x=25;
        y=7;
    }

    a=A%19;
    b=A%4;
    c=A%7;
    d=(19*a+x)%30;
    e=(2*b+4*c+6*d+y)%7;

    if(d+e>9){
        Dia = d+e-9;
    }
    else {
        Dia = d+e+22;
    }
    if(Dia==26 && d+e>9){
        Dia=19;
    }
    else if(Dia==25 && d+e>9 && d==28 && a>10){
        Dia=18;
    }
    return Dia;

}

int mespascoaufrgs(int A){
    int a,b,c,d,e,x,y;
    if(A>=1582 && A<=1599){
        x=22;
        y=2;
    }
    else if(A>=1600 && A<=1699){
        x=22;
        y=2;
    }
    else if(A>=1700 && A<=1799){
        x=23;
        y=3;
    }
    else if(A>=1800 && A<=1899){
        x=24;
        y=4;
    }
    else if(A>=1900 && A<=2099){
        x=24;
        y=5;
    }
    else if(A>=2100 && A<=2199){
        x=24;
        y=6;
    }
    else if(A>=2200 && A<=2299){
        x=25;
        y=7;
    }

    a=A%19;
    b=A%4;
    c=A%7;
    d=(19*a+x)%30;
    e=(2*b+4*c+6*d+y)%7;

    if(d+e>9){
        return 4;
    }
    else {
        return 3;
    }
}
//why do math
int diadepascoamath(int x){
    int a,b,c,d,e,g,h,m,j,k,l,n,p;
    a=x%19;
    b=x/100;
    c=x%100;
    d=b/4;
    e=b%4;
    g=(8*b+13)/25;
    h=(19*a+b-d-g+15)%30;
    m=(a+11*h)/319;
    j=c/4;
    k=c%4;
    l=(2*e+2*j-k-h+m+32)%7;
    n=(h-m+l+90)/25;
    p=(h-m+l+n+19)%32;
    return p;
}

int mesdepascoamath(int x){
    int a,b,c,d,e,g,h,m,j,k,l,n,p;
    a=x%19;
    b=x/100;
    c=x%100;
    d=b/4;
    e=b%4;
    g=(8*b+13)/25;
    h=(19*a+b-d-g+15)%30;
    m=(a+11*h)/319;
    j=c/4;
    k=c%4;
    l=(2*e+2*j-k-h+m+32)%7;
    n=(h-m+l+90)/25;
    p=(h-m+l+n+19)%32;
    return n;
}

int main (){
    int ano, dia1, mes1, dia2, mes2, dia3, mes3, dia4, mes4;
    printf("Digite um ano: ");
    scanf("%d", &ano);
    dia1= diasdepascoakids(ano);
    mes1= mesdepascoakids(ano);
    dia2= diadepascoasomat(ano);
    mes2= mesdepascoamath(ano);
    dia3= diapascoaufrgs(ano);
    mes3= mespascoaufrgs(ano);
    dia4= diadepascoamath(ano);
    mes4= mesdepascoamath(ano);

    printf("\nDe acordo com o quarto metodo: O dia sera %d/%d/%d", dia4, mes4, ano);

    if(dia1==dia4 && mes1==mes4){
        printf ("\nA data do metodo 1 esta igual ao quarto.");
    }
    else{
        printf("\nDe acordo com o primeiro metodo: O dia sera %d/%d/%d ", dia1, mes1, ano);
    }

    if(dia2==dia4 && mes2==mes4){
        printf ("\nA data do metodo 2 esta igual ao quarto.");
    }
    else{
        printf("\nDe acordo com o segundo metodo: O dia sera %d/%d/%d ", dia2, mes2, ano);
    }

    if(dia3==dia4 && mes3==mes4){
        printf ("\nA data do metodo 3 esta igual ao quarto.");
    }
    else{
        printf("\nDe acordo com o terceiro metodo: O dia sera %d/%d/%d ", dia3, mes3, ano);
    }
    return 0;
}
//1988, 1744, 958, 1213.




