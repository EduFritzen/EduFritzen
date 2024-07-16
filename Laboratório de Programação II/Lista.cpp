#include <iostream>
#include <list>
using namespace std;

bool removeNegativos(const int& v)
{
    return (v < 0);
}

int main()
{
    list<int> lista {2,3,4}; //cria uma lista

    lista.push_back(10);  // insere no fim

    lista.push_front(0);  // insere no começo

    lista.insert( end(lista), 10);   // insere no fim
    lista.insert( begin(lista), 0);  // insere no começo
    lista.insert( ++begin(lista), 1); // insere depois do 1o elemento da lista

    lista.remove( 2 );   // remove todos os elementos igual a 2
    lista.remove_if( removeNegativos );  // aplica uma função que decide quem remover

    for(auto it = begin(lista); it != end(lista); it++){
	    cout << *it << ' ';
    } // usando iteradores
    //end() passa do fim da lista! se tentar acessar o elemento lista.end() o 
    //programa terá falha de segmentação pois esta posição não existe em memória.

    lista.unique(); //remove elementos duplicados da lista.
    lista.pop_front(); //remove o primeiro elemento.
    lista.pop_back(); //remove o último elemento
    lista.front(); //retorna elemento da fila que esta na frente
    lista.back(); //retorna elemento da fila que esta na atras
    lista.empty(); //verifica se a lista está vazia
    lista.size(); //retorna o tamanho da lista
    lista.max_size(); //retorno o potencial máximo de capacidade que esta lista pode ter.
    lista.clear(); //limpa a lista
    lista.sort(); //ordena a lista
    lista.reverse(); //ordena inversamente a lista
    return 0;
}
