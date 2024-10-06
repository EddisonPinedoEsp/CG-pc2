#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Mock function to simulate area_poligono behavior for testing
float area_poligono(const vector<vector<float>>& poligono);

TEST(AreaPoligonoTest, Triangulo) {
    vector<vector<float>> poligono = {{0, 0}, {4, 0}, {2, 3}};
    float result = area_poligono(poligono);
    cout << "Triangulo: Área -> " << result << endl;
    EXPECT_NEAR(result, 6.0, 1e-5);
}

TEST(AreaPoligonoTest, Cuadrilatero) {
    vector<vector<float>> poligono = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    float result = area_poligono(poligono);
    cout << "Cuadrilatero: Área -> " << result << endl;
    EXPECT_NEAR(result, 12.0, 1e-5);
}

TEST(AreaPoligonoTest, Pentagono) {
    vector<vector<float>> poligono = {{0, 0}, {4, 0}, {5, 3}, {2, 5}, {-1, 3}};
    float result = area_poligono(poligono);
    cout << "Pentagono: Área -> " << result << endl;
    EXPECT_NEAR(result, 21, 1e-5);
}

TEST(AreaPoligonoTest, Hexagono) {
    vector<vector<float>> poligono = {{0, 0}, {2, 0}, {3, 2}, {2, 4}, {0, 4}, {-1, 2}};
    float result = area_poligono(poligono);
    cout << "Hexagono: Área -> " << result << endl;
    EXPECT_NEAR(result, 12.0, 1e-5);
}

TEST(AreaPoligonoTest, PoligonoGrande) {
    vector<vector<float>> poligono = {{0, 0}, {4, 0}, {4, 4}, {2, 6}, {0, 4}};
    float result = area_poligono(poligono);
    cout << "PoligonoGrande: Área -> " << result << endl;
    EXPECT_NEAR(result, 20.0, 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
