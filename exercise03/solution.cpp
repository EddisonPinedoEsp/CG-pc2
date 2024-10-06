#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Función que calcula la distancia entre un punto y una recta
float distacia_punto_recta(vector<float> P1, vector<float> d, vector<float> P) {
    // Usa la fórmula de la distancia entre un punto y una recta
    float x = P[0] - P1[0];
    float y = P[1] - P1[1];
    float z = P[2] - P1[2];
    float t = (x * d[0] + y * d[1] + z * d[2]) / (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    float x1 = P1[0] + t * d[0];
    float y1 = P1[1] + t * d[1];
    float z1 = P1[2] + t * d[2];
    float x2 = x1 - P[0];
    float y2 = y1 - P[1];
    float z2 = z1 - P[2];
    return sqrt(x2 * x2 + y2 * y2 + z2 * z2);
}

int main() {
    vector<float> P1 = {-1, 2, 3};
    vector<float> d = {3, 1, -2};
    vector<float> P = {1, -4, 3};
    cout << distacia_punto_recta(P1, d, P) << endl;
    return 0;
}
