#include <gtest/gtest.h>

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}