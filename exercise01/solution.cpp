# include <iostream>
using namespace std;

int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    // Calcula el producto cruz para la orientación de tres puntos
    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);

    // Si el producto cruz es 0, los puntos son colineales
    if (orientation == 0) {
        return 0;
    }

    return (orientation > 0) ? 1 : 2;
}

bool enSegmento(float xa, float ya, float xb, float yb, float xc, float yc) {
    if (xc >= min(xa, xb) && xc <= max(xa, xb) && yc >= min(ya, yb) && yc <= max(ya, yb)) {
        return true;
    }

    return false;
}

bool intersecion(float xa, float ya, float xb, float yb, float xc, float yc, float xd, float yd) {
    // Encuentra las cuatro orientaciones necesarias para determinar si hay intersección
    float o1 = orientacion(xa, ya, xb, yb, xc, yc);
    float o2 = orientacion(xa, ya, xb, yb, xd, yd);
    float o3 = orientacion(xc, yc, xd, yd, xa, ya);
    float o4 = orientacion(xc, yc, xd, yd, xb, yb);

    // Caso general
    if (o1 != o2 && o3 != o4) {
        return true;
    }
    // Casos especiales
    // xa, ya y xb, yb son colineales y xc, yc está en el segmento
    if (o1 == 0 && enSegmento(xa, ya, xb, yb, xc, yc)) {
        return true;
    }

    // xa, ya y xb, yb son colineales y xd, yd está en el segmento
    if (o2 == 0 && enSegmento(xa, ya, xb, yb, xd, yd)) {
        return true;
    }

    // xc, yc y xd, yd son colineales y xa, ya está en el segmento
    if (o3 == 0 && enSegmento(xc, yc, xd, yd, xa, ya)) {
        return true;
    }

    // xc, yc y xd, yd son colineales y xb, yb está en el segmento
    if (o4 == 0 && enSegmento(xc, yc, xd, yd, xb, yb)) {
        return true;
    }
    
    return false;
}


void testTotal() {
    // Caso 1: Segmentos se interceptan
    if (intersecion(0, 0, 6, 4, 2, 0, 0, 2)) {
        cout << "Caso 1: Se interceptar\n";
    } else {
        cout << "Caso 1: No se interceptar\n";
    }
}

int main() {
    testTotal();
    return 0;
}






