#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Função polinomial P(x)
double P(double x) {
    return pow(x, 5) + 11400.4 * pow(x, 4) + 35.9479 * pow(x, 3) + 10.9188 * pow(x, 2) - 75.8538 * x - 46.0924;
}

// Método da secante para encontrar a raiz z3
void secante(double x0, double x1, double epsilon) {
    int k = 0;
    double xk, xk_ant, fxk, fxk_ant, erro;

    cout << "MÉTODO DA SECANTE | DETERMINAÇÃO DA RAÍZ z3\n";
    cout << "k\t\txk\t\tf(xk)\t\tERk\n";

    do {
        k++;
        xk_ant = x0;
        xk = x1;
        fxk_ant = P(x0);
        fxk = P(x1);

        erro = fabs((xk - xk_ant) / xk);

        cout << k << "\t\t" << fixed << setprecision(10) << xk << "\t" << fxk << "\t" << erro << "\n";

        double temp = xk;
        xk = xk - fxk * (xk - xk_ant) / (fxk - fxk_ant);
        xk_ant = temp;

        x0 = xk_ant;
        x1 = xk;

    } while (erro > epsilon);

    cout << "Raíz z3 = " << fixed << setprecision(10) << xk << "\n";
}

int main() {
    double x0 = 7.0; // Primeira estimativa inicial
    double x1 = 7.5; // Segunda estimativa inicial
    double epsilon = 1e-6; // Tolerância de erro

    secante(x0, x1, epsilon);

    return 0;
}
