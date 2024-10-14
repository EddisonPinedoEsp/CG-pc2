#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

template <typename T>
int orientacion(T xa, T ya, T xb, T yb, T xc, T yc) {
    T orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);
    if (orientation == 0) {
        return 0;
    }
    return (orientation > 0) ? 1 : 2;
}

template <typename T>
bool esConvexo(const vector<vector<T>>& poligono) {
    if (poligono.size() < 3) {
        return false;
    }

    int n = poligono.size();
    int primera_orientacion = -1; 

    for (int i = 0; i < n; i++) {
        vector<T> A = poligono[i];
        vector<T> B = poligono[(i + 1) % n];
        vector<T> C = poligono[(i + 2) % n];

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

template <typename T>
bool punto_en_poligono(const vector<vector<T>>& P, const vector<T>& A) {
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

template <typename T>
vector<vector<T>> jarvis_march(vector<vector<T>> puntos) {
    int n = puntos.size();
    if (n < 3) return {};

    vector<vector<T>> hull;

    int masInquierda = 0;
    for (int i = 1; i < n; i++) {
        if (puntos[i][0] < puntos[masInquierda][0]) {
            masInquierda = i;
        }
    }

    int p = masInquierda, q;
    do {
        hull.push_back(puntos[p]);

        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientacion(puntos[p][0], puntos[p][1], puntos[i][0], puntos[i][1], puntos[q][0], puntos[q][1]) == 2) {
                q = i;
            }
        }

        p = q;

    } while (p != masInquierda);  

    return hull;
}

template <typename T>
bool interseccion(const vector<T>& A, const vector<T>& B, const vector<T>& C, const vector<T>& D, vector<T>& intersec) {
    T a1 = B[1] - A[1];
    T b1 = A[0] - B[0];
    T c1 = a1 * A[0] + b1 * A[1];

    T a2 = D[1] - C[1];
    T b2 = C[0] - D[0];
    T c2 = a2 * C[0] + b2 * C[1];

    T det = a1 * b2 - a2 * b1;

    if (fabs(det) < 1e-10) {
        return false;
    } else {
        intersec[0] = (b2 * c1 - b1 * c2) / det;
        intersec[1] = (a1 * c2 - a2 * c1) / det;

        if (min(A[0], B[0]) <= intersec[0] && intersec[0] <= max(A[0], B[0]) &&
            min(A[1], B[1]) <= intersec[1] && intersec[1] <= max(A[1], B[1]) &&
            min(C[0], D[0]) <= intersec[0] && intersec[0] <= max(C[0], D[0]) &&
            min(C[1], D[1]) <= intersec[1] && intersec[1] <= max(C[1], D[1])) {
            return true;
        }
    }

    return false;
}

template <typename T>
vector<vector<T>> puntos_de_interseccion(vector<vector<T>> poligono1, vector<vector<T>> poligono2) {
    vector<vector<T>> inter_puntos;

    if (poligono1.size() < 3 || poligono2.size() < 3) {
        return inter_puntos;
    }

    if (!esConvexo(poligono1) || !esConvexo(poligono2)) {
        cout << "One of the poligonos is not convex" << endl;
        return {};
    }

    for (int i = 0; i < poligono1.size(); i++) {
        vector<T> A = poligono1[i];
        vector<T> B = poligono1[(i + 1) % poligono1.size()];

        for (int j = 0; j < poligono2.size(); j++) {
            vector<T> C = poligono2[j];
            vector<T> D = poligono2[(j + 1) % poligono2.size()];

            vector<T> intersec(2);
            if (interseccion(A, B, C, D, intersec)) {
                inter_puntos.push_back(intersec);
            }
        }
    }

    for (auto& punto : poligono1) {
        if (punto_en_poligono(poligono2, punto)) {
            inter_puntos.push_back(punto);
        }
    }

    for (auto& punto : poligono2) {
        if (punto_en_poligono(poligono1, punto)) {
            inter_puntos.push_back(punto);
        }
    }

    return jarvis_march(inter_puntos);
}

template <typename T>
double calcular_area(const vector<vector<T>>& poligono) {
    double area = 0;
    int n = poligono.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poligono[i][0] * poligono[j][1] - poligono[j][0] * poligono[i][1];
    }

    return fabs(area) / 2.0;
}

template <typename T>
double area_of_intersection(vector<vector<T>> const& vertices1, vector<vector<T>> const& vertices2) {
    vector<vector<T>> interseccion_poligono = puntos_de_interseccion(vertices1, vertices2);
    return calcular_area(interseccion_poligono);
}

double area_of_intersection(vector<vector<int>> const& vertices1, vector<vector<int>> const& vertices2) {
    return area_of_intersection<int>(vertices1, vertices2);
}

double area_of_intersection(vector<vector<double>> const& vertices1, vector<vector<double>> const& vertices2) {
    return area_of_intersection<double>(vertices1, vertices2);
}
