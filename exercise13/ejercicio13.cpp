#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;
template <typename T>
T perpendicularDistance(const vector<T>& point, const vector<T>& lineStart, const vector<T>& lineEnd) {
    T x0 = point[0], y0 = point[1];
    T x1 = lineStart[0], y1 = lineStart[1];
    T x2 = lineEnd[0], y2 = lineEnd[1];

    T num = fabs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1);
    T den = sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));

    return num / den;
}

// Douglas-Peucker algorithm
template <typename T>
vector<vector<T>> douglas_peucker(vector<vector<T>> const& vertices, double epsilon) {
    if (vertices.size() < 2) {
        return {};
    }

    T maxDistance = 0;
    size_t index = 0;
    for (size_t i = 1; i < vertices.size() - 1; ++i) {
        T dist = perpendicularDistance(vertices[i], vertices[0], vertices.back());
        if (dist > maxDistance) {
            maxDistance = dist;
            index = i;
        }
    }

    if (maxDistance > epsilon) {
        vector<vector<T>> left = douglas_peucker(vector<vector<T>>(vertices.begin(), vertices.begin() + index + 1), epsilon);
        vector<vector<T>> right = douglas_peucker(vector<vector<T>>(vertices.begin() + index, vertices.end()), epsilon);

        left.pop_back();  // Remove the duplicate point
        left.insert(left.end(), right.begin(), right.end());

        return left;
    } else {
        return {vertices.front(), vertices.back()};
    }
}

vector<vector<int>> douglas_peucker(vector<vector<int>> const& vertices, int epsilon) {
    return douglas_peucker<int>(vertices, epsilon);
}

vector<vector<double>> douglas_peucker(vector<vector<double>> const& vertices, double epsilon) {
    return douglas_peucker<double>(vertices, epsilon);
}
