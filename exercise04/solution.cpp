#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Given a triangle T ∈ R2 (given by its vertices) and an input point P, decide if P ∈ T.

// Función para calcular el área con signo de un triángulo dado por sus vértices
double signed_triangle_area(const vector<float>& a, const vector<float>& b, const vector<float>& c) {
    return (a[0] * b[1] - a[1] * b[0] + a[1] * c[0] - a[0] * c[1] + b[0] * c[1] - c[0] * b[1]) / 2.0;
}

// Función para verificar si los puntos están en sentido horario
bool cw(const vector<float>& a, const vector<float>& b, const vector<float>& c) {
    const double EPSILON = 1e-9;
    return signed_triangle_area(a, b, c) < -EPSILON;
}

// Función para verificar si el punto P está dentro del triángulo T
bool point_in_triangle(const vector<vector<float>>& T, const vector<float>& P) {
    if (cw(T[0], T[1], P)) return false;
    if (cw(T[1], T[2], P)) return false;
    if (cw(T[2], T[0], P)) return false;
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


    cout << " Ponit D " <<point_in_triangle(T, D) << endl;
    cout << " Ponit E " <<point_in_triangle(T, E) << endl;
    cout << " Ponit F " <<point_in_triangle(T, F) << endl;
    cout << " Ponit G " <<point_in_triangle(T, G) << endl;
    cout << " Ponit H " <<point_in_triangle(T, H) << endl;
    cout << " Ponit I " <<point_in_triangle(T, I) << endl;
    cout << " Ponit J " <<point_in_triangle(T, J) << endl;
    cout << " Ponit K " <<point_in_triangle(T, K) << endl;
    cout << " Ponit L " <<point_in_triangle(T, L) << endl;
    cout << " Ponit M " <<point_in_triangle(T, M) << endl;
    cout << " Ponit N " <<point_in_triangle(T, N) << endl;
    cout << " Ponit O " <<point_in_triangle(T, O) << endl;
    cout << " Ponit P " <<point_in_triangle(T, P) << endl;
}



int main() {


    test();
    return 0;
}

