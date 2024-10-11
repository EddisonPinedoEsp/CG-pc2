#include <gtest/gtest.h>
#include <cmath>


double distance_point_to_line_3D(
    double p1x, double p1y, double p1z,  // punto P1
    double dx, double dy, double dz,     // dirección
    double px, double py, double pz      // punto P
);


// test pendiente por revisar

TEST(DistancePointToLine3DTest, PointOnLine) {
    double p1x = 0.0, p1y = 0.0, p1z = 0.0;
    double dx = 1.0, dy = 1.0, dz = 1.0;
    double px = 2.0, py = 2.0, pz = 2.0;
    EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), 0.0, 1e-9);
}

// TEST(DistancePointToLine3DTest, PointOffLine) {
//     double p1x = 0.0, p1y = 0.0, p1z = 0.0;
//     double dx = 1.0, dy = 1.0, dz = 1.0;
//     double px = 1.0, py = 2.0, pz = 3.0;
//     double expected_distance = sqrt(2.0 / 3.0);
//     // EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), expected_distance, 1e-9);
//     EXPECT_EQ(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), 1.41);
// }

TEST(DistancePointToLine3DTest, LargeCoordinates) {
    double p1x = 1e9, p1y = 1e9, p1z = 1e9;
    double dx = 1e9, dy = 1e9, dz = 1e9;
    double px = 2e9, py = 2e9, pz = 2e9;
    EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), 0.0, 1e-9);
}

TEST(DistancePointToLine3DTest, SmallCoordinates) {
    double p1x = 1e-9, p1y = 1e-9, p1z = 1e-9;
    double dx = 1e-9, dy = 1e-9, dz = 1e-9;
    double px = 2e-9, py = 2e-9, pz = 2e-9;
    EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), 0.0, 1e-9);
}

TEST(DistancePointToLine3DTest, ZeroDirectionVector) {
    double p1x = 0.0, p1y = 0.0, p1z = 0.0;
    double dx = 0.0, dy = 0.0, dz = 0.0;
    double px = 1.0, py = 1.0, pz = 1.0;
    EXPECT_TRUE(std::isnan(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz)));
}

TEST(DistancePointToLine3DTest, NegativeCoordinates) {
    double p1x = -1.0, p1y = -1.0, p1z = -1.0;
    double dx = -1.0, dy = -1.0, dz = -1.0;
    double px = -2.0, py = -2.0, pz = -2.0;
    EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), 0.0, 1e-9);
}

TEST(DistancePointToLine3DTest, MixedCoordinates) {
    double p1x = 1.0, p1y = -1.0, p1z = 1.0;
    double dx = -1.0, dy = 1.0, dz = -1.0;
    double px = 2.0, py = -2.0, pz = 2.0;
    double expected_distance = sqrt(0.0);
    EXPECT_NEAR(distance_point_to_line_3D(p1x, p1y, p1z, dx, dy, dz, px, py, pz), expected_distance, 1e-9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}