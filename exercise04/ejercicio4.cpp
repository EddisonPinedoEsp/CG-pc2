#include <vector>
#include <limits>
using namespace std;

template <typename T>
long double signo_area_triangulo(const vector<T>& a, const vector<T>& b, const vector<T>& c) {
    long double area = (static_cast<double>(a[0]) * static_cast<double>(b[1]) 
                 - static_cast<double>(a[1]) * static_cast<double>(b[0]) 
                 + static_cast<double>(a[1]) * static_cast<double>(c[0]) 
                 - static_cast<double>(a[0]) * static_cast<double>(c[1]) 
                 + static_cast<double>(b[0]) * static_cast<double>(c[1]) 
                 - static_cast<double>(c[0]) * static_cast<double>(b[1])) / 2.0;
    return area;
}

template <typename T>
bool sentido_horario(const vector<T>& a, const vector<T>& b, const vector<T>& c) {
    const double EPSILON = 1e-9;
    return signo_area_triangulo(a, b, c) < -EPSILON;
}

template <typename T>
bool inside_triangle(const vector<vector<T>>& vertices, T px, T py) {
    vector<T> P = {px, py};
    // Verifica si el punto P está en el mismo sentido que los vértices del triángulo
    if (sentido_horario(vertices[0], vertices[1], P)) return false;
    if (sentido_horario(vertices[1], vertices[2], P)) return false;
    if (sentido_horario(vertices[2], vertices[0], P)) return false;
    return true;
}

bool inside_triangle(const vector<vector<int>>& vertices, int px, int py) {
    return inside_triangle<int>(vertices, px, py);
}

bool inside_triangle(const vector<vector<double>>& vertices, double px, double py) {
    return inside_triangle<double>(vertices, px, py);
}
