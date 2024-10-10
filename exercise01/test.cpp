#include <gtest/gtest.h>
#include <limits>
using namespace std;

bool intersection(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd);

bool intersection(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd);

TEST(IntersectionTestInt, ColinearOverlap) {
    int xa = 0, ya = 0;
    int xb = 10, yb = 10;
    int xc = 5, yc = 5;
    int xd = 15, yd = 15;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, ColinearNoOverlap) {
    int xa = 0, ya = 0;
    int xb = 10, yb = 10;
    int xc = 11, yc = 11;
    int xd = 20, yd = 20;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, TouchingAtEndpoint) {
    int xa = 0, ya = 0;
    int xb = 10, yb = 10;
    int xc = 10, yc = 10;
    int xd = 20, yd = 20;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, ParallelNoIntersection) {
    int xa = 0, ya = 0;
    int xb = 10, yb = 10;
    int xc = 0, yc = 1;
    int xd = 10, yd = 11;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, LargeCoordinates) {
    int xa = std::numeric_limits<int>::min(), ya = std::numeric_limits<int>::min();
    int xb = std::numeric_limits<int>::max(), yb = std::numeric_limits<int>::max();
    int xc = std::numeric_limits<int>::min(), yc = std::numeric_limits<int>::min() + 1;
    int xd = std::numeric_limits<int>::max(), yd = std::numeric_limits<int>::max() - 1;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, SmallCoordinates) {
    int xa = -1, ya = -1;
    int xb = 1, yb = 1;
    int xc = -1, yc = 1;
    int xd = 1, yd = -1;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestInt, NoIntersection) {
    int xa = 0, ya = 0;
    int xb = 1, yb = 1;
    int xc = 2, yc = 2;
    int xd = 3, yd = 3;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, EdgeCase) {
    double xa = numeric_limits<double>::lowest(), ya = numeric_limits<double>::lowest();
    double xb = numeric_limits<double>::max(), yb = numeric_limits<double>::max();
    double xc = numeric_limits<double>::lowest(), yc = numeric_limits<double>::lowest() + 1;
    double xd = numeric_limits<double>::max(), yd = numeric_limits<double>::max() - 1;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

// Aquí va la implementación de la función intersection

TEST(IntersectionTestDouble, ColinearOverlap) {
    double xa = 0.123456789, ya = 0.123456789;
    double xb = 10.987654321, yb = 10.987654321;
    double xc = 5.555555555, yc = 5.555555555;
    double xd = 15.444444444, yd = 15.444444444;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, ColinearNoOverlap) {
    double xa = 0.123456789, ya = 0.123456789;
    double xb = 10.987654321, yb = 10.987654321;
    double xc = 11.111111111, yc = 11.111111111;
    double xd = 20.222222222, yd = 20.222222222;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, TouchingAtEndpoint) {
    double xa = 0.123456789, ya = 0.123456789;
    double xb = 10.987654321, yb = 10.987654321;
    double xc = 10.987654321, yc = 10.987654321;
    double xd = 20.222222222, yd = 20.222222222;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, ParallelNoIntersection) {
    double xa = 0.123456789, ya = 0.123456789;
    double xb = 10.987654321, yb = 10.987654321;
    double xc = 0.123456789, yc = 1.123456789;
    double xd = 10.987654321, yd = 11.987654321;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, LargeCoordinates) {
    double xa = -1e30, ya = -1e30;
    double xb = 1e30, yb = 1e30;
    double xc = -1e30, yc = -1e30 + 0.000000001;
    double xd = 1e30, yd = 1e30 - 0.000000001;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, SmallCoordinates) {
    double xa = -1.000000001, ya = -1.000000001;
    double xb = 1.000000001, yb = 1.000000001;
    double xc = -1.000000001, yc = 1.000000001;
    double xd = 1.000000001, yd = -1.000000001;
    EXPECT_TRUE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTestDouble, NoIntersection) {
    double xa = 0.123456789, ya = 0.123456789;
    double xb = 1.987654321, yb = 1.987654321;
    double xc = 2.123456789, yc = 2.123456789;
    double xd = 3.987654321, yd = 3.987654321;
    EXPECT_FALSE(intersection(xa, ya, xb, yb, xc, yc, xd, yd));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}