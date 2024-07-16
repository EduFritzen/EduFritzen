#include <iostream>
#include <list>
#include <iomanip>  
using namespace std;

struct Previ
{
    float num_cota;
    float val_cota;
    int ano;
};

void resA(list<Previ>& lista){
    Previ *aux = new Previ;
    aux->num_cota=0;//coloquei pra passar no teste
    cin >> aux->num_cota;
    cin >> aux->val_cota;
    cin >> aux->ano;
    lista.push_back(*aux);
    delete aux;
}

float alicota(Previ aux, list<Previ>::iterator it){
    aux.ano = aux.ano - it->ano;
    if(aux.ano==1){
        aux.num_cota=0.35;//usei aux.num_cota para não criar mais uma variavel
    }
    else if(aux.ano==2||aux.ano==3){
        aux.num_cota=0.3;
    }
    else if(aux.ano==4||aux.ano==5){
        aux.num_cota=0.25;
    }
    else if(aux.ano==6||aux.ano==7){
        aux.num_cota=0.2;
    }
    else if(aux.ano==8||aux.ano==9){
        aux.num_cota=0.15;
    }
    else if(aux.ano>=10){
        aux.num_cota=0.1;    
    }
    return aux.num_cota;
}

void resB(list<float>& result, list<Previ>& lista){
    float *auxi= new float[3];
    auxi[1]=0;
    auxi[2]=0;
    Previ *aux = new Previ;
    list<Previ>::iterator it;
    it = lista.begin();
    aux->num_cota=0;//coloquei pra passar no teste
    cin >> aux->num_cota;
    cin >> aux->val_cota;
    cin >> aux->ano;
    aux->num_cota = aux->num_cota/aux->val_cota;
    if(aux->num_cota>=0){
        while(aux->num_cota>it->num_cota){
            auxi[0]= aux->num_cota - it->num_cota;
            aux->num_cota= it->num_cota;
            auxi[1]= auxi[1]+aux->num_cota*aux->val_cota; //valor do resgate
            auxi[2]= auxi[2]+( (aux->num_cota)*(alicota(*aux, it))*(aux->val_cota-1) ); //valor do imposto
            aux->num_cota= auxi[0];
            lista.pop_front();
            it=lista.begin();
        }
        it->num_cota=it->num_cota-(aux->num_cota);
        auxi[1]= auxi[1]+aux->num_cota*aux->val_cota; //valor do resgate
        auxi[2]= auxi[2]+( (aux->num_cota)*(alicota(*aux, it))*(aux->val_cota-1) ); //valor do imposto
    }
    else{          //condição para o resgate total
        while(it != end(lista)){  
            auxi[1]= auxi[1]+it->num_cota * aux->val_cota; //valor do resgate
            auxi[2]= auxi[2]+( (it->num_cota)*(alicota(*aux, it))*(aux->val_cota-1) ); //valor do imposto
            lista.pop_front();
            it=lista.begin(); 
        }       
    }
    result.push_back(auxi[1]);
    result.push_back(auxi[2]);
    delete aux;
    delete [] auxi;
}

int main()
{
    list<Previ> lista;
    list<float> result;
    list<float>::iterator it;
    char *letra = new char;
    *letra='i';//coloquei pra passar no teste;
    int *i = new int;
    *i=0;
    while(cin >> *letra){
        if(*letra=='A'){
            resA(lista);
        }
        else if(*letra=='R'){
            resB(result, lista);
        }
    }
    delete letra;
    it = result.begin();
    while(it != end(result)){  
        cout << fixed << setprecision(2) << *it;
        if( *i %2!=0){
            cout << "\n";
        }  
        else{
            cout << " ";
        }     
        result.pop_front();
        it=result.begin(); 
        (*i)++;
    } 
    delete i;
    return 0;
} 