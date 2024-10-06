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


void test() {
    vector<vector<float>> T = {{3.44, 4.44}, {1.7, 1.8}, {6.26, 2.14}};
    vector<float> D = {3.44,4.44};
    vector<float> E = {1.7,1.8};
    vector<float> F = {6.26,2.14};
    vector<float> G = {4.90334,1.70082};
    vector<float> H = {4.59329,2.54096};
    vector<float> I = {3.60311,3.97121};
    vector<float> J = {4.65, 3.45};
    vector<float> K = {1.7, 1.8};
    vector<float> L = {3.02825,3.21927};
    vector<float> M = {3.96607,2.91845};
    vector<float> N = {3.05255,2.6273};
    vector<float> O = {1.79261,2.7436};
    vector<float> P = {3.90543,3.36388};


    cout << " Ponit D " <<punto_en_triangulo(T, D) << endl;
    cout << " Ponit E " <<punto_en_triangulo(T, E) << endl;
    cout << " Ponit F " <<punto_en_triangulo(T, F) << endl;
    cout << " Ponit G " <<punto_en_triangulo(T, G) << endl;
    cout << " Ponit H " <<punto_en_triangulo(T, H) << endl;
    cout << " Ponit I " <<punto_en_triangulo(T, I) << endl;
    cout << " Ponit J " <<punto_en_triangulo(T, J) << endl;
    cout << " Ponit K " <<punto_en_triangulo(T, K) << endl;
    cout << " Ponit L " <<punto_en_triangulo(T, L) << endl;
    cout << " Ponit M " <<punto_en_triangulo(T, M) << endl;
    cout << " Ponit N " <<punto_en_triangulo(T, N) << endl;
    cout << " Ponit O " <<punto_en_triangulo(T, O) << endl;
    cout << " Ponit P " <<punto_en_triangulo(T, P) << endl;
}



int main() {
    test();
    return 0;
}

