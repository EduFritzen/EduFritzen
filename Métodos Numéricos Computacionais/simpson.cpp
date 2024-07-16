#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x);   // Declaração da função
double g(double x);
double integrand(double x);  // Declaração da função de integração

//double c1 = 1.5, c2 = 0.23, c3 = 1.7, c4 = 0.56;
//double c1 = 1.5, c2 = 0.61, c3 = 1.6, c4 = 1.6;
double c1 = 0.52, c2 = 0.49, c3 = 1.4, c4 = 0.19;

int main()
{
    int i, j, k, nint, nmax = 20;
    double A[nmax], ER[nmax], epsilon = 0.000001, a, b, h, aux;
    //a = 1.79;
    //b = 3.69;
    //a = -0.241;
    //b = 1.11;
    a = -0.261;
    b = 2.44;
    h = 0.5*(b-a);
    A[0] = h*( integrand(a) + integrand(b) + 4.0*integrand(0.5*(a+b)) )/3.0;
    ER[0] = 1.0;
    i = 0;
    nint = 2;
    while ( ER[i] > epsilon && i < nmax ){
        i++;
        nint = 2*nint;
        h = 0.5*h;
        double x[nint+1];
        x[0] = a;
        for ( j=1 ; j<=nint ; j++ ){
            x[j] = x[j-1] + h;
        }
        aux = integrand(x[2]);
        j = 4;
        while ( j < nint ){
            aux = aux + integrand(x[j]);
            j = j + 2;
        }
        A[i] = 2.0*aux;
        aux = integrand(x[1]);
        j = 3;
        while ( j < nint ){
            aux = aux + integrand(x[j]);
            j = j + 2;
        }
        A[i] = A[i] + 4.0*aux + integrand(x[0]) + integrand(x[nint]);
        A[i] = h*A[i]/3.0;
        ER[i] = abs(A[i]-A[i-1])/abs(A[i]);
    }

    cout << "k\t\tA\t\tER" << endl;
    for ( j=0 ; j<=i ; j++ ){
        cout << setprecision(10) << j << "\t\t" << A[j] << "\t\t" << ER[j] << endl;
    }
}

double f( double x ){
    double pi = 3.14159265359;
    return sin(2*pi*(x*(c1-(c2*x))+g(x)));
}

double g(double x){
    double pi = 3.14159265359;
    return 2*cos(2*pi*x*(c3-(c4*x)));
}

double integrand(double x) {
    return exp(-x) * f(x);
}
