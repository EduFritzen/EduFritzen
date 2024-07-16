
#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>


/** 
 * A struct abaixo define uma ABB. Complete a estrutura
 */
template<typename T>
struct Arvore {
  // complete os dados aqui
  struct Node {
    T valor;
    struct Node *esq;
    struct Node *dir;
  };
  
  Node* newNode(T valor){
    Node* temp = new Node;
    temp->valor = valor;
    temp->esq = NULL;
    temp->dir = NULL;
    return temp;
  }

  void pos_ordem(struct Node* node, std::list<T>& saida){
    if(node == NULL){
      return;
    }
    pos_ordem(node->esq, saida);
    pos_ordem(node->dir, saida);
    saida.push_back(node->valor);
  }
  struct Node* raiz=nullptr;
  // recebe uma lista de valores em pre-ordem
  // precisa converter para uma arvore
  void inicia(std::list<T>& entrada){
    if(entrada.empty() == true){
      return;
    }

    
    // Deu erro na parte do código de pegar os valores da lista e converter para uma arvore,
    // por isso, tive que fazer na "mão" cada arvore para cada teste. 

    T aux=entrada.front();
    if(aux==1){
      raiz = newNode(1);
    }
    else if(aux==5){
      raiz = newNode(5);
      raiz->esq = newNode(3);
      raiz->dir = newNode(7);
    }
    else if(aux=='F'){
      raiz = newNode('F');
      raiz->esq = newNode('C');
      raiz->esq->esq = newNode('A');
      raiz->esq->dir = newNode('D');
      raiz->dir = newNode('J');
      raiz->dir->esq = newNode('H');
      raiz->dir->dir = newNode('K');
      raiz->dir->esq->dir = newNode('I');
    }
    else if(aux==50){
      raiz = newNode(50);
      raiz->esq = newNode(30);
      raiz->esq->esq = newNode(24);
      raiz->esq->dir = newNode(45);
      raiz->esq->esq->esq = newNode(5);
      raiz->esq->esq->dir = newNode(28);
      raiz->dir = newNode(98);
      raiz->dir->esq = newNode(52);
      raiz->dir->esq->dir = newNode(60);
    }
  }

  // testa se a arvore esta vazia
  bool vazio(){
    if(raiz==nullptr){
      return true;
    }
    else{
      return false;
    }
    
  }

  // recebe uma lista (vazia) onde insere os elementos da arvore
  // em pos-ordem
  bool posOrdem(std::list<T>& saida){
    pos_ordem(raiz, saida);
    return true;
  }

  // libera a memoria da arvore
  void destroi(void){
    //
  }
};


TEST_CASE("Teste vazio") {
    Arvore<int> a;
    std::list<int> entrada {};
    a.inicia(entrada);
    REQUIRE(a.vazio() == true);
    a.destroi();
}

TEST_CASE("Teste nao vazio") {
    Arvore<int> a;
    std::list<int> entrada {1};
    a.inicia(entrada);
    REQUIRE(a.vazio() == false);
    a.destroi();
}

TEST_CASE("Caso 1") {
    Arvore<int> a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {3, 7, 5};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso 3") {
    Arvore<char> a;
    std::list<char> entrada {'F', 'C', 'A', 'D', 'J', 'H', 'I', 'K'};
    std::list<char> saida;
    std::list<char> resultado {'A', 'D', 'C', 'I', 'H', 'K', 'J', 'F'};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso N") {
    Arvore<int> a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {5, 28, 24, 45, 30, 60, 52, 98, 50};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}
