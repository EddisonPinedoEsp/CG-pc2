
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>


using namespace std;

// Write a function that computes the area of the intersection of two convex polygons
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

bool point_in_polygon(const vector<vector<float>>& P, const vector<float>& A) {
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

vector<vector<float>> jarvis_march(vector<vector<float>> points) {
    int n = points.size();
    if (n < 3) return {};  // No se puede formar una envolvente convexa con menos de 3 puntos

    vector<vector<float>> hull;

    // Encuentra el punto más a la izquierda
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i][0] < points[leftmost][0]) {
            leftmost = i;
        }
    }

    // Realiza el algoritmo de Jarvis March
    int p = leftmost, q;
    do {
        // Añade el punto actual a la envolvente
        hull.push_back(points[p]);

        // Encuentra el punto más "a la izquierda" de todos los demás con respecto a p
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientacion(points[p][0], points[p][1], points[i][0], points[i][1],points[q][0], points[q][1]) == 2) {
                q = i;
            }
        }

        // Mueve al siguiente punto
        p = q;

    } while (p != leftmost);  // Se detiene cuando volvemos al punto inicial

    return hull;
}

// Función que calcula el punto de intersección entre dos segmentos si existe
bool intersect_segment(const vector<float>& A, const vector<float>& B, const vector<float>& C, const vector<float>& D, vector<float>& intersection) {
    float a1 = B[1] - A[1];
    float b1 = A[0] - B[0];
    float c1 = a1 * A[0] + b1 * A[1];

    float a2 = D[1] - C[1];
    float b2 = C[0] - D[0];
    float c2 = a2 * C[0] + b2 * C[1];

    float det = a1 * b2 - a2 * b1;

    if (fabs(det) < 1e-10) {
        return false;  // Los segmentos son paralelos o coincidentes
    } else {
        intersection[0] = (b2 * c1 - b1 * c2) / det;
        intersection[1] = (a1 * c2 - a2 * c1) / det;

        // Verificamos que la intersección esté en ambos segmentos
        if (min(A[0], B[0]) <= intersection[0] && intersection[0] <= max(A[0], B[0]) &&
            min(A[1], B[1]) <= intersection[1] && intersection[1] <= max(A[1], B[1]) &&
            min(C[0], D[0]) <= intersection[0] && intersection[0] <= max(C[0], D[0]) &&
            min(C[1], D[1]) <= intersection[1] && intersection[1] <= max(C[1], D[1])) {
            return true;
        }
    }

    return false;
}

// Función principal que calcula los puntos en la intersección de dos polígonos convexos
vector<vector<float>> the_points_of_intersection(vector<vector<float>> polygon1, vector<vector<float>> polygon2) {
    vector<vector<float>> intersection_points;

    if (polygon1.size() < 3 || polygon2.size() < 3) {
        return intersection_points;  // No hay intersección si hay menos de 3 puntos
    }

    // Verifica si los polígonos son convexos
    if (!esConvexo(polygon1) || !esConvexo(polygon2)) {
        cout << "One of the polygons is not convex" << endl;
        return {};
    }

    // Verifica intersecciones de los lados de los polígonos
    for (int i = 0; i < polygon1.size(); i++) {
        vector<float> A = polygon1[i];
        vector<float> B = polygon1[(i + 1) % polygon1.size()];

        for (int j = 0; j < polygon2.size(); j++) {
            vector<float> C = polygon2[j];
            vector<float> D = polygon2[(j + 1) % polygon2.size()];

            vector<float> intersection(2);
            if (intersect_segment(A, B, C, D, intersection)) {
                intersection_points.push_back(intersection);
            }
        }
    }

    // Añade puntos del polígono 1 dentro del polígono 2
    for (auto& point : polygon1) {
        if (point_in_polygon(polygon2, point)) {
            intersection_points.push_back(point);
        }
    }

    // Añade puntos del polígono 2 dentro del polígono 1
    for (auto& point : polygon2) {
        if (point_in_polygon(polygon1, point)) {
            intersection_points.push_back(point);
        }
    }

    // Convierte los puntos a una envolvente convexa
    return jarvis_march(intersection_points);
}

// Función para calcular el área de un polígono dado sus puntos (Fórmula de Shoelace)
float calcular_area(const vector<vector<float>>& polygon) {
    float area = 0;
    int n = polygon.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += polygon[i][0] * polygon[j][1] - polygon[j][0] * polygon[i][1];
    }

    return fabs(area) / 2.0;
}


void test() {

    vector<vector<float>> polygon1 = { {0, 0}, {4, 0}, {4, 4}, {0, 4} };
    vector<vector<float>> polygon2 = { {2, 2}, {6, 2}, {6, 6}, {2, 6} };

    vector<vector<float>> puntos_interseccion = the_points_of_intersection(polygon1, polygon2);

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


