#include <gtest/gtest.h>
#include <vector>
#include <cmath>

using namespace std;

// Declaración de la función a probar
float distacia_punto_recta(vector<float> P1, vector<float> d, vector<float> P);

// Implementación de los tests
TEST(DistanciaPuntoRectaTest, PuntoSobreLaRecta) {
    vector<float> P1 = {0, 0};
    vector<float> d = {1, 1};
    vector<float> P = {1, 1};
    EXPECT_NEAR(distacia_punto_recta(P1, d, P), 0.0, 1e-5);
}

TEST(DistanciaPuntoRectaTest, PuntoFueraDeLaRecta) {
    vector<float> P1 = {0, 0};
    vector<float> d = {1, 0};
    vector<float> P = {0, 1};
    EXPECT_NEAR(distacia_punto_recta(P1, d, P), 1.0, 1e-5);
}

TEST(DistanciaPuntoRectaTest, PuntoEnElOrigen) {
    vector<float> P1 = {1, 1};
    vector<float> d = {1, 1};
    vector<float> P = {0, 0};
    EXPECT_NEAR(distacia_punto_recta(P1, d, P), sqrt(2) / 2, 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}