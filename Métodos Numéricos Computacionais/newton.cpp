#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Função polinomial P(x)
double P(double x) {
    return pow(x, 5) + 11.4004 * pow(x, 4) + 35.9479 * pow(x, 3) + 10.9188 * pow(x, 2) - 75.8538 * x - 46.0924;
}

// Derivada da função polinomial P'(x)
double dP(double x) {
    return 5 * pow(x, 4) + 45601.6 * pow(x, 3) + 107.8437 * pow(x, 2) + 21.8376 * x - 75.8538;
}

// Método de Newton para encontrar a raiz
void newton(double a, double b, double epsilon) {
    double x0 = (a + b) / 2.0; // Estimativa inicial

    int k = 0;
    double xk, fxk, f_d_xk, erro;

    cout << "MÉTODO DE NEWTON | DETERMINAÇÃO DA RAÍZ\n";
    cout << "k\t\t xk\t\t\t f(xk)\t\t\t f'(xk)\t\t\t ERk\n";

    do {
        k++;
        fxk = P(x0);
        f_d_xk = dP(x0);

        xk = x0 - fxk / f_d_xk;
        erro = fabs(fxk);

        cout << k << "\t\t " << fixed << setprecision(10) << xk << "\t\t " << fxk << "\t\t " << f_d_xk << "\t\t " << erro << "\n";

        x0 = xk;
    } while (erro > epsilon);

    cout << "Raíz encontrada: " << fixed << setprecision(10) << xk << "\n";
}

int main() {
    double a = -7.0; // Limite inferior do intervalo
    double b = 3.0;  // Limite superior do intervalo
    double epsilon = 1e-6; // Tolerância de erro

    newton(a, b, epsilon);

    return 0;
}
