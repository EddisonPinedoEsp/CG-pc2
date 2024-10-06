#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

struct Segment {
    Point p1, p2;
    Segment(Point a, Point b) : p1(a), p2(b) {
        if (p2 < p1) swap(p1, p2);  // Ensure p1 is the left endpoint
    }
};

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

// Function to check if two segments intersect
bool doIntersect(const Segment& s1, const Segment& s2) {
    auto orientation = [](const Point& p, const Point& q, const Point& r) {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;  // collinear
        return (val > 0) ? 1 : 2;  // clock or counterclockwise
    };

    auto onSegment = [](const Point& p, const Point& q, const Point& r) {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
                q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
    };

    int o1 = orientation(s1.p1, s1.p2, s2.p1);
    int o2 = orientation(s1.p1, s1.p2, s2.p2);
    int o3 = orientation(s2.p1, s2.p2, s1.p1);
    int o4 = orientation(s2.p1, s2.p2, s1.p2);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(s1.p1, s2.p1, s1.p2)) return true;
    if (o2 == 0 && onSegment(s1.p1, s2.p2, s1.p2)) return true;
    if (o3 == 0 && onSegment(s2.p1, s1.p1, s2.p2)) return true;
    if (o4 == 0 && onSegment(s2.p1, s1.p2, s2.p2)) return true;

    return false;
}

// Comparator to order segments by their y-coordinate when intersected by the sweep line
struct SegmentComparator {
    bool operator()(const Segment* s1, const Segment* s2) const {
        if (s1->p1.y == s2->p1.y) return s1->p2.y < s2->p2.y;
        return s1->p1.y < s2->p1.y;
    }
};

bool detectIntersections(vector<Segment>& segments) {
    vector<Event> events;
    
    // Create events for each segment
    for (auto& segment : segments) {
        events.push_back({segment.p1.x, true, &segment});
        events.push_back({segment.p2.x, false, &segment});
    }
    
    // Sort events by x-coordinate
    sort(events.begin(), events.end());

    // Balanced BST to store active segments
    set<Segment*, SegmentComparator> activeSegments;

    // Sweep line algorithm
    for (auto& event : events) {
        Segment* currentSegment = event.segment;

        if (event.isStart) {
            // Insert the segment into the active set
            auto iter = activeSegments.insert(currentSegment).first;
            
            // Check for intersection with neighbors
            auto above = next(iter);
            auto below = (iter == activeSegments.begin()) ? activeSegments.end() : prev(iter);

            if (above != activeSegments.end() && doIntersect(**iter, **above)) return true;
            if (below != activeSegments.end() && doIntersect(**iter, **below)) return true;
        } else {
            // Remove the segment and check for intersections between neighbors
            auto iter = activeSegments.find(currentSegment);
            auto above = next(iter);
            auto below = (iter == activeSegments.begin()) ? activeSegments.end() : prev(iter);

            if (above != activeSegments.end() && below != activeSegments.end() && doIntersect(**above, **below)) return true;

            // Remove the segment from the active set
            activeSegments.erase(iter);
        }
    }

    return false;
}
