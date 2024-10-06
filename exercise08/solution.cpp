#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>

using namespace std;

// Funcion calcula la distancia entre dos puntos
double dist(const vector<float>& p1, const vector<float>& p2) {
    // Usa la fórmula de la distancia entre dos puntos
    return sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) +
                (p1[1] - p2[1]) * (p1[1] - p2[1]));
}

// Calcula la distancia más pequeña entre dos puntos de un conjunto de puntos
double segmentoCerca(vector<vector<float>>& segmento, double d, pair<vector<float>, vector<float>>& puntosCerca) {
    double min = d;

    // Ordena los puntos
    sort(segmento.begin(), segmento.end(), [](const vector<float>& p1, const vector<float>& p2) {
        return p1[1] < p2[1];
    });

    // Compara todos los puntos en el segmento
    for (size_t i = 0; i < segmento.size(); ++i) {
        for (size_t j = i + 1; j < segmento.size() && (segmento[j][1] - segmento[i][1]) < min; ++j) {
            double distance = dist(segmento[i], segmento[j]);
            if (distance < min) {
                min = distance;
                puntosCerca = {segmento[i], segmento[j]};
            }
        }
    }

    return min;
}

// Función auxiliar para encontrar la distancia más pequeña entre dos puntos
double masCerca(vector<vector<float>>& P, size_t n, pair<vector<float>, vector<float>>& puntosCerca) {
    // Si hay mas de 3 puntos, se resuelve por fuerza bruta
    if (n <= 3) {
        double min = DBL_MAX;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                double distance = dist(P[i], P[j]);
                if (distance < min) {
                    min = distance;
                    puntosCerca = {P[i], P[j]};
                }
            }
        }
        return min;
    }

    // Busca el punto medio
    size_t mid = n / 2;
    vector<float> midPoint = P[mid];

    // Encuentra la distancia más pequeña en la mitad izquierda y derecha del conjunto de puntos
    pair<vector<float>, vector<float>> leftPair, rightPair;
    double dl = masCerca(P, mid, leftPair);
    double dr = masCerca(P, n - mid, rightPair);

    // Encuentra la distancia más pequeña entre los puntos de la mitad izquierda y derecha
    double d = min(dl, dr);
    puntosCerca = (dl < dr) ? leftPair : rightPair;

    // Crea un segmento de puntos que están a una distancia menor que d del punto medio
    vector<vector<float>> segmento;
    for (size_t i = 0; i < n; i++) {
        if (abs(P[i][0] - midPoint[0]) < d) {
            segmento.push_back(P[i]);
        }
    }

    // Encuentra la distancia más pequeña en el segmento
    double segmentoDist = segmentoCerca(segmento, d, puntosCerca);
    if (segmentoDist < d) {
        d = segmentoDist;
    }

    return d;
}

// Función para encontrar la distancia más pequeña entre dos puntos
pair<vector<float>, vector<float>> cerca(vector<vector<float>>& P) {
    size_t n = P.size();
    sort(P.begin(), P.end(), [](const vector<float>& p1, const vector<float>& p2) {
        return p1[0] < p2[0];
    });

    pair<vector<float>, vector<float>> puntosCerca;
    masCerca(P, n, puntosCerca);
    return puntosCerca;
}

int main() {
    vector<vector<float>> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    pair<vector<float>, vector<float>> puntosCerca = cerca(P);
    cout << "The cerca pair of points are: (" << puntosCerca.first[0] << ", " << puntosCerca.first[1] << ") and ("
         << puntosCerca.second[0] << ", " << puntosCerca.second[1] << ")" << endl;
    return 0;
}



