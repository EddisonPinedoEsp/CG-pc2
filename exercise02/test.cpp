#include <gtest/gtest.h>
#include <vector>
using namespace std;

bool is_convex(vector<vector<int>> const& P);
bool is_convex(vector<vector<double>> const& P);

TEST(IsConvexTestInt, ConvexPolygon) {
    vector<vector<int>> P = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    EXPECT_TRUE(is_convex(P));
}

TEST(IsConvexTestInt, ConcavePolygon) {
    vector<vector<int>> P = {{0, 0}, {4, 0}, {2, 2}, {4, 4}, {0, 4}};
    EXPECT_FALSE(is_convex(P));
}

TEST(IsConvexTestInt, ColinearPoints) {
    vector<vector<int>> P = {{0, 0}, {2, 2}, {4, 4}};
    EXPECT_FALSE(is_convex(P));
}

TEST(IsConvexTestInt, LargeCoordinates) {
    vector<vector<int>> P = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}
    };
    EXPECT_TRUE(is_convex(P));
}

TEST(IsConvexTestDouble, ConvexPolygon) {
    vector<vector<double>> P = {{0.0, 0.0}, {4.0, 0.0}, {4.0, 4.0}, {0.0, 4.0}};
    EXPECT_TRUE(is_convex(P));
}

TEST(IsConvexTestDouble, ConcavePolygon) {
    vector<vector<double>> P = {{0.0, 0.0}, {4.0, 0.0}, {2.0, 2.0}, {4.0, 4.0}, {0.0, 4.0}};
    EXPECT_FALSE(is_convex(P));
}

TEST(IsConvexTestDouble, ColinearPoints) {
    vector<vector<double>> P = {{0.0, 0.0}, {2.0, 2.0}, {4.0, 4.0}};
    EXPECT_FALSE(is_convex(P));
}

TEST(IsConvexTestDouble, LargeCoordinates) {
    vector<vector<double>> P = {
        {-1e308, -1e308},
        {1e308, -1e308},
        {1e308, 1e308},
        {-1e308, 1e308}
    };
    EXPECT_TRUE(is_convex(P));
}

TEST(IsConvexTestDouble, SmallCoordinates) {
    vector<vector<double>> P = {
        {-1.000000001, -1.000000001},
        {1.000000001, -1.000000001},
        {1.000000001, 1.000000001},
        {-1.000000001, 1.000000001}
    };
    EXPECT_TRUE(is_convex(P));
}