#include <cmath>

double distance_point_to_line_3D(double p1x, double p1y, double p1z,  // Punto P1
                                 double dx, double dy, double dz,     // Dirección de la línea
                                 double px, double py, double pz) {   // Punto P
    // Vector P1 -> P
    long double vx = px - p1x;
    long double vy = py - p1y;
    long double vz = pz - p1z;

    // Producto cruzado entre el vector dirección D y el vector P1 -> P
    long double cross_x = vy * dz - vz * dy;
    long double cross_y = vz * dx - vx * dz;
    long double cross_z = vx * dy - vy * dx;

    // Magnitud del producto cruzado |(P1 -> P) × D|
    long double cross_magnitude = std::sqrt(cross_x * cross_x + cross_y * cross_y + cross_z * cross_z);

    // Magnitud del vector de dirección |D|
    long double direction_magnitude = std::sqrt(dx * dx + dy * dy + dz * dz);

    // Distancia = |(P1 -> P) × D| / |D|
    return cross_magnitude / direction_magnitude;
}