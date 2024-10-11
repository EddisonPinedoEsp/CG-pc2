#include <vector>
#include <limits>
using namespace std;

template <typename T> 
vector<int> closest_points(vector<vector<T>> const& points) {
    int n = points.size();

    double min_distance = numeric_limits<double>::max();
    vector<int> result(2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Calculamos la distancia al cuadrado entre el punto i y el punto j
            double dx = points[j][0] - points[i][0];
            double dy = points[j][1] - points[i][1];
            double distance_sq = dx * dx + dy * dy;

            // Si encontramos una distancia menor, actualizamos el par de puntos más cercanos
            if (distance_sq < min_distance) {
                min_distance = distance_sq;
                result = {i, j};
            }
        }
    }

    if (result[0] > result[1]) {
        swap(result[0], result[1]);
    }

    return result;
}

vector<int> closest_points(vector<vector<int>> const& points) {
    return closest_points<int>(points);
}

vector<int> closest_points(vector<vector<double>> const& points) {
    return closest_points<double>(points);
}
