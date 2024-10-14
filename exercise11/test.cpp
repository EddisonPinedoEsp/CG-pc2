#include <gtest/gtest.h>
#include <vector>
#include <limits>

using namespace std;

double area(vector<vector<int>> const& vertices);
double area(vector<vector<double>> const& vertices);

TEST(AreaTestInt, SimpleSquare) {
    vector<vector<int>> vertices = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    EXPECT_EQ(area(vertices), 16.0);
}

TEST(AreaTestInt, SimpleTriangle) {
    vector<vector<int>> vertices = {{0, 0}, {4, 0}, {2, 4}};
    EXPECT_NEAR(area(vertices), 8.0, 1e-9);
}

TEST(AreaTestInt, LargeCoordinates) {
    vector<vector<int>> vertices = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}
    };
    EXPECT_NEAR(area(vertices), 1.7014118346046923e+38, 1e+30);
}

TEST(AreaTestDouble, SimpleSquare) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {4.0, 0.0}, {4.0, 4.0}, {0.0, 4.0}};
    EXPECT_NEAR(area(vertices), 16.0, 1e-9);
}

TEST(AreaTestDouble, SimpleTriangle) {
    vector<vector<double>> vertices = {{0.0, 0.0}, {4.0, 0.0}, {2.0, 4.0}};
    EXPECT_NEAR(area(vertices), 8.0, 1e-9);
}

// TEST(AreaTestDouble, LargeCoordinates) {
//     vector<vector<double>> vertices = {
//         {-1e308, -1e308},
//         {1e308, -1e308},
//         {1e308, 1e308},
//         {-1e308, 1e308}
//     };
//     EXPECT_NEAR(area(vertices), 4*1e+76, 1e+30);
// }

TEST(AreaTestDouble, SmallCoordinates) {
    vector<vector<double>> vertices = {
        {-1.000000001, -1.000000001},
        {1.000000001, -1.000000001},
        {1.000000001, 1.000000001},
        {-1.000000001, 1.000000001}
    };
    EXPECT_NEAR(area(vertices), 4.000000004, 1e-9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
