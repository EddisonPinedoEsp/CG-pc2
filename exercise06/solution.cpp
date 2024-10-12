#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Función para calcular el producto cruzado entre tres puntos
template <typename T>
T cross_product(const vector<T>& p, const vector<T>& q, const vector<T>& r) {
    return (q[0] - p[0]) * (r[1] - p[1]) - (q[1] - p[1]) * (r[0] - p[0]);
}

// Función para verificar si un punto está dentro del polígono
template <typename T>
bool is_inside_polygon(const vector<vector<T>>& vertices, const vector<T>& point) {
    int n = vertices.size();
    bool positive = false, negative = false;
    
    for (int i = 0; i < n; ++i) {
        const vector<T>& p1 = vertices[i];
        const vector<T>& p2 = vertices[(i + 1) % n];
        T cross = cross_product(p1, p2, point);
        
        if (cross > 0) positive = true;
        else if (cross < 0) negative = true;

        // Si el punto está tanto a la izquierda como a la derecha de algún borde, está fuera
        if (positive && negative) return false;
    }
    
    // Si el punto está en el mismo lado de todos los bordes, está dentro
    return true;
}

// Función para eliminar puntos interiores
template <typename T>
vector<vector<T>> interior_points_removal(const vector<vector<T>>& vertices) {
    vector<vector<T>> filtered;

    for (size_t i = 0; i < vertices.size(); ++i) {
        bool isInterior = false;

        // Crea un nuevo polígono excluyendo el punto actual
        vector<vector<T>> polygon;
        for (size_t j = 0; j < vertices.size(); ++j) {
            if (i != j) polygon.push_back(vertices[j]);
        }

        // Verifica si el punto actual está dentro del polígono formado por los otros puntos
        if (is_inside_polygon(polygon, vertices[i])) {
            isInterior = true;
        }

        // Solo se agrega el punto si no es interior
        if (!isInterior) {
            filtered.push_back(vertices[i]);
        }
    }
    return filtered;
}

// Función para encontrar el punto más a la izquierda
template <typename T>
int leftmost_point(const vector<vector<T>>& vertices) {
    int leftmost = 0;
    for (size_t i = 1; i < vertices.size(); i++) {
        if (vertices[i][0] < vertices[leftmost][0]) {
            leftmost = i;
        }
    }
    return leftmost;
}

// Algoritmo de Jarvis March
template <typename T>
vector<vector<T>> jarvis(const vector<vector<T>>& vertices, bool withInteriorPointsRemoval) {
    vector<vector<T>> points = vertices;

    // Elimina los puntos interiores si el parámetro está activado
    if (withInteriorPointsRemoval) {
        points = interior_points_removal(points);
    }

    // Verifica si hay suficientes puntos para formar una envolvente convexa
    if (points.size() < 3) return {};

    vector<vector<T>> hull;
    int start = leftmost_point(points);
    int current = start;

    do {
        hull.push_back(points[current]);
        int next = (current + 1) % points.size();
        
        for (size_t i = 0; i < points.size(); i++) {
            if (cross_product(points[current], points[next], points[i]) > 0) {
                next = i;
            }
        }
        current = next;
    } while (current != start);

    return hull;
}


// Función para calcular la distancia cuadrada entre dos puntos
template <typename T>
T squared_distance(const vector<T>& p, const vector<T>& q) {
    return (q[0] - p[0]) * (q[0] - p[0]) + (q[1] - p[1]) * (q[1] - p[1]);
}

// Función de comparación de ángulos para ordenar los puntos
template <typename T>
bool polar_order(const vector<T>& p0, const vector<T>& p1, const vector<T>& p2) {
    T cross = cross_product(p0, p1, p2);
    if (cross == 0) {
        return squared_distance(p0, p1) < squared_distance(p0, p2); // Ordenar por distancia en caso de ser colineales
    }
    return cross > 0; // Ordenar por ángulo polar
}

// Función para encontrar el punto más bajo (en caso de empate, el más a la izquierda)
template <typename T>
int lowest_point(const vector<vector<T>>& vertices) {
    int lowest = 0;
    for (size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i][1] < vertices[lowest][1] || 
           (vertices[i][1] == vertices[lowest][1] && vertices[i][0] < vertices[lowest][0])) {
            lowest = i;
        }
    }
    return lowest;
}

// Algoritmo de Graham Scan
template <typename T>
vector<vector<T>> graham(const vector<vector<T>>& vertices, bool withInteriorPointsRemoval) {
    vector<vector<T>> points = vertices;

    // Elimina los puntos interiores si el parámetro está activado
    if (withInteriorPointsRemoval) {
        points = interior_points_removal(points);
    }

    // Verifica si hay suficientes puntos para formar una envolvente convexa
    if (points.size() < 3) return {};

    // Encuentra el punto más bajo (el "pivote") y lo mueve al inicio
    int lowest = lowest_point(points);
    swap(points[0], points[lowest]);

    // Ordena los puntos por ángulo polar respecto al pivote
    sort(points.begin() + 1, points.end(), [&](const vector<T>& p1, const vector<T>& p2) {
        return polar_order(points[0], p1, p2);
    });

    // Algoritmo de Graham Scan
    vector<vector<T>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() > 1 && cross_product(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back(); // Elimina el punto que no pertenece a la envolvente convexa
        }
        hull.push_back(points[i]);
    }

    return hull;
}

int main() {
    vector<vector<int>> vertices = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9},
                {1, 0}, {1, 9}, {2, 0}, {2, 9}, {3, 0}, {3, 9}, {4, 0}, {4, 9}, {5, 0}, {5, 9}};

    // Ejecutar Jarvis con eliminación de puntos interiores
    vector<vector<int>> result = jarvis(vertices, true);

    cout << "Jarvis con eliminación de puntos interiores:" << endl;
    for (const auto& point : result) {
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
    }

    // Ejecutar Jarvis sin eliminación de puntos interiores
    result = jarvis(vertices, false);

    cout << "Jarvis sin eliminación de puntos interiores:" << endl;
    for (const auto& point : result) {
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
    }

    // Ejecutar Graham con eliminación de puntos interiores
    result = graham(vertices, true);

    cout << "Graham con eliminación de puntos interiores:" << endl;
    for (const auto& point : result) {
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
    }

    // Ejecutar Graham sin eliminación de puntos interiores
    result = graham(vertices, false);

    cout << "Graham sin eliminación de puntos interiores:" << endl;
    for (const auto& point : result) {
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
    }

    return 0;
}
