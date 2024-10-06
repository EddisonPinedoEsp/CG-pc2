#include <gtest/gtest.h>
#include <vector>
#include <iostream>

using namespace std;

// Mock function to simulate numeroTriangulaciones behavior for testing
int numeroTriangulaciones(vector<vector<float>> poligono);

TEST(NumeroTriangulacionesTest, Triangulo) {
    vector<vector<float>> poligono = {{0, 0}, {1, 0}, {0, 1}};
    int result = numeroTriangulaciones(poligono);
    cout << "Triangulo: Número de triangulaciones -> " << result << endl;
    EXPECT_EQ(result, 1);
}

TEST(NumeroTriangulacionesTest, Cuadrilatero) {
    vector<vector<float>> poligono = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    int result = numeroTriangulaciones(poligono);
    cout << "Cuadrilatero: Número de triangulaciones -> " << result << endl;
    EXPECT_EQ(result, 2);
}

TEST(NumeroTriangulacionesTest, Pentagono) {
    vector<vector<float>> poligono = {{0, 0}, {1, 0}, {1.5, 1}, {0.5, 1.5}, {-0.5, 1}};
    int result = numeroTriangulaciones(poligono);
    cout << "Pentagono: Número de triangulaciones -> " << result << endl;
    EXPECT_EQ(result, 5);
}

TEST(NumeroTriangulacionesTest, Hexagono) {
    vector<vector<float>> poligono = {{0, 0}, {1, 0}, {2, 1}, {1, 2}, {0, 2}, {-1, 1}};
    int result = numeroTriangulaciones(poligono);
    cout << "Hexagono: Número de triangulaciones -> " << result << endl;
    EXPECT_EQ(result, 14);
}

TEST(NumeroTriangulacionesTest, PoligonoGrande) {
    vector<vector<float>> poligono = {{0, 0}, {1, 0}, {2, 1}, {3, 2}, {2, 3}, {1, 3}, {0, 2}, {-1, 1}};
    int result = numeroTriangulaciones(poligono);
    cout << "PoligonoGrande: Número de triangulaciones -> " << result << endl;
    EXPECT_EQ(result, 42); // Número esperado basado en los números de Catalan
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

