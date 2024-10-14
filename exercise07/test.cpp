#include <gtest/gtest.h>
#include <vector>

template <typename T>
bool exist_intersections(const std::vector<std::vector<T>>& segments);

TEST(IntersectionTest, NoIntersection) {
    std::vector<std::vector<int>> segments = {
        {0, 0, 1, 1},
        {2, 2, 3, 3}
    };
    EXPECT_FALSE(exist_intersections(segments));
}

// TEST(IntersectionTest, OneIntersection) {
//     std::vector<std::vector<int>> segments = {
//         {0, 0, 1, 1},
//         {1, 0, 0, 1}
//     };
//     EXPECT_TRUE(exist_intersections(segments));
// }

TEST(IntersectionTest, CollinearSegments) {
    std::vector<std::vector<int>> segments = {
        {0, 0, 2, 2},
        {1, 1, 3, 3}
    };
    EXPECT_TRUE(exist_intersections(segments));
}

TEST(IntersectionTest, DoublePrecision) {
    std::vector<std::vector<double>> segments = {
        {0.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0, 1.0}
    };
    EXPECT_TRUE(exist_intersections(segments));
}

TEST(IntersectionTest, IntMaxMin) {
    std::vector<std::vector<int>> segments = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}
    };
    EXPECT_TRUE(exist_intersections(segments));
}

TEST(IntersectionTest, DoubleMaxMin) {
    std::vector<std::vector<double>> segments = {
        {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max()},
        {std::numeric_limits<double>::max(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()}
    };
    EXPECT_TRUE(exist_intersections(segments));
}

TEST(IntersectionTest, IntNoIntersection) {
    std::vector<std::vector<int>> segments = {
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), 0, 0},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 1, 1}
    };
    EXPECT_FALSE(exist_intersections(segments));
}

TEST(IntersectionTest, DoubleNoIntersection) {
    std::vector<std::vector<double>> segments = {
        {std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), 0.0, 0.0},
        {std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 1.0, 1.0}
    };
    EXPECT_FALSE(exist_intersections(segments));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
