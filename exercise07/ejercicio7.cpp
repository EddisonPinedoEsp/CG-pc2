#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
};

template <typename T>
struct Segment {
    Point<T> p1, p2;
    Segment(Point<T> p1, Point<T> p2) : p1(p1), p2(p2) {}

    T get_y_at(T x) const {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (T)(p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
    }
};

// Barrido
template <typename T>
struct Event {
    T x;
    int segmentIndex;
    bool isStart;

    Event(T x, int segmentIndex, bool isStart) : x(x), segmentIndex(segmentIndex), isStart(isStart) {}

    bool operator<(const Event& other) const {
        if (x == other.x) return isStart && !other.isStart;
        return x < other.x;
    }
};

template <typename T>
int orientation(const Point<T>& p, const Point<T>& q, const Point<T>& r) {
    long double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colineal
    return (val > 0) ? 1 : 2; // 1: horario, 2: antihorario
}

template <typename T>
bool on_segment(const Point<T>& p, const Point<T>& q, const Point<T>& r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

template <typename T>
bool segments_intersect(const Segment<T>& s1, const Segment<T>& s2) {
    Point<T> p1 = s1.p1, q1 = s1.p2, p2 = s2.p1, q2 = s2.p2;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // Caso general
    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false;
}

template <typename T>
bool exist_intersections(const vector<vector<T>>& segments) {
    int n = segments.size();
    vector<Segment<T>> segs;

    vector<Event<T>> events;
    for (int i = 0; i < n; ++i) {
        Point<T> p1(segments[i][0], segments[i][1]);
        Point<T> p2(segments[i][2], segments[i][3]);

        if (p1.x > p2.x) swap(p1, p2);

        segs.push_back(Segment<T>(p1, p2));
        events.push_back(Event<T>(p1.x, i, true));  // Evento de inicio
        events.push_back(Event<T>(p2.x, i, false)); // Evento de fin
    }

    sort(events.begin(), events.end());

    set<int> activeSegments;

    auto compare = [&](int i, int j) {
        T x = events[i].x;
        return segs[i].get_y_at(x) < segs[j].get_y_at(x);
    };

    // Procesar los eventos
    for (const auto& event : events) {
        int index = event.segmentIndex;

        if (event.isStart) {
            auto it = activeSegments.insert(index).first;

            if (it != activeSegments.begin() && segments_intersect(segs[index], segs[*prev(it)]))
                return true;
            if (next(it) != activeSegments.end() && segments_intersect(segs[index], segs[*next(it)]))
                return true;
        } else {
            auto it = activeSegments.find(index);
            if (it != activeSegments.begin() && next(it) != activeSegments.end() &&
                segments_intersect(segs[*prev(it)], segs[*next(it)]))
                return true;
            activeSegments.erase(it);
        }
    }

    return false;
}

bool exist_intersections(const vector<vector<int>>& segments) {
    return exist_intersections<int>(segments);
}

bool exist_intersections(const vector<vector<double>>& segments) {
    return exist_intersections<double>(segments);
}