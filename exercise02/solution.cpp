# include <iostream>
# include <vector>

using namespace std;

// Let P be a polygon, represented as a list of adjacent vertices. For example: if P = [p0, p1, p2, . . . , pn−1], the vertex p2 is adjacent to the vertices p1 and p3, the vertex p5 is adjacent to the vertices p4 and p6, and so on (notice that the vertex pn−1 will be adjacent to pn−2 and to p0).
// Decide if P, represented in the mentioned way, is convex or not. 
// The function should return true if the polygon is convex, and false otherwise.

// bool esConvexo(vector<vector<int>> P) {
//     int cantidaDeVertices = P.size();
//     long long prev = 0;  
//     long long curr = 0; 

//     for (int i = 0; i < cantidaDeVertices; i++) {
//         int x1 = P[(i + 1) % cantidaDeVertices][0] - P[i][0];
//         int y1 = P[(i + 1) % cantidaDeVertices][1] - P[i][1];
//         int x2 = P[(i + 2) % cantidaDeVertices][0] - P[(i + 1) % cantidaDeVertices][0];
//         int y2 = P[(i + 2) % cantidaDeVertices][1] - P[(i + 1) % cantidaDeVertices][1];
//         curr = x1 * y2 - x2 * y1;
//         if (curr != 0) {
//             if (curr * prev < 0) {
//                 return false;
//             }
//             prev = curr;
//         }
//     }
//     return true;
// }


// Función que calcula la orientación de tres puntos (producto cruz)
int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;  // Colineales
    }
    return (orientation > 0) ? 1 : 2;  // 1: Sentido horario, 2: Sentido antihorario
}

// Función que verifica si un polígono es convexo
bool esConvexo(const vector<vector<int>>& P) {
    if (P.size() < 3) {
        return false;  // Un polígono debe tener al menos 3 vértices
    }

    int n = P.size();
    int primera_orientacion = -1;  // Para almacenar la primera orientación encontrada

    for (int i = 0; i < n; i++) {
        vector<int> A = P[i];
        vector<int> B = P[(i + 1) % n];
        vector<int> C = P[(i + 2) % n];

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

// Función de prueba
void test() {
    vector<vector<int>> P = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};  // Rectángulo
    cout << (esConvexo(P) ? "Es convexo" : "No es convexo") << endl;
}

int main() {
    test();
    return 0;
}

