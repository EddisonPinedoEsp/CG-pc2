#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include <vector>

using namespace std;


bool inside_triangle(vector<vector<int>> const& vertices, int px, int py);
bool inside_triangle(vector<vector<double>> const& vertices, double px, double py);

TEST(InsideTriangleTestInt, PointInside) {
    vector<vector<int>> vertices = {{0, 0}, {5, 0}, {0, 5}};
    EXPECT_TRUE(inside_triangle(vertices, 1, 1));
}

TEST(InsideTriangleTestInt, PointOutside) {
    vector<vector<int>> vertices = {{0, 0}, {5, 0}, {0, 5}};
    EXPECT_FALSE(inside_triangle(vertices, 6, 6));
}

TEST(InsideTriangleTestInt, PointOnEdge) {
    vector<vector<int>> vertices = {{0, 0}, {5, 0}, {0, 5}};
    EXPECT_TRUE(inside_triangle(vertices, 2, 0));
}

TEST(InsideTriangleTestInt, PointAtVertex) {
    vector<vector<int>> vertices = {{0, 0}, {5, 0}, {0, 5}};
    EXPECT_TRUE(inside_triangle(vertices, 0, 0));
}

TEST(InsideTriangleTestInt, LargeCoordinates) {
    vector<vector<int>> vertices = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()},
        {0, std::numeric_limits<int>::max()}
    };
    EXPECT_TRUE(inside_triangle(vertices, 0, 0));
}

TEST(InsideTriangleTestDouble, PointInside) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_triangle(vertices, 1.0, 1.0));
}

TEST(InsideTriangleTestDouble, PointOutside) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {0.0, 5.0}};
    EXPECT_FALSE(inside_triangle(vertices, 6.0, 6.0));
}

TEST(InsideTriangleTestDouble, PointOnEdge) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_triangle(vertices, 2.5, 0.0));
}

TEST(InsideTriangleTestDouble, PointAtVertex) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_triangle(vertices, 0.0, 0.0));
}

TEST(InsideTriangleTestDouble, LargeCoordinates) {
    vector<vector<double>> vertices = {
        {-1e308, -1e308},
        {1e308, -1e308},
        {0.0, 1e308}
    };
    EXPECT_TRUE(inside_triangle(vertices, 0.0, 0.0));
}

TEST(InsideTriangleTestDouble, SmallCoordinates) {
    vector<vector<double>> vertices = {
        {-1.000000001, -1.000000001},
        {1.000000001, -1.000000001},
        {0.0, 1.000000001}
    };
    EXPECT_TRUE(inside_triangle(vertices, 0.0, 0.0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
