#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

template <typename T>
struct Triangle {
    int idx;
    T area; 
    T max_angle; 
};

template <typename T>
T triangle_area(const vector<T>& p1, const vector<T>& p2, const vector<T>& p3) {
    return abs(p1[0] * (p2[1] - p3[1]) + p2[0] * (p3[1] - p1[1]) + p3[0] * (p1[1] - p2[1])) / static_cast<T>(2);
}

template <typename T>
T distance(const vector<T>& p1, const vector<T>& p2) {
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}

template <typename T>
T max_triangle_angle(const vector<T>& p1, const vector<T>& p2, const vector<T>& p3) {
    T a = distance(p2, p3);
    T b = distance(p1, p3);
    T c = distance(p1, p2);

    T angle1 = acos((b * b + c * c - a * a) / (2 * b * c));
    T angle2 = acos((a * a + c * c - b * b) / (2 * a * c));
    T angle3 = acos((a * a + b * b - c * c) / (2 * a * b));

    return max({angle1, angle2, angle3});
}

template <typename T>
vector<vector<T>> triangles_based_simplification(vector<vector<T>> const& vertices, int N) {
    int original_size = vertices.size();
    if (N >= original_size) return vertices;

    vector<vector<T>> simplified_vertices = vertices;

    vector<Triangle<T>> triangles;
    for (int i = 1; i < simplified_vertices.size() - 1; ++i) {
        T area = triangle_area(simplified_vertices[i - 1], simplified_vertices[i], simplified_vertices[i + 1]);
        T max_angle = max_triangle_angle(simplified_vertices[i - 1], simplified_vertices[i], simplified_vertices[i + 1]);
        triangles.push_back({i, area, max_angle});
    }

    while (simplified_vertices.size() > N) {
        sort(triangles.begin(), triangles.end(), [](const Triangle<T>& t1, const Triangle<T>& t2) {
            if (t1.area == t2.area) {
                return t1.max_angle > t2.max_angle;
            }
            return t1.area < t2.area;
        });

        // Eliminar el vértice central del triángulo más pequeño
        int to_remove = triangles.front().idx;
        simplified_vertices.erase(simplified_vertices.begin() + to_remove);

        // Actualizar los triángulos adyacentes
        triangles.clear();
        for (int i = 1; i < simplified_vertices.size() - 1; ++i) {
            T area = triangle_area(simplified_vertices[i - 1], simplified_vertices[i], simplified_vertices[i + 1]);
            T max_angle = max_triangle_angle(simplified_vertices[i - 1], simplified_vertices[i], simplified_vertices[i + 1]);
            triangles.push_back({i, area, max_angle});
        }
    }

    return simplified_vertices;
}

vector<vector<int>> triangles_based_simplification(vector<vector<int>> const& vertices, int N) {
    return triangles_based_simplification<int>(vertices, N);
}

vector<vector<double>> triangles_based_simplification(vector<vector<double>> const& vertices, int N) {
    return triangles_based_simplification<double>(vertices, N);
}

