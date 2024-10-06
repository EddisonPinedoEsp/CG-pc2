#include <gtest/gtest.h>
using namespace std;

bool intersecion(float xa, float ya, float xb, float yb, float xc, float yc, float xd, float yd);
TEST(IntersectionTest, NoIntersection) {
    float xa = 0, ya = 0, xb = 1, yb = 1, xc = 2, yc = 2, xd = 3, yd = 3;
    cout << "Test puntos: (" << xa << ", " << ya << "), (" << xb << ", " << yb << "), (" << xc << ", " << yc << "), (" << xd << ", " << yd << ")\n";
    EXPECT_FALSE(intersecion(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTest, IntersectionAtPoint) {
    float xa = 0, ya = 0, xb = 2, yb = 2, xc = 0, yc = 2, xd = 2, yd = 0;
    cout << "Test puntos: (" << xa << ", " << ya << "), (" << xb << ", " << yb << "), (" << xc << ", " << yc << "), (" << xd << ", " << yd << ")\n";
    EXPECT_TRUE(intersecion(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTest, OverlappingLines) {
    float xa = 0, ya = 0, xb = 2, yb = 2, xc = 1, yc = 1, xd = 3, yd = 3;
    cout << "Test puntos: (" << xa << ", " << ya << "), (" << xb << ", " << yb << "), (" << xc << ", " << yc << "), (" << xd << ", " << yd << ")\n";
    EXPECT_TRUE(intersecion(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTest, ParallelLines) {
    float xa = 0, ya = 0, xb = 2, yb = 2, xc = 0, yc = 1, xd = 2, yd = 3;
    cout << "Test puntos: (" << xa << ", " << ya << "), (" << xb << ", " << yb << "), (" << xc << ", " << yc << "), (" << xd << ", " << yd << ")\n";
    EXPECT_FALSE(intersecion(xa, ya, xb, yb, xc, yc, xd, yd));
}

TEST(IntersectionTest, CoincidingLines) {
    float xa = 0, ya = 0, xb = 2, yb = 2, xc = 0, yc = 0, xd = 2, yd = 2;
    cout << "Test puntos: (" << xa << ", " << ya << "), (" << xb << ", " << yb << "), (" << xc << ", " << yc << "), (" << xd << ", " << yd << ")\n";
    EXPECT_TRUE(intersecion(xa, ya, xb, yb, xc, yc, xd, yd));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}