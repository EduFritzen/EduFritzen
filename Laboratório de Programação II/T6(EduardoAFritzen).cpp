

#include <stack>
#include <iostream>

#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
#include "catch.hpp"

template<typename T>
T converte(std::string s)
{}

template<>
int converte<int>(std::string s)
{
    return std::stoi(s);
}

template<>
float converte<float>(std::string s)
{
    return std::stof(s);
}

template<typename T>
struct Calculadora {
    int cont=0;
    // ver http://en.cppreference.com/w/cpp/container/stack
    std::stack<T> operandos;    // números, basicamente
    std::stack<char> operadores; // operadores: +, -, /, *
    // podem incluir mais dados, se necessário

    // cria a calculadora
    void cria(void){
    }

    // destroi a calculadora, limpa as pilhas
    void destroi(void){
        while(operandos.empty() == false)
            operandos.pop();
        while(operadores.empty() == false)
            operadores.pop();
    }

    // insere um novo operando para o calculo
    void operando(T op) {
        operandos.push(op);
    }

    // insere um novo operador para o calculo (pode ser '+', '-', '*', '/', '**')
    // se for um abre parenteses '(' tudo ok. 
    // se for um fecha parenteses ')', deve-se calcular tudo dentro.
    void operador(char op){
        // verficar aqui o operador inserido
        T aux1,aux2;
        if(op=='('||op==')'){
            cont++;
        }
        if(op==')'){
           aux2=operandos.top();
           operandos.pop();
           aux1=operandos.top();
           operandos.pop();
           if(operadores.top()=='+'){
               operandos.push(aux1+aux2);
           }
           else if(operadores.top()=='-'){
               operandos.push(aux1-aux2);
           }
           operadores.pop();
           operadores.pop();
        }
		if((operadores.size() > 0) && (operandos.size() > 1)){
			if((operadores.top()=='*'||operadores.top()=='/') && op!='('){
                aux2=operandos.top();
                operandos.pop();
                aux1=operandos.top();
                operandos.pop();
                if(operadores.top()=='*'){
                    operandos.push(aux1*aux2);
                }
                else if(operadores.top()=='/'){
                    operandos.push(aux1/aux2);
                }
                operadores.pop(); 
            }
		}
        if(op==')'){

        }
        else{
            operadores.push(op);
        }
        
    }
    
    // recebe uma formula in-fixa como entrada e coloca nas pilhas
    void formula(std::string form){
        int i=0;
        int tam=form.size();
        char a[10];
        if(form[0] == '-'){//sem essa condição, dá segmention fault
			form[0] = '0';
		}
        for(int k=0;k<tam;k++){
            while((form[k]!='+') && (form[k]!='-') && (form[k]!='*') && (form[k]!='/') && (form[k]!='(') && (form[k]!=')') && (k<tam)){
                a[i]=form[k];
                i++;
                k++;
            }//vai formando o numero em a[i]
            if(((k-1)>=0) && (form[k-1]!='+') && (form[k-1]!='-') && (form[k-1]!='*') && (form[k-1]!='/') && (form[k-1]!='(') && (form[k-1]!=')') && (k-1<tam)){
                operando( converte<float>(a) );    
            }
            i=0; // eh necessario zerar o i para manipular o vetor char
            for(int j=0;j<10;j++){
                a[j]='\0';
            } // coloquei um \0 em todas as posições do vetor para nao dar problema
            operador(form[k]);// nao precisa de if pq obrigatoriamente quando sair do while é um operador    
        }
    }

    // finaliza o calculo e verifica erros.
    // retorna false se erro detectado
    bool fim(void) {
        if(operandos.empty()){
            return false;
        }
        if(operadores.empty()&&operandos.size()!=1){
            return false; 
        }
        if(operandos.size()==1 && operadores.size()==1){
            return false;
        }
        if( cont%2 != 0){
            return false;
        }
		if(operadores.size() > 0){
			if(operadores.top() == '\0'){//condição para corrigir um erro, em algumas situação a pila de operadores armazena um caractere a mais \0
				operadores.pop();
			} 
		}
        T aux1,aux2;
        while(!operadores.empty()){
            aux2=operandos.top();
            operandos.pop();
            aux1=operandos.top();
            operandos.pop();
            if(operadores.top()=='+'){
                operandos.push(aux1+aux2);
            }
            else if(operadores.top()=='-'){
                operandos.push(aux1-aux2);
            }
            operadores.pop();
        }
        return true;
    }

    // retorna o resultado calculo (topo da pilha de operandos)
    // esse resultado sera parcial se ainda nao foi chamado calc_fim().
    T resultado(void) {
        if(operandos.empty())
            return static_cast<T>(0);

        return operandos.top();
    }
};

// erro porque as pilhas estao vazias
TEST_CASE("Teste vazio") {
    Calculadora<int> c;
    c.cria();
    REQUIRE(c.fim() == false);
}


// apenas um numero, entao OK
TEST_CASE("Casos simples") {
    Calculadora<int> c;
    c.cria();
    c.operando(1);
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 1);
}

// dois numeros sem operador e um erro
TEST_CASE("1 2") {
    Calculadora<int> c;
    c.cria();
    c.operando(1);
    c.operando(2);
    REQUIRE(c.fim() == false);
}

// falta um numero nesse calculo
TEST_CASE("1+ = erro") {
    Calculadora<int> c;
    c.cria();
    c.operando(1);
    c.operador('+');
    REQUIRE(c.fim() == false);
}

// erro de formula
TEST_CASE("3* = erro") {
    Calculadora<int> c;
    c.cria();
    c.formula("3*");
    REQUIRE(c.fim() == false);
}

// soma simples
TEST_CASE("3+2+9 = 14") {
    Calculadora<int> c;
    c.cria();
    c.formula("3+2+9");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 14);
}

// soma com negativos
TEST_CASE("-1+3-5 = -3") {
    Calculadora<int> c;
    c.cria();
    c.formula("-1+3-5");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == -3);
}

// soma com negativos
TEST_CASE("30-15+8 = 23") {
    Calculadora<int> c;
    c.cria();
    c.formula("30-15+8");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 23);
}

// multiplicacao
TEST_CASE("3*8+7 = 31") {
    Calculadora<int> c;
    c.cria();
    c.formula("3*8+7");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 31);
}

// divisao e multiplicacao
TEST_CASE("3*7+4/3 = 22") {
    Calculadora<int> c;
    c.cria();
    c.formula("3*7+4/3");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 22);
}

// parentesis
TEST_CASE("(3+4)*2+7 = 21") {
    Calculadora<int> c;
    c.cria();
    c.formula("(3+4)*2+7");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 21);
}

// parentesis
TEST_CASE("3+4*(9+3) = 51") {
    Calculadora<int> c;
    c.cria();
    c.formula("3+4*(9+3)");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 51);
}

// parentesis
TEST_CASE("(3+1)*(4+7)+3-1 = 46") {
    Calculadora<int> c;
    c.cria();
    c.formula("(3+1)*(4+7)+3-1");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 46);
}

// parentesis errado
TEST_CASE("4+(1+2 = erro") {
    Calculadora<int> c;
    c.cria();
    c.formula("4+(1+2");
    REQUIRE(c.fim() == false);
}

// parentesis errado
TEST_CASE("4+(1+2)+1) = erro") {
    Calculadora<int> c;
    c.cria();
    c.formula("4+(1+2)+1)");
    REQUIRE(c.fim() == false);
}

TEST_CASE("3.1+5.7-3.3 = 5.5") {
    Calculadora<float> c;
    c.cria();
    c.formula("3.1+5.7-3.3");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 5.5);
}


TEST_CASE("7/4+1 = 2.75") {
    Calculadora<float> c;
    c.cria();
    c.formula("7/4+1");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 2.75);
}

TEST_CASE("3.3*2+7.796 = 14.396") {
    Calculadora<float> c;
    c.cria();
    c.formula("3.3*2+7.796");
    REQUIRE(c.fim() == true);
    REQUIRE(c.resultado() == 14.396f);
}