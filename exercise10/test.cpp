#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int num_of_triangulations(int n);

TEST(NumOfTriangulationsTest, conocidos) {
    EXPECT_EQ(num_of_triangulations(2), 0);
    EXPECT_EQ(num_of_triangulations(3), 1);
    EXPECT_EQ(num_of_triangulations(4), 2);
    EXPECT_EQ(num_of_triangulations(5), 5);
    EXPECT_EQ(num_of_triangulations(6), 14);
    EXPECT_EQ(num_of_triangulations(7), 42);
    EXPECT_EQ(num_of_triangulations(8), 132);
    EXPECT_EQ(num_of_triangulations(9), 429);
    EXPECT_EQ(num_of_triangulations(10), 1430);
    EXPECT_EQ(num_of_triangulations(11), 4862);
    EXPECT_EQ(num_of_triangulations(12), 16796);
    EXPECT_EQ(num_of_triangulations(13), 58786);
    EXPECT_EQ(num_of_triangulations(14), 208012);
    EXPECT_EQ(num_of_triangulations(15), 742900);
    EXPECT_EQ(num_of_triangulations(16), 2674440);
    EXPECT_EQ(num_of_triangulations(17), 9694845);
    EXPECT_EQ(num_of_triangulations(18), 35357670);
    EXPECT_EQ(num_of_triangulations(19), 129644790);
    EXPECT_EQ(num_of_triangulations(20), 477638700);
    EXPECT_EQ(num_of_triangulations(21), 1767263190 % 1000000007);
    EXPECT_EQ(num_of_triangulations(22), 6564120420 % 1000000007);
    EXPECT_EQ(num_of_triangulations(23), 24466267020 % 1000000007);
    EXPECT_EQ(num_of_triangulations(24), 91482563640 % 1000000007);
    EXPECT_EQ(num_of_triangulations(25), 343059613650 % 1000000007);
    EXPECT_EQ(num_of_triangulations(26), 1289904147324 % 1000000007);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

