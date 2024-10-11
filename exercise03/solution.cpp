#include <cmath>

double distance_point_to_line_3D(
    double p1x, double p1y, double p1z,  // punto P1
    double dx, double dy, double dz,     // dirección
    double px, double py, double pz      // punto P
) {
    // Usa la fórmula de la distancia entre un punto y una recta
    double x = px - p1x;
    double y = py - p1y;
    double z = pz - p1z;
    double t = (x * dx + y * dy + z * dz) / (dx * dx + dy * dy + dz * dz);
    double x1 = p1x + t * dx;
    double y1 = p1y + t * dy;
    double z1 = p1z + t * dz;
    double x2 = x1 - px;
    double y2 = y1 - py;
    double z2 = z1 - pz;
    return sqrt(x2 * x2 + y2 * y2 + z2 * z2);
}