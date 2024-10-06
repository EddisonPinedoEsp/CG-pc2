#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Función para calcular el área con signo de un triángulo dado por sus vértices
double signo_area_triangulo(const vector<float>& a, const vector<float>& b, const vector<float>& c) {
    return (a[0] * b[1] - a[1] * b[0] + a[1] * c[0] - a[0] * c[1] + b[0] * c[1] - c[0] * b[1]) / 2.0;
}

// Función para verificar si los puntos están en sentido horario
bool sentido_horario(const vector<float>& a, const vector<float>& b, const vector<float>& c) {
    const double EPSILON = 1e-9;
    return signo_area_triangulo(a, b, c) < -EPSILON;
}

// Función para verificar si el punto P está dentro del triángulo T
bool punto_en_triangulo(const vector<vector<float>>& T, const vector<float>& P) {
    // Verifica si el punto P está en el mismo sentido que los vértices del triángulo
    if (sentido_horario(T[0], T[1], P)) return false;
    if (sentido_horario(T[1], T[2], P)) return false;
    if (sentido_horario(T[2], T[0], P)) return false;
    return true;
}
