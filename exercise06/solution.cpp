#include<iostream>
#include<vector>
#include<algorithm>
#include <cstdlib>   // Para rand() y srand()
#include <ctime>     // Para time()
#include<opencv2/opencv.hpp>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;


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

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};


int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

vector<Point> jarvis_march(vector<Point> points) {
    int n = points.size();
    if (n < 3) return {};  // No se puede formar una envolvente convexa con menos de 3 puntos

    vector<Point> hull;

    // Encuentra el punto más a la izquierda
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x) {
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
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        // Mueve al siguiente punto
        p = q;

    } while (p != leftmost);  // Se detiene cuando volvemos al punto inicial

    return hull;
}

// Función para encontrar el cuadrado de la distancia entre dos puntos
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Variable global para el punto de referencia
Point p0(0, 0);

// Función de comparación para ordenar los puntos por ángulo polar
bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0)  // Si son colineales, el más cercano al p0 va primero
        return distSq(p0, p2) >= distSq(p0, p1);
    return o == 2;  // Ordenar en sentido antihorario
}

// Función principal para el algoritmo de Graham Scan
vector<Point> graham_scan(vector<Point> points) {
    int n = points.size();
    if (n < 3) return {};  // No se puede formar una envolvente convexa con menos de 3 puntos

    // Encuentra el punto más abajo (y más a la izquierda en caso de empate)
    int ymin = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (y == ymin && points[i].x < points[minIdx].x)) {
            ymin = points[i].y;
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
    vector<Point> hull;
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

// Puntos aleatorios dentro de un círculo
vector<Point> points_in_circle(int n, int radius) {
    vector<Point> points_circle;
    for (int i = 0; i < n; ++i) {
        double angle = static_cast<double>(rand()) / RAND_MAX * 2 * CV_PI;
        double r = sqrt(static_cast<double>(rand()) / RAND_MAX) * radius;
        int x = static_cast<int>(r * cos(angle));
        int y = static_cast<int>(r * sin(angle));
        points_circle.push_back(Point(x, y));
    }
    return points_circle;
}

// Puntos aleatorios en el borde de un círculo
vector<Point> points_on_circle(int n, int radius) {
    vector<Point> points_circle;
    for (int i = 0; i < n; ++i) {
        double angle = static_cast<double>(rand()) / RAND_MAX * 2 * CV_PI;
        int x = static_cast<int>(radius * cos(angle));
        int y = static_cast<int>(radius * sin(angle));
        points_circle.push_back(Point(x, y));
    }
    return points_circle;
}

// Puntos aleatorios dentro de un rectángulo
vector<Point> points_in_rectangle(int n, int width, int height) {
    vector<Point> points_rect;
    for (int i = 0; i < n; ++i) {
        int x = rand() % width - width / 2;
        int y = rand() % height - height / 2;
        points_rect.push_back(Point(x, y));
    }
    return points_rect;
}

// Puntos aleatorios en el borde de un rectángulo
vector<Point> points_on_rectangle(int n, int width, int height) {
    vector<Point> points_rect;
    for (int i = 0; i < n; ++i) {
        int side = rand() % 4;
        int x, y;
        switch (side) {
            case 0:  // Superior
                x = rand() % width - width / 2;
                y = height / 2;
                break;
            case 1:  // Derecha
                x = width / 2;
                y = rand() % height - height / 2;
                break;
            case 2:  // Inferior
                x = rand() % width - width / 2;
                y = -height / 2;
                break;
            case 3:  // Izquierda
                x = -width / 2;
                y = rand() % height - height / 2;
                break;
        }
        points_rect.push_back(Point(x, y));
    }
    return points_rect;
}

// Putos aleatorios dentro de una parábola
vector<Point> points_in_parabola(int n, int width, int height) {
    vector<Point> points_parabola;
    for (int i = 0; i < n; ++i) {
        int x = rand() % width - width / 2;
        int y = rand() % height - height / 2;
        if (y >= x * x) {
            points_parabola.push_back(Point(x, y));
        }
    }
    return points_parabola;
}

// Puntos aleatorios en una parábola
vector<Point> points_on_parabola(int n, int width, int height) {
    vector<Point> points_parabola;
    for (int i = 0; i < n; ++i) {
        int side = rand() % 2;
        int x, y;
        if (side == 0) {
            x = rand() % width - width / 2;
            y = x * x;
        } else {
            y = rand() % height - height / 2;
            x = sqrt(y);
        }
        points_parabola.push_back(Point(x, y));
    }
    return points_parabola;
}


// Función para medir el tiempo de ejecución
template <typename Func>
double measure_runtime(Func func, vector<Point> &points) {
    auto start = high_resolution_clock::now();
    func(points);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();  // Tiempo en milisegundos
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Tamaños de puntos a probar
    vector<int> sizes = {1000, 10000, 100000, 1000000, 2000000, 5000000};

    // Disposiciones de puntos
    vector<string> types = {
        "points in a circle",
        "points border circle",
        "points in a rectangle",
        "points border rectangle"
    };

    cout << setw(35) << left << "Test Case" << setw(15) << "Size"
         << setw(20) << "Jarvis March (ms)" << setw(20) << "Graham Scan (ms)" << endl;
    cout << string(90, '-') << endl;

    for (int size : sizes) {
        for (const string &type : types) {
            vector<Point> points;

            // Generar puntos según el tipo
            if (type == "random points in a circle")
                points = points_in_circle(size, 500);
            else if (type == "random points on the border of a circle")
                points = points_on_circle(size, 500);
            else if (type == "random points in a rectangle")
                points = points_in_rectangle(size, 1000, 1000);
            else if (type == "random points on the border of a rectangle")
                points = points_on_rectangle(size, 1000, 1000);

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