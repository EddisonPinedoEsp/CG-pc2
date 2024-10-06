#include <gtest/gtest.h>
#include <vector>
#include <iostream>

using namespace std;

// Mock function to simulate punto_en_poligono behavior for testing
bool punto_en_poligono(const vector<vector<float>>& P, const vector<float>& A);

TEST(PuntoEnPoligonoTest, InsidePolygon) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    vector<float> A = {2, 2};
    bool result = punto_en_poligono(P, A);
    cout << "InsidePolygon: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, OnVertex) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    vector<float> A = {0, 0};
    bool result = punto_en_poligono(P, A);
    cout << "OnVertex: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, OnEdge) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    vector<float> A = {2.5, 0};
    bool result = punto_en_poligono(P, A);
    cout << "OnEdge: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, OutsidePolygon) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    vector<float> A = {6, 6};
    bool result = punto_en_poligono(P, A);
    cout << "OutsidePolygon: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(PuntoEnPoligonoTest, ComplexPolygonInside) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {3, 3}, {0, 5}};
    vector<float> A = {2, 2};
    bool result = punto_en_poligono(P, A);
    cout << "ComplexPolygonInside: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, ComplexPolygonOutside) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {3, 3}, {0, 5}};
    vector<float> A = {6, 6};
    bool result = punto_en_poligono(P, A);
    cout << "ComplexPolygonOutside: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(PuntoEnPoligonoTest, ConcavePolygonInside) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {3, 3}, {5, 5}, {0, 5}};
    vector<float> A = {1, 4};
    bool result = punto_en_poligono(P, A);
    cout << "ConcavePolygonInside: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, ConcavePolygonOutside) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {3, 3}, {5, 5}, {0, 5}};
    vector<float> A = {4, 2};
    bool result = punto_en_poligono(P, A);
    cout << "ConcavePolygonOutside: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(PuntoEnPoligonoTest, NegativeCoordinates) {
    vector<vector<float>> P = {{-5, -5}, {0, 0}, {-5, 0}, {0, -5}};
    vector<float> A = {-3, -2};
    bool result = punto_en_poligono(P, A);
    cout << "NegativeCoordinates: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(PuntoEnPoligonoTest, FloatingPointPrecision) {
    vector<vector<float>> P = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    vector<float> A = {2.999999, 2.999999};
    bool result = punto_en_poligono(P, A);
    cout << "FloatingPointPrecision: Punto (" << A[0] << ", " << A[1] << ") -> " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
