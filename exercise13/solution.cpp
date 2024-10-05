#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Funcion que calcula la distancia perpendicular de un punto a una línea
float perpendicularDistance(const vector<float>& point, const vector<float>& lineStart, const vector<float>& lineEnd) {
    float x0 = point[0], y0 = point[1];
    float x1 = lineStart[0], y1 = lineStart[1];
    float x2 = lineEnd[0], y2 = lineEnd[1];

    float num = fabs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1);
    float den = sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));

    return num / den;
}

// Douglas-Peucker
vector<vector<float>> douglasPeucker(const vector<vector<float>>& points, float epsilon) {
    if (points.size() < 2) {
        return {};
    }

    // Buscar el punto con la mayor distancia
    float maxDistance = 0;
    size_t index = 0;
    for (size_t i = 1; i < points.size() - 1; ++i) {
        float dist = perpendicularDistance(points[i], points[0], points.back());
        if (dist > maxDistance) {
            maxDistance = dist;
            index = i;
        }
    }

    // Si la distancia máxima es mayor que epsilon, se simplifica
    if (maxDistance > epsilon) {
        // Hacemos llamadas recursivas para los segmentos izquierdo y derecho
        vector<vector<float>> left = douglasPeucker(vector<vector<float>>(points.begin(), points.begin() + index + 1), epsilon);
        vector<vector<float>> right = douglasPeucker(vector<vector<float>>(points.begin() + index, points.end()), epsilon);

        // Combinamos los resultados
        left.pop_back();  // Y removemos los puntos duplicados
        left.insert(left.end(), right.begin(), right.end());

        return left;
    } else {
        // retornamos los puntos extremos
        return {points.front(), points.back()};
    }
}



int main() {
    // Example usage
    vector<vector<float>> points;
    int num_points = 100;
    float a = 0.1f; // Spiral coefficient
    float b = 0.2f; // Spiral coefficient

    for (int i = 0; i < num_points; ++i) {
        float theta = i * 0.1f;
        float x = (a + b * theta) * cos(theta);
        float y = (a + b * theta) * sin(theta);
        points.push_back({x, y});
    }

    float epsilon = 1.0;

    vector<vector<float>> simplified_points = douglasPeucker(points, epsilon);

    cout << "Simplified points:\n";
    for (const auto& point : simplified_points) {
        cout << "(" << point[0] << ", " << point[1] << ")\n";
    }
    // Find the bounding box of the points
    float minX = numeric_limits<float>::max(), minY = numeric_limits<float>::max();
    float maxX = numeric_limits<float>::lowest(), maxY = numeric_limits<float>::lowest();

    for (const auto& point : points) {
        if (point[0] < minX) minX = point[0];
        if (point[1] < minY) minY = point[1];
        if (point[0] > maxX) maxX = point[0];
        if (point[1] > maxY) maxY = point[1];
    }

    // Calculate scale and margin
    int margin = 50;
    float scaleX = (1000.0f - 2 * margin) / (maxX - minX);
    float scaleY = (1000.0f - 2 * margin) / (maxY - minY);
    float scale = min(scaleX, scaleY);

    // Create an image with a margin
    cv::Mat image(1000 + 2 * margin, 1000 + 2 * margin, CV_8UC3, cv::Scalar(255, 255, 255));

    // Draw original points in blue
    for (const auto& point : points) {
        cv::circle(image, cv::Point((point[0] - minX) * scale + margin, 1000 - (point[1] - minY) * scale + margin), 5, cv::Scalar(255, 0, 0), -1);
    }

    // Draw simplified points in red
    for (const auto& point : simplified_points) {
        cv::circle(image, cv::Point((point[0] - minX) * scale + margin, 1000 - (point[1] - minY) * scale + margin), 5, cv::Scalar(0, 0, 255), -1);
    }

    // Draw lines between original points
    for (size_t i = 0; i < points.size() - 1; ++i) {
        cv::line(image, cv::Point((points[i][0] - minX) * scale + margin, 1000 - (points[i][1] - minY) * scale + margin), 
                cv::Point((points[i + 1][0] - minX) * scale + margin, 1000 - (points[i + 1][1] - minY) * scale + margin), 
                cv::Scalar(255, 0, 0), 1);
    }

    // Draw lines between simplified points
    for (size_t i = 0; i < simplified_points.size() - 1; ++i) {
        cv::line(image, cv::Point((simplified_points[i][0] - minX) * scale + margin, 1000 - (simplified_points[i][1] - minY) * scale + margin), 
                cv::Point((simplified_points[i + 1][0] - minX) * scale + margin, 1000 - (simplified_points[i + 1][1] - minY) * scale + margin), 
                cv::Scalar(0, 0, 255), 1);
    }

    cv::imwrite("points_DO.png", image);

    return 0;
}
