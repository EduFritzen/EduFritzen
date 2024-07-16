#include <iostream>
#include <string.h>
using namespace std;

struct tabuleiro{
    int **tab {nullptr};
    char **tabC {nullptr};
};

void aloca_tabchar(tabuleiro* tabI, int tam){
    tabI->tabC = new char*[tam];        
    for(auto i = 0; i < tam; i++){
        tabI->tabC[i] = new char[tam];
    }
}

void aloca_tabint(tabuleiro* tabI, int tam){
    tabI->tab = new int*[tam];        
    for(auto i = 0; i < tam; i++){
        tabI->tab[i] = new int[tam];
    }
    /*for(auto i = 0; i < tam; i++){
        delete[] tabI->tab[i];
    }   
    delete[] tabI->tab;*/
}

void preencheTab(tabuleiro* tabI, int tam){
    char str[tam+1];
    for(int i=0;i<tam;i++){
        cin >> str;
        for(int j=0;j<tam;j++){
            tabI->tabC[i][j]=str[j];
        }    
    }    
}

void transCharInt(tabuleiro* tabI, int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            if(tabI->tabC[i][j]=='.'){
                tabI->tab[i][j]=0;
            }
            else{
                tabI->tab[i][j]=999;
            }
        }
    }
}

int Cordenada_valida(int i, int j, int tam){
    if(i>=0 && i<tam && j>=0 && j<tam){
        return 1;
    }
    else{
        return 0;
    }
}

void calculabomba(tabuleiro* tabI, int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            if(Cordenada_valida(i-1,j,tam) && tabI->tab[i-1][j]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;    
            }
            if(Cordenada_valida(i+1,j,tam) && tabI->tab[i+1][j]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;    
            }
            if(Cordenada_valida(i,j-1,tam) && tabI->tab[i][j-1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;    
            }
            if(Cordenada_valida(i,j+1,tam) && tabI->tab[i][j+1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;    
            }
            if(Cordenada_valida(i-1,j-1,tam) && tabI->tab[i-1][j-1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;   
            }
            if(Cordenada_valida(i+1,j+1,tam) && tabI->tab[i+1][j+1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;   
            }
            if(Cordenada_valida(i-1,j+1,tam) && tabI->tab[i-1][j+1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;   
            }
            if(Cordenada_valida(i+1,j-1,tam) && tabI->tab[i+1][j-1]==999 && tabI->tab[i][j]!=999){
                tabI->tab[i][j]=tabI->tab[i][j]+1;   
            }
        }
    }
}

void imprimeTab(tabuleiro* tabI, int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            if(tabI->tab[i][j]==999){
                cout << "*";
            }
            else{
                cout<< tabI->tab[i][j];
            }
        }
        cout<<"\n";
    } 
}

int main()
{
    tabuleiro tabI;
    int tam;
    cin >> tam;
    aloca_tabchar(&tabI, tam);
    aloca_tabint(&tabI, tam);
    preencheTab(&tabI, tam);
    transCharInt(&tabI, tam);
    calculabomba(&tabI, tam);
    imprimeTab(&tabI, tam);
    for(auto i = 0; i < tam; i++){
        delete[] tabI.tabC[i];
        delete[] tabI.tab[i];

    }   
    delete[] tabI.tab; 
    delete[] tabI.tabC;    
    return 0;
}