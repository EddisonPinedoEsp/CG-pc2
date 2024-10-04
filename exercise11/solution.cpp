#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Write a function that computes the area of a convex polygon.


// Función que calcula la orientación de tres puntos (producto cruz)
int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;  // Colineales
    }
    return (orientation > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Función que verifica si un polígono es convexo
bool esConvexo(const vector<vector<float>>& polygon) {
    if (polygon.size() < 3) {
        return false;  // Un polígono debe tener al menos 3 vértices
    }

    int n = polygon.size();
    int primera_orientacion = -1;  // Para almacenar la primera orientación encontrada

    for (int i = 0; i < n; i++) {
        vector<float> A = polygon[i];
        vector<float> B = polygon[(i + 1) % n];
        vector<float> C = polygon[(i + 2) % n];

        int orient = orientacion(A[0], A[1], B[0], B[1], C[0], C[1]);

        if (orient != 0) {
            if (primera_orientacion == -1) {
                primera_orientacion = orient;  // Guardamos la primera orientación no colineal
            } else if (orient != primera_orientacion) {
                return false;  // Si las orientaciones difieren, no es convexo
            }
        }
    }

    return true;
}
// Función para calcular el área de un polígono usando la fórmula del zapato
float polygon_area(const vector<vector<float>>& polygon) {
    if (polygon.size() < 3) {
        return 0;  // El área de un polígono con menos de 3 puntos es 0
    }

    // Verifica si el polígono es convexo
    if (!esConvexo(polygon)) {
        cout << "The polygon is not convex" << endl;
        return -1;
    }

    float area = 0;
    int n = polygon.size();

    for (int i = 0; i < n; i++) {
        float x1 = polygon[i][0];
        float y1 = polygon[i][1];
        float x2 = polygon[(i + 1) % n][0];
        float y2 = polygon[(i + 1) % n][1];

        area += (x1 * y2) - (x2 * y1);
    }

    area = abs(area) / 2.0;
    return area;
}

// Función de prueba
void test() {
    // Definir un polígono regular (rectángulo en este caso)
    vector<vector<float>> polygon = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};  // Rectángulo

    float area = polygon_area(polygon);
    if (area != -1) {
        cout << "Area: " << area << endl;
    }

    polygon = {{1, 1}, {8, 2}, {7.62, 6.16}, {2.66, 5.74}};
    float area1 = polygon_area(polygon);
    if (area1 != -1) {
        cout << "Area: " << area1 << endl;
    }
}

int main() {
    test();
    return 0;
}
