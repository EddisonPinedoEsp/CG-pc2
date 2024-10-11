#include <vector>
using namespace std;

template <typename T>
int orientacion(T xa, T ya, T xb, T yb, T xc, T yc) {
    T orienttacion = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orienttacion == 0) {
        return 0;  // Colineales
    }
    return (orienttacion > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

template <typename T>
bool is_convex(vector<vector<T>> const& P) {
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
            // Caso donde tres puntos son colineales
            if ((B[0] - A[0]) * (C[0] - B[0]) >= 0 && (B[1] - A[1]) * (C[1] - B[1]) >= 0) {
                // Si los tres puntos son colineales y están alineados, no es convexo
                return false;
            }
        }
    }

    return true;
}


bool is_convex(vector<vector<int>> const& P) {
    return is_convex<int>(P);
}

bool is_convex(vector<vector<double>> const& P) {
    return is_convex<double>(P);
}