#include <iostream>
#include<conio.h>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// ---------- IMPRIME UN VECTOR : CON 2 DECIMALES DE PRESICION --------------
void imprimirVector(const vector<double>& v) {
    for (double val : v) {
        cout << fixed << setprecision(2) << val << " ";
    }
    cout << endl;
}

// ------------ CALCULA EL PRODUCTO PUNTO -----------------
double productoPunto(const vector<double>& v1, const vector<double>& v2) {
    double result = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// -------------- RESTA DOS VECTORES -------------
vector<double> restarVectores(const vector<double>& v1, const vector<double>& v2) {
    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

// -------------- MULTIPLA UN VECTOR POR UN ESCALAR -------------------
vector<double> multiplicarPorEscalar(const vector<double>& v, double escalar) {
    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * escalar;
    }
    return result;
}

// ------------ CALCULA LA NORMA DE UN VECTOR ----------------
double normaVector(const vector<double>& v) {
    return sqrt(productoPunto(v, v));
}

// ------------ NORMALIZA UN VECTOR DIVIDIENDOLO POR SU NORMA ----------------
vector<double> normalizarVector(const vector<double>& v) {
    double norma = normaVector(v);
    if (norma == 0) {
        cerr << "Error: Norma del vector es cero. No se puede normalizar." << endl;
        exit(1);
    }
    return multiplicarPorEscalar(v, 1.0 / norma);
}

int main() {
    int n, p;
    cout << "______________________________________________" << endl;
    cout << "Ingrese el numero de dimensiones (n): ";
    cin >> n;
    cout << "Ingrese el numero de vectores (p): ";
    cin >> p;
    cout << "______________________________________________" << endl;

    vector<vector<double>> x(p, vector<double>(n));
    vector<vector<double>> v(p, vector<double>(n));
    vector<vector<double>> z(p, vector<double>(n));  // Matriz para vectores normalizados

    // Entrada de vectores
    for (int i = 0; i < p; ++i) {
        cout << "\nIngrese el vector x" << i + 1 << " (dimensiones separadas por espacios): ";
        for (int j = 0; j < n; ++j) {
            cin >> x[i][j];
        }
    }

    // Algoritmo de Gram-Schmidt
    for (int i = 0; i < p; ++i) {
        vector<double> temp(n, 0.0);
        v[i] = x[i];

        for (int j = 0; j < i; ++j) {
            double prodPunto = productoPunto(x[i], v[j]);
            double normaCuadrada = productoPunto(v[j], v[j]);

            if (normaCuadrada == 0) {
                cerr << "Error: Norma cuadrada es cero en la iteración " << j << ". Esto puede indicar que un vector es cero." << endl;
                return 1;
            }

            temp = multiplicarPorEscalar(v[j], prodPunto / normaCuadrada);
            v[i] = restarVectores(v[i], temp);
        }
        z[i] = normalizarVector(v[i]); // Normaliza el vector ortogonal
    }

    // Imprimir la base ortogonal y los vectores normalizados
    cout << "\n________________________________" << endl;
    cout << "La base ortogonal es:" << endl;
    for (const auto& vec : v) {
        imprimirVector(vec);
    }

    cout << "________________________________" << endl;
    cout << "La base ortonormal es:" << endl;
    for (const auto& vec : z) {
        imprimirVector(vec);
    }
    cout << "________________________________" << endl;

    return 0;
    getch();
}