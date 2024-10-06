#include <gtest/gtest.h>
#include <vector>

using namespace std;

// Mock function to simulate punto_en_triangulo behavior for testing
bool punto_en_triangulo(const vector<vector<float>>& T, const vector<float>& P);

TEST(PuntoEnTrianguloTest, InsideTriangle) {
    vector<vector<float>> T = {{0, 0}, {5, 0}, {0, 5}};
    vector<float> P = {1, 1};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, OnVertex) {
    vector<vector<float>> T = {{0, 0}, {5, 0}, {0, 5}};
    vector<float> P = {0, 0};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, OnEdge) {
    vector<vector<float>> T = {{0, 0}, {5, 0}, {0, 5}};
    vector<float> P = {2.5, 0};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, OutsideTriangle) {
    vector<vector<float>> T = {{0, 0}, {5, 0}, {0, 5}};
    vector<float> P = {6, 6};
    EXPECT_FALSE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, CollinearPoints) {
    vector<vector<float>> T = {{0, 0}, {5, 0}, {10, 0}};
    vector<float> P = {2.5, 0};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, NegativeCoordinates) {
    vector<vector<float>> T = {{-5, -5}, {0, 0}, {-5, 0}};
    vector<float> P = {-3, -2};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, CenterOfTriangle) {
    vector<vector<float>> T = {{0, 0}, {6, 0}, {0, 6}};
    vector<float> P = {2, 2};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, OnEdgeNotVertex) {
    vector<vector<float>> T = {{0, 0}, {6, 0}, {0, 6}};
    vector<float> P = {3, 0};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, NearEdgeOutside) {
    vector<vector<float>> T = {{0, 0}, {6, 0}, {0, 6}};
    vector<float> P = {6.1, 0};
    EXPECT_FALSE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, OnExtendedEdge) {
    vector<vector<float>> T = {{0, 0}, {6, 0}, {0, 6}};
    vector<float> P = {7, 0};
    EXPECT_FALSE(punto_en_triangulo(T, P));
}

TEST(PuntoEnTrianguloTest, FloatingPointPrecision) {
    vector<vector<float>> T = {{0, 0}, {6, 0}, {0, 6}};
    vector<float> P = {2.999999, 2.999999};
    EXPECT_TRUE(punto_en_triangulo(T, P));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
