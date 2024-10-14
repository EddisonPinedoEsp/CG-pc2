#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
double producto_cruz(const vector<T>& p, const vector<T>& q, const vector<T>& r) {
    return (q[0] - p[0]) * (r[1] - p[1]) - (q[1] - p[1]) * (r[0] - p[0]);
}

template <typename T>
bool dentro_poligono(const vector<vector<T>>& vertices, const vector<T>& point) {
    int n = vertices.size();
    bool positive = false, negative = false;
    
    for (int i = 0; i < n; ++i) {
        const vector<T>& p1 = vertices[i];
        const vector<T>& p2 = vertices[(i + 1) % n];
        T cross = producto_cruz(p1, p2, point);
        
        if (cross > 0) positive = true;
        else if (cross < 0) negative = true;

        if (positive && negative) return false;
    }
    
    return true;
}

template <typename T>
vector<vector<T>> interior_points_removal(const vector<vector<T>>& vertices) {
    vector<vector<T>> filtered;

    for (size_t i = 0; i < vertices.size(); ++i) {
        bool isInterior = false;

        vector<vector<T>> polygon;
        for (size_t j = 0; j < vertices.size(); ++j) {
            if (i != j) polygon.push_back(vertices[j]);
        }

        if (dentro_poligono(polygon, vertices[i])) {
            isInterior = true;
        }

        if (!isInterior) {
            filtered.push_back(vertices[i]);
        }
    }
    return filtered;
}

template <typename T>
int leftmost_point(const vector<vector<T>>& vertices) {
    int leftmost = 0;
    for (size_t i = 1; i < vertices.size(); i++) {
        if (vertices[i][0] < vertices[leftmost][0]) {
            leftmost = i;
        }
    }
    return leftmost;
}

template <typename T>
vector<vector<T>> jarvis(const vector<vector<T>>& vertices, bool withInteriorPointsRemoval) {
    vector<vector<T>> points = vertices;

    if (withInteriorPointsRemoval) {
        points = interior_points_removal(points);
    }

    if (points.size() < 3) return {};

    vector<vector<T>> hull;
    int start = leftmost_point(points);
    int current = start;

    do {
        hull.push_back(points[current]);
        int next = (current + 1) % points.size();
        
        for (size_t i = 0; i < points.size(); i++) {
            if (producto_cruz(points[current], points[next], points[i]) > 0) {
                next = i;
            }
        }
        current = next;
    } while (current != start);

    return hull;
}


template <typename T>
T squared_distance(const vector<T>& p, const vector<T>& q) {
    return (q[0] - p[0]) * (q[0] - p[0]) + (q[1] - p[1]) * (q[1] - p[1]);
}

template <typename T>
bool polar_order(const vector<T>& p0, const vector<T>& p1, const vector<T>& p2) {
    T cross = producto_cruz(p0, p1, p2);
    if (cross == 0) {
        return squared_distance(p0, p1) < squared_distance(p0, p2);
    }
    return cross > 0;
}

template <typename T>
int lowest_point(const vector<vector<T>>& vertices) {
    int lowest = 0;
    for (size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i][1] < vertices[lowest][1] || 
            (vertices[i][1] == vertices[lowest][1] && vertices[i][0] < vertices[lowest][0])) {
            lowest = i;
        }
    }
    return lowest;
}

// Algoritmo de Graham Scan
template <typename T>
vector<vector<T>> graham(const vector<vector<T>>& vertices, bool withInteriorPointsRemoval) {
    vector<vector<T>> points = vertices;

    if (withInteriorPointsRemoval) {
        points = interior_points_removal(points);
    }

    if (points.size() < 3) return {};

    int lowest = lowest_point(points);
    swap(points[0], points[lowest]);

    sort(points.begin() + 1, points.end(), [&](const vector<T>& p1, const vector<T>& p2) {
        return polar_order(points[0], p1, p2);
    });

    vector<vector<T>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() > 1 && producto_cruz(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return hull;
}
vector<vector<int>> graham(const vector<vector<int>>& vertices, bool withInteriorPointsRemoval) {
    return graham<int>(vertices, withInteriorPointsRemoval);
}

vector<vector<double>> graham(const vector<vector<double>>& vertices, bool withInteriorPointsRemoval) {
    return graham<double>(vertices, withInteriorPointsRemoval);
}

vector<vector<int>> jarvis(const vector<vector<int>>& vertices, bool withInteriorPointsRemoval) {
    return jarvis<int>(vertices, withInteriorPointsRemoval);
}

vector<vector<double>> jarvis(const vector<vector<double>>& vertices, bool withInteriorPointsRemoval) {
    return jarvis<double>(vertices, withInteriorPointsRemoval);
}


