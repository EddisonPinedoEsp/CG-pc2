#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>


using namespace std;

int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;
    }
    return (orientation > 0) ? 1 : 2;
}

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

bool punto_en_poligono(const vector<vector<float>>& P, const vector<float>& A) {
    int n = P.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((P[i][1] > A[1]) != (P[j][1] > A[1])) &&
            (A[0] < (P[j][0] - P[i][0]) * (A[1] - P[i][1]) / (P[j][1] - P[i][1]) + P[i][0])) {
            inside = !inside;
        }
    }
    return inside;
}

vector<vector<float>> jarvis_march(vector<vector<float>> puntos) {
    int n = puntos.size();
    if (n < 3) return {};

    vector<vector<float>> hull;

    int masInquierda = 0;
    for (int i = 1; i < n; i++) {
        if (puntos[i][0] < puntos[masInquierda][0]) {
            masInquierda = i;
        }
    }

    int p = masInquierda, q;
    do {
        // Añade el punto actual a la envolvente
        hull.push_back(puntos[p]);

        // Encuentra el punto más "a la izquierda" de todos los demás con respecto a p
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientacion(puntos[p][0], puntos[p][1], puntos[i][0], puntos[i][1],puntos[q][0], puntos[q][1]) == 2) {
                q = i;
            }
        }

        // Mueve al siguiente punto
        p = q;

    } while (p != masInquierda);  // Se detiene cuando volvemos al punto inicial

    return hull;
}

// Función que calcula el punto de intersección entre dos segmentos si existe
bool interseccion(const vector<float>& A, const vector<float>& B, const vector<float>& C, const vector<float>& D, vector<float>& intersec) {
    float a1 = B[1] - A[1];
    float b1 = A[0] - B[0];
    float c1 = a1 * A[0] + b1 * A[1];

    float a2 = D[1] - C[1];
    float b2 = C[0] - D[0];
    float c2 = a2 * C[0] + b2 * C[1];

    float det = a1 * b2 - a2 * b1;

    // fabs(): devuelve el valor absoluto de un número
    if (fabs(det) < 1e-10) {
        return false;
    } else {
        intersec[0] = (b2 * c1 - b1 * c2) / det;
        intersec[1] = (a1 * c2 - a2 * c1) / det;

        // Verificamos que la intersección esté en ambos segmentos
        if (min(A[0], B[0]) <= intersec[0] && intersec[0] <= max(A[0], B[0]) &&
            min(A[1], B[1]) <= intersec[1] && intersec[1] <= max(A[1], B[1]) &&
            min(C[0], D[0]) <= intersec[0] && intersec[0] <= max(C[0], D[0]) &&
            min(C[1], D[1]) <= intersec[1] && intersec[1] <= max(C[1], D[1])) {
            return true;
        }
    }

    return false;
}

// Función principal que calcula los puntos en la intersección de dos polígonos convexos
vector<vector<float>> puntos_de_interseccion(vector<vector<float>> poligono1, vector<vector<float>> poligono2) {
    vector<vector<float>> inter_puntos;

    if (poligono1.size() < 3 || poligono2.size() < 3) {
        return inter_puntos;  // No hay intersección si hay menos de 3 puntos
    }

    // Verifica si los polígonos son convexos
    if (!esConvexo(poligono1) || !esConvexo(poligono2)) {
        cout << "One of the poligonos is not convex" << endl;
        return {};
    }

    // Verifica intersecciones de los lados de los polígonos
    for (int i = 0; i < poligono1.size(); i++) {
        vector<float> A = poligono1[i];
        vector<float> B = poligono1[(i + 1) % poligono1.size()];

        for (int j = 0; j < poligono2.size(); j++) {
            vector<float> C = poligono2[j];
            vector<float> D = poligono2[(j + 1) % poligono2.size()];

            vector<float> intersec(2);
            if (interseccion(A, B, C, D, intersec)) {
                inter_puntos.push_back(intersec);
            }
        }
    }

    // Añade puntos del polígono 1 dentro del polígono 2
    for (auto& punto : poligono1) {
        if (punto_en_poligono(poligono2, punto)) {
            inter_puntos.push_back(punto);
        }
    }

    // Añade puntos del polígono 2 dentro del polígono 1
    for (auto& punto : poligono2) {
        if (punto_en_poligono(poligono1, punto)) {
            inter_puntos.push_back(punto);
        }
    }

    // Convierte los puntos a una envolvente convexa
    return jarvis_march(inter_puntos);
}

// Función para calcular el área de un polígono dado sus puntos (Fórmula de Shoelace)
float calcular_area(const vector<vector<float>>& poligono) {
    float area = 0;
    int n = poligono.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poligono[i][0] * poligono[j][1] - poligono[j][0] * poligono[i][1];
    }

    return fabs(area) / 2.0;
}


void test() {

    vector<vector<float>> polygon1 = { {0, 0}, {4, 0}, {4, 4}, {0, 4} };
    vector<vector<float>> polygon2 = { {2, 2}, {6, 2}, {6, 6}, {2, 6} };

    vector<vector<float>> puntos_interseccion = puntos_de_interseccion(polygon1, polygon2);

    if (!puntos_interseccion.empty()) {
        float area = calcular_area(puntos_interseccion);
        cout << "Área de intersección: " << area << endl;
    } else {
        cout << "No hay intersección" << endl;
    }

}

int main(){
    test();
    return 0;
}


