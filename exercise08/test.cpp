#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// Mock function to simulate cerca behavior for testing
pair<vector<float>, vector<float>> cerca(vector<vector<float>>& P);

// Función auxiliar para calcular la distancia entre dos puntos
float distancia(const vector<float>& p1, const vector<float>& p2) {
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}

TEST(CercaTest, SimpleCase) {
    vector<vector<float>> P = {{0, 0}, {2, 2}, {3, 3}};
    auto result = cerca(P);
    float dist = distancia(result.first, result.second);
    cout << "SimpleCase: Distancia entre (" << result.first[0] << ", " << result.first[1] << ") y ("
        << result.second[0] << ", " << result.second[1] << ") -> " << dist << endl;
    EXPECT_NEAR(dist, sqrt(2), 1e-5);
}

TEST(CercaTest, MultiplePoints) {
    vector<vector<float>> P = {{0, 0}, {5, 5}, {3, 4}, {1, 1}};
    auto result = cerca(P);
    float dist = distancia(result.first, result.second);
    cout << "MultiplePoints: Distancia entre (" << result.first[0] << ", " << result.first[1] << ") y ("
        << result.second[0] << ", " << result.second[1] << ") -> " << dist << endl;
    EXPECT_NEAR(dist, sqrt(2), 1e-5);
}

TEST(CercaTest, NegativeCoordinates) {
    vector<vector<float>> P = {{-1, -1}, {-2, -2}, {3, 4}, {5, 5}};
    auto result = cerca(P);
    float dist = distancia(result.first, result.second);
    cout << "NegativeCoordinates: Distancia entre (" << result.first[0] << ", " << result.first[1] << ") y ("
        << result.second[0] << ", " << result.second[1] << ") -> " << dist << endl;
    EXPECT_NEAR(dist, sqrt(2), 1e-5);
}

TEST(CercaTest, SamePoint) {
    vector<vector<float>> P = {{0, 0}, {0, 0}, {1, 1}};
    auto result = cerca(P);
    float dist = distancia(result.first, result.second);
    cout << "SamePoint: Distancia entre (" << result.first[0] << ", " << result.first[1] << ") y ("
        << result.second[0] << ", " << result.second[1] << ") -> " << dist << endl;
    EXPECT_NEAR(dist, 0, 1e-5);
}

TEST(CercaTest, LargeDataset) {
    vector<vector<float>> P;
    for (int i = 0; i < 1000; ++i) {
        P.push_back({static_cast<float>(i), static_cast<float>(i)});
    }
    auto result = cerca(P);
    float dist = distancia(result.first, result.second);
    cout << "LargeDataset: Distancia entre (" << result.first[0] << ", " << result.first[1] << ") y ("
        << result.second[0] << ", " << result.second[1] << ") -> " << dist << endl;
    EXPECT_NEAR(dist, sqrt(2), 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
