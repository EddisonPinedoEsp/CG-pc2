#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Función para verificar si un punto está dentro de un polígono
bool punto_en_poligono(const vector<vector<float>>& P, const vector<float>& A) {

    // Recorre todos los lados del polígono y verifica si el punto está a la izquierda o a la derecha   
    int n = P.size();
    bool inside = false;
    
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((P[i][1] > A[1]) != (P[j][1] > A[1])) &&
            (A[0] < (P[j][0] - P[i][0]) * (A[1] - P[i][1]) / (P[j][1] - P[i][1]) + P[i][0])) {
            inside = !inside;
        }
    }
    return inside;
}
