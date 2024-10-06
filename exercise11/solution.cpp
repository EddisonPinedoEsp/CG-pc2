#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// Función que calcula la orientación de tres puntos (producto cruz)
int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;
    }
    return (orientation > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Función que verifica si un polígono es convexo
bool esConvexo(const vector<vector<float>>& poligono) {
    if (poligono.size() < 3) {
        return false;
    }

    int n = poligono.size();
    int primera_orientacion = -1; 

    for (int i = 0; i < n; i++) {
        vector<float> A = poligono[i];
        vector<float> B = poligono[(i + 1) % n];
        vector<float> C = poligono[(i + 2) % n];

        int orient = orientacion(A[0], A[1], B[0], B[1], C[0], C[1]);

        if (orient != 0) {
            if (primera_orientacion == -1) {
                primera_orientacion = orient;
            } else if (orient != primera_orientacion) {
                return false;
            }
        }
    }

    return true;
}

// Función para calcular el área de un polígono
float area_poligono(const vector<vector<float>>& poligono) {
    // El polígono debe tener al menos 3 vértices
    if (poligono.size() < 3) {
        return 0;
    }

    if (!esConvexo(poligono)) {
        cout << "El polígono no es convexo" << endl;
        return -1;
    }

    float area = 0;
    int n = poligono.size();

    for (int i = 0; i < n; i++) {
        float x1 = poligono[i][0];
        float y1 = poligono[i][1];
        float x2 = poligono[(i + 1) % n][0];
        float y2 = poligono[(i + 1) % n][1];

        area += (x1 * y2) - (x2 * y1);
    }

    area = abs(area) / 2.0;
    return area;
}
