#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Función para determinar la orientación entre tres puntos
template <typename T>
int orientacion(T xa, T ya, T xb, T yb, T xc, T yc) {
    T orientacion = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientacion == 0) {
        return 0;  // Colineales
    }
    return (orientacion > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Función para verificar si un polígono es convexo
template <typename T>
bool is_convex(const vector<vector<T>>& P) {
    if (P.size() < 3) {
        return false; // Un polígono debe tener al menos 3 vértices
    }

    int n = P.size();
    int first_orientation = -1; // No definida al principio

    for (int i = 0; i < n; i++) {
        vector<T> A = P[i];
        vector<T> B = P[(i + 1) % n];
        vector<T> C = P[(i + 2) % n];

        int orient = orientacion(A[0], A[1], B[0], B[1], C[0], C[1]);

        if (orient != 0) { // Si no es colineal
            if (first_orientation == -1) {
                first_orientation = orient;
            } else if (orient != first_orientation) {
                return false; // Si cambia la orientación, no es convexo
            }
        } else {
            // Verificación adicional para colinealidad alineada
            if ((B[0] - A[0]) * (C[0] - B[0]) >= 0 && (B[1] - A[1]) * (C[1] - B[1]) >= 0) {
                return false; // Tres puntos colineales y alineados
            }
        }
    }

    return true;
}

// Función para calcular el área de un polígono convexo
template <typename T>
double area(const vector<vector<T>>& vertices) {
    if (vertices.size() < 3) {
        return 0;
    }

    if (!is_convex(vertices)) {
        return 0;
    }

    double area = 0.0;
    int n = vertices.size();

    for (int i = 0; i < n; i++) {
        double x1 = static_cast<double>(vertices[i][0]);
        double y1 = static_cast<double>(vertices[i][1]);
        double x2 = static_cast<double>(vertices[(i + 1) % n][0]);
        double y2 = static_cast<double>(vertices[(i + 1) % n][1]);

        area += (x1 * y2) - (y1 * x2);
    }

    return fabs(area) / 2.0;  // Usamos fabs para evitar diferencias de signo
}

double area(vector<vector<int>> const& vertices) {
    return area<int>(vertices);
}

double area(vector<vector<double>> const& vertices) {
    return area<double>(vertices);
}