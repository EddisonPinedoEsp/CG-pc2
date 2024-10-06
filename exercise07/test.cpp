#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

struct Punto {
    int x, y;
    bool operator<(const Punto& otro) const {
        return tie(x, y) < tie(otro.x, otro.y);
    }
};

struct Segmento {
    Punto p1, p2;
    Segmento(Punto a, Punto b) : p1(a), p2(b) {
        if (p2 < p1) swap(p1, p2); 
    }
};

struct Event {
    int x;
    bool esComienso;
    Segmento* segmento;
    
    bool operator<(const Event& otro) const {
        if (x != otro.x)
            return x < otro.x;
        return esComienso > otro.esComienso;
    }
};

bool detectarInterseccion(vector<Segmento>& Segmentos);

TEST(DetectIntersectionsTest, NoIntersections) {
    vector<Segmento> Segmentos = {
        Segmento({0, 0}, {1, 1}),
        Segmento({2, 2}, {3, 3})
    };
    bool result = detectarInterseccion(Segmentos);
    cout << "NoIntersections: " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(DetectIntersectionsTest, OneIntersection) {
    vector<Segmento> Segmentos = {
        Segmento({0, 0}, {2, 2}),
        Segmento({0, 2}, {2, 0})
    };
    bool result = detectarInterseccion(Segmentos);
    cout << "OneIntersection: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, MultipleIntersections) {
    vector<Segmento> segmentos = {
        Segmento({0, 0}, {3, 3}),
        Segmento({0, 3}, {3, 0}),
        Segmento({1, 0}, {1, 3})
    };
    bool result = detectarInterseccion(segmentos);
    cout << "MultipleIntersections: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, CollinearSegmentos) {
    vector<Segmento> segmentos = {
        Segmento({0, 0}, {2, 2}),
        Segmento({1, 1}, {3, 3})
    };
    bool result = detectarInterseccion(segmentos);
    cout << "CollinearSegmentos: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, TouchingEndPuntos) {
    vector<Segmento> segmentos = {
        Segmento({0, 0}, {2, 2}),
        Segmento({2, 2}, {3, 3})
    };
    bool result = detectarInterseccion(segmentos);
    cout << "TouchingEndPuntos: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, ParallelSegmentos) {
    vector<Segmento> segmentos = {
        Segmento({0, 0}, {2, 2}),
        Segmento({0, 1}, {2, 3})
    };
    bool result = detectarInterseccion(segmentos);
    cout << "ParallelSegmentos: " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(DetectIntersectionsTest, GivenCase) {
    vector<Segmento> segmentos = {
        Segmento({0, 0}, {4, 4}),
        Segmento({1, 5}, {5, 1}),
        Segmento({1, 1}, {5, 5})
    };
    bool result = detectarInterseccion(segmentos);
    cout << "GivenCase: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
