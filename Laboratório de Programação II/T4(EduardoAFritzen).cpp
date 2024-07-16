#include <iostream>
#include <list>
using namespace std;

int main()
{
    int tam, aux=0;
    list<int> baralho;
    list<int> res;
    cin >> tam;
    for(auto i=0;i<tam;i++){
        baralho.push_back(i+1);
    }
    while(baralho.size()>1){
        if(aux%2==0){
            res.push_back(baralho.front());
            baralho.pop_front();
        }
        else{
            baralho.push_back(baralho.front());
            baralho.pop_front();
        }
        aux++;
    }
    for(auto it = begin(res); it != end(res); it++){
	    cout << *it << ' ';
    }
    cout << "\n" << baralho.front() << "\n";
    return 0;
}