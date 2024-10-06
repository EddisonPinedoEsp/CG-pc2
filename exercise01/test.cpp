#include <gtest/gtest.h>

bool intersecion(float xa, float ya, float xb, float yb, float xc, float yc, float xd, float yd);

TEST(IntersectionTest, NoIntersection) {
    EXPECT_FALSE(intersecion(0, 0, 1, 1, 2, 2, 3, 3));
}

TEST(IntersectionTest, IntersectionAtPoint) {
    EXPECT_TRUE(intersecion(0, 0, 2, 2, 0, 2, 2, 0));
}

TEST(IntersectionTest, OverlappingLines) {
    EXPECT_TRUE(intersecion(0, 0, 2, 2, 1, 1, 3, 3));
}

TEST(IntersectionTest, ParallelLines) {
    EXPECT_FALSE(intersecion(0, 0, 2, 2, 0, 1, 2, 3));
}

TEST(IntersectionTest, CoincidingLines) {
    EXPECT_TRUE(intersecion(0, 0, 2, 2, 0, 0, 2, 2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

