// #include<opencv2/opencv.hpp>
#include<iostream>
#include<iomanip>
#include<vector>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#ifndef M_PI
#endif

// Jarvis March Algorithm
int orientacion(vector<float> p, vector<float> q, vector<float> r) {
    float val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

vector<vector<float>> jarvis_march(vector<vector<float>> puntos) {
    int n = puntos.size();
    if (n < 3) return {};

    vector<vector<float>> hull;

    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (puntos[i][0] < puntos[leftmost][0]) {
            leftmost = i;
        }
    }

    int p = leftmost, q;
    do {
        hull.push_back(puntos[p]);

        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientacion(puntos[p], puntos[i], puntos[q]) == 2) {
                q = i;
            }
        }

        p = q;

    } while (p != leftmost); 

    return hull;
}


// Graham Scan Algorithm
float distSq(float x1, float y1, float x2, float y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// Variable global para el punto de referencia
vector<float> p0(2, 0.0);

bool compara(vector<float> p1, vector<float> p2) {
    int o = orientacion(p0, p1, p2);
    if (o == 0) {
        return distSq(p0[0], p0[1], p1[0], p1[1]) < distSq(p0[0], p0[1], p2[0], p2[1]);
    }
    return o == 2;
}

vector<vector<float>> graham_scan(vector<vector<float>> puntos) {
    int n = puntos.size();
    if (n < 3) return {};

    float ymin = puntos[0][1];
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        float y = puntos[i][1];
        if ((y < ymin) || (ymin == y && puntos[i][0] < puntos[minIdx][0])) {
            ymin = puntos[i][1];
            minIdx = i;
        }
    }

    swap(puntos[0], puntos[minIdx]);
    p0 = puntos[0];


    sort(puntos.begin() + 1, puntos.end(), compara);

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientacion(p0, puntos[i], puntos[i + 1]) == 0)
            i++;
        puntos[m] = puntos[i];
        m++;
    }

    if (m < 3) return {};

    vector<vector<float>> hull;
    hull.push_back(puntos[0]);
    hull.push_back(puntos[1]);
    hull.push_back(puntos[2]);

    for (int i = 3; i < m; i++) {
        while (hull.size() > 1 && orientacion(hull[hull.size() - 2], hull[hull.size() - 1], puntos[i]) != 2)
            hull.pop_back();
        hull.push_back(puntos[i]);
    }

    return hull;
}
// **


// Implementación de las disposiciones de puntos
// **
// Puntos aleatorios dentro de un círculo
vector<vector<float>> puntos_in_circle(int n, int radius) {
    vector<vector<float>> puntos;
    puntos.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x, y;
        do {
            x = static_cast<float>(rand()) / RAND_MAX * 2 * radius - radius;
            y = static_cast<float>(rand()) / RAND_MAX * 2 * radius - radius;
        } while (x * x + y * y > radius * radius);
        
        puntos.push_back({x, y});
    }

    return puntos;
}

// Puntos aleatorios en el borde de un círculo
vector<vector<float>> puntos_on_circle(int n, int radius) {
    vector<vector<float>> puntos_circle;
    puntos_circle.reserve(n);

    for (int i = 0; i < n; ++i) {
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        puntos_circle.push_back({x, y});
    }

    return puntos_circle;
}

// Puntos aleatorios dentro de un rectángulo
vector<vector<float>> puntos_in_rectangle(int n, int width, int height) {
    vector<vector<float>> puntos_rect;
    puntos_rect.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * width;
        float y = static_cast<float>(rand()) / RAND_MAX * height;
        puntos_rect.push_back({x, y});
    }

    return puntos_rect;
}

// Puntos aleatorios en el borde de un rectángulo
vector<vector<float>> puntos_on_rectangle(int n, int width, int height) {
    vector<vector<float>> puntos_rect;
    puntos_rect.reserve(n);

    for (int i = 0; i < n; ++i) {
        int edge = rand() % 4;
        float x, y;
        switch (edge) {
            case 0: // Borde superior
                x = static_cast<float>(rand()) / RAND_MAX * width;
                y = 0;
                break;
            case 1: // Borde inferior
                x = static_cast<float>(rand()) / RAND_MAX * width;
                y = height;
                break;
            case 2: // Borde izquierdo
                x = 0;
                y = static_cast<float>(rand()) / RAND_MAX * height;
                break;
            case 3: // Borde derecho
                x = width;
                y = static_cast<float>(rand()) / RAND_MAX * height;
                break;
        }
        puntos_rect.push_back({x, y});
    }

    return puntos_rect;
}

// Puntos aleatorios dentro de una región limitada por una parábola
vector<vector<float>> puntos_in_parabola(int n, float a, float x_max) {
    vector<vector<float>> puntos_parabola;
    puntos_parabola.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2 * x_max - x_max;
        float y = static_cast<float>(rand()) / RAND_MAX * a * x * x;
        puntos_parabola.push_back({x, y});
    }

    return puntos_parabola;
}

// Puntos aleatorios en una parábola
vector<vector<float>> puntos_on_parabola(int n, float a, float x_max) {
    vector<vector<float>> puntos_parabola;
    puntos_parabola.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2 * x_max - x_max;
        float y = a * x * x;
        puntos_parabola.push_back({x, y});
    }

    return puntos_parabola;
}

// **


// Función para medir el tiempo de ejecución
template <typename Func>
double measure_runtime(Func func, vector<vector<float>> &puntos) {
    auto start = high_resolution_clock::now();
    func(puntos);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();  // Tiempo en milisegundos
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Tamaños de puntos a probar
    vector<int> sizes = {
                        // 1000, 
                        // 10000, 
                        100000, 
                        // 1000000, 
                        // 2000000, 
                        // 5000000
                        };

    // Disposiciones de puntos
    vector<string> types = {
        "puntos in a circle",
        "puntos border circle",
        "puntos in a rectangle",
        "puntos border rectangle",
        "puntos in a parabola",
        "puntos on a parabola",

    };

    cout << setw(35) << left << "Test Case" << setw(15) << "Size"
        << setw(20) << "Jarvis March (ms)" << setw(20) << "Graham Scan (ms)" << endl;
    cout << string(90, '-') << endl;

    for (int size : sizes) {
        for (const string &type : types) {
            vector<vector<float>> puntos;

            // Generar puntos según el tipo
            if (type == "puntos in a circle")
                puntos = puntos_in_circle(size, 1000);
            else if (type == "puntos border circle")
                puntos = puntos_on_circle(size, 1000);
            else if (type == "puntos in a rectangle")
                puntos = puntos_in_rectangle(size, 1000, 1000);
            else if (type == "random border rectangle")
                puntos = puntos_on_rectangle(size, 1000, 1000);
            else if (type == "puntos in a parabola")
                puntos = puntos_in_parabola(size, 0.1, 1000);
            else if (type == "puntos on a parabola")
                puntos = puntos_on_parabola(size, 0.1, 1000);

            // Medir el tiempo de ejecución para Jarvis March
            double jarvis_time = measure_runtime(jarvis_march, puntos);

            // Medir el tiempo de ejecución para Graham Scan
            double graham_time = measure_runtime(graham_scan, puntos);

            // Imprimir resultados en formato tabla
            cout << setw(35) << left << type << setw(15) << size
                << setw(20) << jarvis_time << setw(20) << graham_time << endl;
        }
    }

    return 0;
}