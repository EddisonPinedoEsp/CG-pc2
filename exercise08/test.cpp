#include <gtest/gtest.h>
#include <limits>
using namespace std;

vector<int> closest_points(vector<vector<int>> const& points);
vector<int> closest_points(vector<vector<double>> const& points);

TEST(ClosestPointsTestInt, SimpleCase) {
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 3}};
    vector<int> result = closest_points(points);
    vector<int> expected = {1, 2};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestInt, LargeCoordinates) {
    vector<vector<int>> points = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {0, 0}
    };
    vector<int> result = closest_points(points);
    vector<int> expected = {0, 1};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestDouble, SimpleCase) {
    vector<vector<double>> points = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}};
    vector<int> result = closest_points(points);
    vector<int> expected = {0, 1};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestDouble, LargeCoordinates) {
    vector<vector<double>> points = {
        {-1e308, -1e308},
        {1e38, 1e38},
        {0.0, 0.0}
    };
    vector<int> result = closest_points(points);
    vector<int> expected = {1, 2};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestDouble, SmallCoordinates) {
    vector<vector<double>> points = {
        {-1.000000001, -1.000000001},
        {1.000000001, 1.000000001},
        {0.0, 0.0}
    };
    vector<int> result = closest_points(points);
    vector<int> expected = {0, 2};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestInt, IdenticalPoints) {
    vector<vector<int>> points = {{0, 0}, {0, 0}, {1, 1}};
    vector<int> result = closest_points(points);
    vector<int> expected = {0, 1};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTestDouble, IdenticalPoints) {
    vector<vector<double>> points = {{0.0, 0.0}, {0.0, 0.0}, {1.0, 1.0}};
    vector<int> result = closest_points(points);
    vector<int> expected = {0, 1};
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
