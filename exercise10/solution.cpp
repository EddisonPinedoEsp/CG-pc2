#include <iostream>
#include <vector>

using namespace std;

// Funncion para calcular el factorial de un número
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Usamos la fórmula de la función de Catalan para calcular el n-ésimo número de Catalan
unsigned long long catalan(int n) {
    return factorial(2 * n) / (factorial(n + 1) * factorial(n));
}

// Fnunción para calcular el número de triangulaciones de un polígono
int numeroTriangulaciones(vector<vector<float>> poligono) {
    int n = poligono.size();

    // El polígono debe tener al menos 3 lados para la triangulación
    if (n < 3) {
        cerr << "Un polígono debe tener al menos 3 lados" << endl;
        return 0;
    }

    // Aplicamos la fórmula de la función de Catalan para calcular el número de triangulaciones
    return catalan(n - 2);
}
