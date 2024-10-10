#include <iostream>
#include <limits>
using namespace std;

template <typename T>
int orientation(T px, T py, T qx, T qy, T rx, T ry) {
    T val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // horario o antihorario
}

template <typename T>
bool onSegment(T px, T py, T qx, T qy, T rx, T ry) {
    if (qx <= max(px, rx) && qx >= min(px, rx) &&
        qy <= max(py, ry) && qy >= min(py, ry))
        return true;
    return false;
}

template <typename T>
bool intersection(T xa, T ya, T xb, T yb, T xc, T yc, T xd, T yd) {
    int o1 = orientation(xa, ya, xb, yb, xc, yc);
    int o2 = orientation(xa, ya, xb, yb, xd, yd);
    int o3 = orientation(xc, yc, xd, yd, xa, ya);
    int o4 = orientation(xc, yc, xd, yd, xb, yb);

    // Caso general
    if (o1 != o2 && o3 != o4)
        return true;

    // Casos especiales
    // A, B y C son colineares y C está en el segmento AB
    if (o1 == 0 && onSegment(xa, ya, xc, yc, xb, yb)) return true;

    // A, B y D son colineares y D está en el segmento AB
    if (o2 == 0 && onSegment(xa, ya, xd, yd, xb, yb)) return true;

    // C, D y A son colineares y A está en el segmento CD
    if (o3 == 0 && onSegment(xc, yc, xa, ya, xd, yd)) return true;

    // C, D y B son colineares y B está en el segmento CD
    if (o4 == 0 && onSegment(xc, yc, xb, yb, xd, yd)) return true;

    return false; // No se intersectan
}

// Sobrecarga para tipos específicos
bool intersection(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd) {
    return intersection<int>(xa, ya, xb, yb, xc, yc, xd, yd);
}

bool intersection(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd) {
    return intersection<double>(xa, ya, xb, yb, xc, yc, xd, yd);
}
