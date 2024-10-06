# include <iostream>
# include <vector>

using namespace std;

int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;  // Colineales
    }
    return (orientation > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Función que verifica si un polígono es convexo
bool esConvexo(const vector<vector<float>>& polygon) {
    // El polígono debe tener al menos 3 vértices
    if (polygon.size() < 3) {
        return false;
    }

    int n = polygon.size();
    int primera_orientacion = -1;

    for (int i = 0; i < n; i++) {
        vector<float> A = polygon[i];
        vector<float> B = polygon[(i + 1) % n];
        vector<float> C = polygon[(i + 2) % n];

        int orient = orientacion(A[0], A[1], B[0], B[1], C[0], C[1]);

        if (orient != 0) {
            if (primera_orientacion == -1) {
                primera_orientacion = orient;
            } else if (orient != primera_orientacion) {
                // Si las orientaciones no son iguales, el polígono no es convexo
                return false;
            }
        }
    }

    return true;
}

