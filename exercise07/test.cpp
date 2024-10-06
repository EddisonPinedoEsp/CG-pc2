#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

// Definición de la estructura Point
struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

// Definición de la estructura Segment
struct Segment {
    Point p1, p2;
    Segment(Point a, Point b) : p1(a), p2(b) {
        if (p2 < p1) swap(p1, p2);  // Ensure p1 is the left endpoint
    }
};

// Definición de la estructura Event
struct Event {
    int x;
    bool isStart;
    Segment* segment;
    
    bool operator<(const Event& other) const {
        if (x != other.x)
            return x < other.x;
        return isStart > other.isStart;  // Start event comes before end event if equal x
    }
};

// Mock function to simulate detectIntersections behavior for testing
bool detectIntersections(vector<Segment>& segments);

TEST(DetectIntersectionsTest, NoIntersections) {
    vector<Segment> segments = {
        Segment({0, 0}, {1, 1}),
        Segment({2, 2}, {3, 3})
    };
    bool result = detectIntersections(segments);
    cout << "NoIntersections: " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(DetectIntersectionsTest, OneIntersection) {
    vector<Segment> segments = {
        Segment({0, 0}, {2, 2}),
        Segment({0, 2}, {2, 0})
    };
    bool result = detectIntersections(segments);
    cout << "OneIntersection: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, MultipleIntersections) {
    vector<Segment> segments = {
        Segment({0, 0}, {3, 3}),
        Segment({0, 3}, {3, 0}),
        Segment({1, 0}, {1, 3})
    };
    bool result = detectIntersections(segments);
    cout << "MultipleIntersections: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, CollinearSegments) {
    vector<Segment> segments = {
        Segment({0, 0}, {2, 2}),
        Segment({1, 1}, {3, 3})
    };
    bool result = detectIntersections(segments);
    cout << "CollinearSegments: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, TouchingEndpoints) {
    vector<Segment> segments = {
        Segment({0, 0}, {2, 2}),
        Segment({2, 2}, {3, 3})
    };
    bool result = detectIntersections(segments);
    cout << "TouchingEndpoints: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

TEST(DetectIntersectionsTest, ParallelSegments) {
    vector<Segment> segments = {
        Segment({0, 0}, {2, 2}),
        Segment({0, 1}, {2, 3})
    };
    bool result = detectIntersections(segments);
    cout << "ParallelSegments: " << (result ? "true" : "false") << endl;
    EXPECT_FALSE(result);
}

TEST(DetectIntersectionsTest, GivenCase) {
    vector<Segment> segments = {
        Segment({0, 0}, {4, 4}),
        Segment({1, 5}, {5, 1}),
        Segment({1, 1}, {5, 5})
    };
    bool result = detectIntersections(segments);
    cout << "GivenCase: " << (result ? "true" : "false") << endl;
    EXPECT_TRUE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
