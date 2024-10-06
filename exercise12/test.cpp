#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Mock functions to simulate behavior for testing
float calcular_area(const vector<vector<float>>& poligono);
vector<vector<float>> puntos_de_interseccion(vector<vector<float>> poligono1, vector<vector<float>> poligono2);

TEST(CalcularAreaTest, InterseccionPoligonos) {
    vector<vector<float>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<float>> poligono2 = {{2, 2}, {6, 2}, {6, 6}, {2, 6}};
    vector<vector<float>> interseccion = puntos_de_interseccion(poligono1, poligono2);
    float result = calcular_area(interseccion);
    cout << "InterseccionPoligonos: Área -> " << result << endl;
    EXPECT_NEAR(result, 4.0, 1e-5); // Ajustar según la implementación real
}

TEST(CalcularAreaTest, InterseccionPoligonosDesplazados) {
    vector<vector<float>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<float>> poligono2 = {{5, 5}, {9, 5}, {9, 9}, {5, 9}};
    vector<vector<float>> interseccion = puntos_de_interseccion(poligono1, poligono2);
    float result = calcular_area(interseccion);
    cout << "InterseccionPoligonosDesplazados: Área -> " << result << endl;
    EXPECT_NEAR(result, 0.0, 1e-5); // No hay intersección
}

TEST(CalcularAreaTest, InterseccionPoligonosParcial) {
    vector<vector<float>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<float>> poligono2 = {{3, 3}, {7, 3}, {7, 7}, {3, 7}};
    vector<vector<float>> interseccion = puntos_de_interseccion(poligono1, poligono2);
    float result = calcular_area(interseccion);
    cout << "InterseccionPoligonosParcial: Área -> " << result << endl;
    EXPECT_NEAR(result, 1.0, 1e-5); // Ajustar según la implementación real
}

TEST(CalcularAreaTest, InterseccionPoligonosCompleta) {
    vector<vector<float>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<float>> poligono2 = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};
    vector<vector<float>> interseccion = puntos_de_interseccion(poligono1, poligono2);
    float result = calcular_area(interseccion);
    cout << "InterseccionPoligonosCompleta: Área -> " << result << endl;
    EXPECT_NEAR(result, 4.0, 1e-5); // Ajustar según la implementación real
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
