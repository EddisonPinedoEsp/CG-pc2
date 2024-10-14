#include <vector>
#include <limits>
using namespace std;

template <typename T>
bool punto_en_segmento(const vector<T>& a, const vector<T>& b, T px, T py) {
    return (px <= max(a[0], b[0]) && px >= min(a[0], b[0]) &&
            py <= max(a[1], b[1]) && py >= min(a[1], b[1]) &&
            (b[0] - a[0]) * (py - a[1]) == (b[1] - a[1]) * (px - a[0]));
}

template <typename T>
bool inside_polygon(const vector<vector<T>>& vertices, T px, T py) {
    int n = vertices.size();
    bool inside = false;

    // Primero, verifica si el punto está en algún vértice del polígono
    for (const auto& vertex : vertices) {
        if (px == vertex[0] && py == vertex[1]) {
            return true;  // El punto es un vértice
        }
    }

    // Verifica si el punto está en un borde del polígono
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (punto_en_segmento(vertices[i], vertices[j], px, py)) {
            return true;  // El punto está en un borde
        }
    }

    // Si no es un vértice ni está en un borde, usa el algoritmo del rayo
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if ((vertices[i][1] > py) != (vertices[j][1] > py) &&
            (px < (vertices[j][0] - vertices[i][0]) * (py - vertices[i][1]) / (vertices[j][1] - vertices[i][1]) + vertices[i][0])) {
            inside = !inside;  // Cambia el estado de inside si el rayo cruza el borde
        }
    }
    return inside;
}

bool inside_polygon(const vector<vector<int>>& vertices, int px, int py){
    return inside_polygon<int>(vertices, px, py);
}

bool inside_polygon(const vector<vector<double>>& vertices, double px, double py){
    return inside_polygon<double>(vertices, px, py);
}