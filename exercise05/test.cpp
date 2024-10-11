#include <gtest/gtest.h>
#include <limits>
#include <vector>

using namespace std;

bool inside_polygon(const vector<vector<int>>& vertices, int px, int py);
bool inside_polygon(const vector<vector<double>>& vertices, double px, double py);

TEST(InsidePolygonTestInt, PointInsideOutsite) {
    vector<vector<int>> vertices = {{0, 0}, {5, 0}, {5, 5}, {0, 5}};
    
    EXPECT_TRUE(inside_polygon(vertices, 2, 2));
    EXPECT_TRUE(inside_polygon(vertices, 0, 0));
    EXPECT_TRUE(inside_polygon(vertices, 5, 0));
    EXPECT_TRUE(inside_polygon(vertices, 5, 5));
    EXPECT_TRUE(inside_polygon(vertices, 0, 5));
    EXPECT_FALSE(inside_polygon(vertices, 6, 6));
    EXPECT_TRUE(inside_polygon(vertices, 5, 2));
}

TEST(InsidePolygonTestInt, LargeCoordinates) {
    vector<vector<int>> vertices = {
        {numeric_limits<int>::min(), numeric_limits<int>::min()},
        {numeric_limits<int>::max(), numeric_limits<int>::min()},
        {numeric_limits<int>::max(), numeric_limits<int>::max()},
        {numeric_limits<int>::min(), numeric_limits<int>::max()}
    };
    
    EXPECT_TRUE(inside_polygon(vertices, 0, 0));
    
    // vertices
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::min(), numeric_limits<int>::min()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::max(), numeric_limits<int>::min()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::max(), numeric_limits<int>::max()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::min(), numeric_limits<int>::max()));

    // bordes
    EXPECT_TRUE(inside_polygon(vertices, 0, numeric_limits<int>::min()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::max(), 0));
    EXPECT_TRUE(inside_polygon(vertices, 0, numeric_limits<int>::max()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<int>::min(), 0));


    // dentro
    EXPECT_TRUE(inside_polygon(vertices, 5, 5));
    EXPECT_TRUE(inside_polygon(vertices, 99, 99));
    EXPECT_TRUE(inside_polygon(vertices, -99, -99));
    EXPECT_TRUE(inside_polygon(vertices, 1000, 10000));

}

TEST(InsidePolygonTestDouble, PointInside) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_polygon(vertices, 2.0, 2.0));
}

TEST(InsidePolygonTestDouble, PointOutside) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}};
    EXPECT_FALSE(inside_polygon(vertices, 6.0, 6.0));
}

TEST(InsidePolygonTestDouble, PointOnEdge) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_polygon(vertices, 5.0, 2.0));
}

TEST(InsidePolygonTestDouble, PointAtVertex) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {5.0, 0.0}, {5.0, 5.0}, {0.0, 5.0}};
    EXPECT_TRUE(inside_polygon(vertices, 0.0, 0.0));
}

TEST(InsidePolygonTestDouble, LargeCoordinates) {
    vector<vector<double>> vertices = {
        {-1e308, -1e308},
        {1e308, -1e308},
        {1e308, 1e308},
        {-1e308, 1e308}
    };
    EXPECT_TRUE(inside_polygon(vertices, 0.0, 0.0));
}

TEST(InsidePolygonTestDouble, SmallCoordinates) {
    vector<vector<double>> vertices = {
        {-1.000000001, -1.000000001},
        {1.000000001, -1.000000001},
        {1.000000001, 1.000000001},
        {-1.000000001, 1.000000001}
    };
    EXPECT_TRUE(inside_polygon(vertices, 0.0, 0.0));
}

TEST(InsidePolygonTestDouble, ExhaustiveTest) {
    vector<vector<double>> vertices = {
        {-numeric_limits<double>::max(), -numeric_limits<double>::max()},
        {numeric_limits<double>::max(), -numeric_limits<double>::max()},
        {numeric_limits<double>::max(), numeric_limits<double>::max()},
        {-numeric_limits<double>::max(), numeric_limits<double>::max()}
    };
    EXPECT_TRUE(inside_polygon(vertices, 0.0, 0.0));
    EXPECT_TRUE(inside_polygon(vertices, -numeric_limits<double>::max(), -numeric_limits<double>::max()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<double>::max(), -numeric_limits<double>::max()));
    EXPECT_TRUE(inside_polygon(vertices, numeric_limits<double>::max(), numeric_limits<double>::max()));
    EXPECT_TRUE(inside_polygon(vertices, -numeric_limits<double>::max(), numeric_limits<double>::max()));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
