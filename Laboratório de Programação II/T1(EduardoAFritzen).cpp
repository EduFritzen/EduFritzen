#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

struct pontos{
    vector<float> x;
    vector<float> y;
};

int main(int argc, char const *argv[])
{
    pontos coord;
    float numx, numy, res=0;
    int cont=0;
    while(cont<11){
        cin >> numx >> numy;
        coord.x.push_back(numx); 
        coord.y.push_back(numy); 
        cont++;
    }
    for(int i=0;i<10;i++){
        res= res + sqrt((coord.x[i+1]-coord.x[i])*(coord.x[i+1]-coord.x[i])+(coord.y[i+1]-coord.y[i])*(coord.y[i+1]-coord.y[i]));
    }
    cout << "\n" << setprecision(4)<< res;
    return 0;
}
