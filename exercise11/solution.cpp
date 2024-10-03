#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Write a function that computes the area of a convex polygon.


struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

// Función para calcular la orientación de tres puntos A, B, C
int orientation(Point A, Point B, Point C) {
    double cross_product = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);

    if (cross_product == 0) {
        return 0;  // Los puntos son colineales
    }

    return (cross_product > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Verifica si un polígono es convexo
bool is_convex(const vector<Point>& polygon) {
    if (polygon.size() < 3) {
        return false;  // Un polígono debe tener al menos 3 vértices
    }

    int n = polygon.size();
    int first_orientation = -1;

    for (int i = 0; i < n; i++) {
        Point A = polygon[i];
        Point B = polygon[(i + 1) % n];
        Point C = polygon[(i + 2) % n];

        int orient = orientation(A, B, C);
        if (orient != 0) {
            if (first_orientation == -1) {
                first_orientation = orient;  // Guarda la primera orientación no colineal
            } else if (orient != first_orientation) {
                return false;  // Si las orientaciones difieren, no es convexo
            }
        }
    }

    return true;
}

// Función para calcular el área de un polígono usando la fórmula del zapato
float polygon_area(const vector<Point>& polygon) {
    if (polygon.size() < 3) {
        return 0;  // El área de un polígono con menos de 3 puntos es 0
    }

    // Verifica si el polígono es convexo
    if (!is_convex(polygon)) {
        cout << "The polygon is not convex" << endl;
        return -1;
    }

    int n = polygon.size();
    double area = 0.0;

    // Usamos la fórmula del zapato para calcular el área
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y;
    }

    return abs(area) / 2.0;
}

// Función de prueba
void test() {
    // Definir un polígono regular (rectángulo en este caso)
    vector<Point> polygon = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};  // Rectángulo

    float area = polygon_area(polygon);
    if (area != -1) {
        cout << "Area: " << area << endl;
    }
}

int main() {
    test();
    return 0;
}
