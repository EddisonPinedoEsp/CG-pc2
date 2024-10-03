// Write a function that receives 4 points (given by their coordinates) a = (xa, ya), b = (xb, yb), c = (xc, yc), d = (xd, yd), and returns true if and only ab ∩ cd != ∅.
# include <iostream>

using namespace std;


int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    // Calcula el producto cruz para la orientación de tres puntos (xa, ya), (xb, yb), (xc, yc)

    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);

    // Si el producto cruz es 0, los puntos son colineales
    if (orientation == 0) {
        return 0;
    }

    return (orientation > 0) ? 1 : 2;
}

bool enSegmento(float xa, float ya, float xb, float yb, float xc, float yc) {
    // Verifica si el punto (xc, yc) está en el segmento (xa, ya) - (xb, yb)

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
    if (o1 == 0 && enSegmento(xa, ya, xb, yb, xc, yc)) {
        return true;
    }

    if (o2 == 0 && enSegmento(xa, ya, xb, yb, xd, yd)) {
        return true;
    }

    if (o3 == 0 && enSegmento(xc, yc, xd, yd, xa, ya)) {
        return true;
    }

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






