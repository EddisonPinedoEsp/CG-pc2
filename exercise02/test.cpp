#include <gtest/gtest.h>
#include <vector>
using namespace std;

// Declaración de la función esConvexo
bool esConvexo(const vector<vector<float>>& polygon);

TEST(EsConvexoTest, ConvexPolygon) {
    vector<vector<float>> polygon = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    EXPECT_TRUE(esConvexo(polygon));
}

TEST(EsConvexoTest, ConcavePolygon) {
    vector<vector<float>> polygon = {{0, 0}, {2, 0}, {1, 1}, {2, 2}, {0, 2}};
    EXPECT_FALSE(esConvexo(polygon));
}

TEST(EsConvexoTest, Triangle) {
    vector<vector<float>> polygon = {{0, 0}, {1, 0}, {0.5, 1}};
    EXPECT_TRUE(esConvexo(polygon));
}

TEST(EsConvexoTest, Line) {
    vector<vector<float>> polygon = {{0, 0}, {1, 0}};
    EXPECT_FALSE(esConvexo(polygon));
}

TEST(EsConvexoTest, SinglePoint) {
    vector<vector<float>> polygon = {{0, 0}};
    EXPECT_FALSE(esConvexo(polygon));
}

TEST(EsConvexoTest, EmptyPolygon) {
    vector<vector<float>> polygon = {};
    EXPECT_FALSE(esConvexo(polygon));
}