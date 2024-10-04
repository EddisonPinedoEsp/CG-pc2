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
#define M_PI 3.14159265358979323846
#endif


// Implement the Jarvis march and the Graham scan, with and without interior points removal.
// Measure the runtime of each algorithm with the same inputs, containing 1k, 10k,
// 100k, 1M, 2M, 5M points. Consider different disposition for the points in the inputs:
// • random points in a circle
// • random points in the border of a circle
// • random points in a rectangle
// • random points in the border of a rectangle
// • random points inside a region limited by a parabola
// • random points on a parabola.
// Make a table comparing the runtimes.



// Jarvis March Algorithm
// **
int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    float ori = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);

    if (ori == 0) return 0;
    return (ori > 0) ? 1 : 2;
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

// **

// Graham Scan Algorithm

// **
// Función para encontrar el cuadrado de la distancia entre dos puntos
float distSq(float x1, float y1, float x2, float y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

// Variable global para el punto de referencia
vector<float> p0(2, 0.0);

// Función de orientación
int orientation(vector<float> p, vector<float> q, vector<float> r) {
    float val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Función de comparación para ordenar los puntos por ángulo polar
bool compare(vector<float> p1, vector<float> p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) {
        return distSq(p0[0], p0[1], p1[0], p1[1]) < distSq(p0[0], p0[1], p2[0], p2[1]);
    }
    return o == 2;
}

// Función principal para el algoritmo de Graham Scan
vector<vector<float>> graham_scan(vector<vector<float>> points) {
    int n = points.size();
    if (n < 3) return {};  // No se puede formar una envolvente convexa con menos de 3 puntos

    // Encuentra el punto más abajo (y más a la izquierda en caso de empate)
    float ymin = points[0][1];
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        float y = points[i][1];
        if ((y < ymin) || (ymin == y && points[i][0] < points[minIdx][0])) {
            ymin = points[i][1];
            minIdx = i;
        }
    }

    // Coloca el punto más bajo en la primera posición
    swap(points[0], points[minIdx]);
    p0 = points[0];

    // Ordena los puntos según el ángulo polar con p0
    sort(points.begin() + 1, points.end(), compare);

    // Si después de ordenar hay puntos colineales al inicio, ignóralos
    int m = 1;  // Contador de puntos válidos
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    if (m < 3) return {};  // Si hay menos de 3 puntos en la envolvente, no es posible

    // Usa una pila para almacenar los puntos de la envolvente
    vector<vector<float>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    // Recorre los puntos restantes
    for (int i = 3; i < m; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2)
            hull.pop_back();  // Elimina el punto si forma un giro en sentido horario
        hull.push_back(points[i]);
    }

    return hull;
}
// **


// Implementación de las disposiciones de puntos
// **
// Puntos aleatorios dentro de un círculo
vector<vector<float>> points_in_circle(int n, int radius) {
    vector<vector<float>> points;
    points.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x, y;
        do {
            x = static_cast<float>(rand()) / RAND_MAX * 2 * radius - radius;
            y = static_cast<float>(rand()) / RAND_MAX * 2 * radius - radius;
        } while (x * x + y * y > radius * radius);
        
        points.push_back({x, y});
    }

    return points;
}

// Puntos aleatorios en el borde de un círculo
vector<vector<float>> points_on_circle(int n, int radius) {
    vector<vector<float>> points_circle;
    points_circle.reserve(n);

    for (int i = 0; i < n; ++i) {
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        points_circle.push_back({x, y});
    }

    return points_circle;
}

// Puntos aleatorios dentro de un rectángulo
vector<vector<float>> points_in_rectangle(int n, int width, int height) {
    vector<vector<float>> points_rect;
    points_rect.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * width;
        float y = static_cast<float>(rand()) / RAND_MAX * height;
        points_rect.push_back({x, y});
    }

    return points_rect;
}

// Puntos aleatorios en el borde de un rectángulo
vector<vector<float>> points_on_rectangle(int n, int width, int height) {
    vector<vector<float>> points_rect;
    points_rect.reserve(n);

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
        points_rect.push_back({x, y});
    }

    return points_rect;
}

// Puntos aleatorios dentro de una región limitada por una parábola
vector<vector<float>> points_in_parabola(int n, float a, float x_max) {
    vector<vector<float>> points_parabola;
    points_parabola.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2 * x_max - x_max;
        float y = static_cast<float>(rand()) / RAND_MAX * a * x * x;
        points_parabola.push_back({x, y});
    }

    return points_parabola;
}

// Puntos aleatorios en una parábola
vector<vector<float>> points_on_parabola(int n, float a, float x_max) {
    vector<vector<float>> points_parabola;
    points_parabola.reserve(n);

    for (int i = 0; i < n; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * 2 * x_max - x_max;
        float y = a * x * x;
        points_parabola.push_back({x, y});
    }

    return points_parabola;
}

// **


// Función para medir el tiempo de ejecución
template <typename Func>
double measure_runtime(Func func, vector<vector<float>> &points) {
    auto start = high_resolution_clock::now();
    func(points);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();  // Tiempo en milisegundos
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Tamaños de puntos a probar
    vector<int> sizes = {
                        1000, 
                        10000, 
                        100000, 
                        1000000, 
                        2000000, 
                        5000000
                        };

    // Disposiciones de puntos
    vector<string> types = {
        "points in a circle",
        "points border circle",
        "points in a rectangle",
        "points border rectangle",
        "points in a parabola",
        "points on a parabola",

    };

    cout << setw(35) << left << "Test Case" << setw(15) << "Size"
        << setw(20) << "Jarvis March (ms)" << setw(20) << "Graham Scan (ms)" << endl;
    cout << string(90, '-') << endl;

    for (int size : sizes) {
        for (const string &type : types) {
            vector<vector<float>> points;

            // Generar puntos según el tipo
            if (type == "points in a circle")
                points = points_in_circle(size, 1000);
            else if (type == "points border circle")
                points = points_on_circle(size, 1000);
            else if (type == "points in a rectangle")
                points = points_in_rectangle(size, 1000, 1000);
            else if (type == "random border rectangle")
                points = points_on_rectangle(size, 1000, 1000);
            else if (type == "points in a parabola")
                points = points_in_parabola(size, 0.1, 1000);
            else if (type == "points on a parabola")
                points = points_on_parabola(size, 0.1, 1000);

            // Medir el tiempo de ejecución para Jarvis March
            double jarvis_time = measure_runtime(jarvis_march, points);

            // Medir el tiempo de ejecución para Graham Scan
            double graham_time = measure_runtime(graham_scan, points);

            // Imprimir resultados en formato tabla
            cout << setw(35) << left << type << setw(15) << size
                << setw(20) << jarvis_time << setw(20) << graham_time << endl;
        }
    }

    return 0;
}