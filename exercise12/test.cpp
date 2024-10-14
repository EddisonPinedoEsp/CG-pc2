#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Mock functions to simulate behavior for testing
double area_of_intersection(vector<vector<int>> const& vertices1, vector<vector<int>> const& vertices2);

TEST(CalcularAreaTest, InterseccionPoligonos) {
    vector<vector<int>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<int>> poligono2 = {{2, 2}, {6, 2}, {6, 6}, {2, 6}};
    double result = area_of_intersection(poligono1, poligono2);
    cout << "InterseccionPoligonos: Área -> " << result << endl;
    EXPECT_NEAR(result, 4.0, 1e-5); // Ajustar según la implementación real
}

TEST(CalcularAreaTest, InterseccionPoligonosDesplazados) {
    vector<vector<int>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<int>> poligono2 = {{5, 5}, {9, 5}, {9, 9}, {5, 9}};
    double result = area_of_intersection(poligono1, poligono2);
    cout << "InterseccionPoligonosDesplazados: Área -> " << result << endl;
    EXPECT_NEAR(result, 0.0, 1e-5); // No hay intersección
}

TEST(CalcularAreaTest, InterseccionPoligonosParcial) {
    vector<vector<int>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<int>> poligono2 = {{3, 3}, {7, 3}, {7, 7}, {3, 7}};
    double result = area_of_intersection(poligono1, poligono2);
    cout << "InterseccionPoligonosParcial: Área -> " << result << endl;
    EXPECT_NEAR(result, 1.0, 1e-5); // Ajustar según la implementación real
}

TEST(CalcularAreaTest, InterseccionPoligonosCompleta) {
    vector<vector<int>> poligono1 = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<vector<int>> poligono2 = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};
    double result = area_of_intersection(poligono1, poligono2);
    cout << "InterseccionPoligonosCompleta: Área -> " << result << endl;
    EXPECT_NEAR(result, 4.0, 1e-5); // Ajustar según la implementación real
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
