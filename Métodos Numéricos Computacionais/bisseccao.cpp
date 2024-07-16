#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return pow(x, 5) + 11.4004 * pow(x, 4) + 35.9479 * pow(x, 3) + 10.9188 * pow(x, 2) - 75.8538 * x - 46.0924;
}

void bisseccao(double a, double b, double precisao) {
    double fa = f(a);
    double fb = f(b);
    double c;

    int k = 0;
    double erro_rel;

    cout << "MÉTODO DA BISSECÇÃO | DETERMINAÇÃO DA RAÍZ z1" << endl;
    cout << "k\tak\t\txk\t\tbk\t\tf(xk)\t\tERk" << endl;

    do {
        c = (a + b) / 2.0;
        double fc = f(c);
        erro_rel = fabs((b - a) / (b + a));

        cout << k << "\t" << fixed << setprecision(10) << a << "\t" << c << "\t" << b << "\t" << fc << "\t" << erro_rel << endl;

        if (fa * fc > 0) {
            a = c;
            fa = fc;
        } else {
            b = c;
            fb = fc;
        }

        k++;
    } while (erro_rel > precisao && k < 1000); // Evita looping infinito

    cout << "Raíz z1 = " << fixed << setprecision(10) << c << endl;
}

int main() {
    double a = -7.0;
    double b = 3.0;
    double precisao = 1e-6; // 10^-6

    bisseccao(a, b, precisao);

    return 0;
}
