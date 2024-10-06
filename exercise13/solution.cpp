#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Funcion que calcula la distancia perpendicular de un punto a una línea
float distanciaPerpendicular(const vector<float>& punto, const vector<float>& lineaInicio, const vector<float>& lineaFin) {
    float x0 = punto[0], y0 = punto[1];
    float x1 = lineaInicio[0], y1 = lineaInicio[1];
    float x2 = lineaFin[0], y2 = lineaFin[1];

    float num = fabs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1);
    float den = sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));

    return num / den;
}

// Douglas-Peucker
vector<vector<float>> douglasPeucker(const vector<vector<float>>& puntos, float epsilon) {
    if (puntos.size() < 2) {
        return {};
    }

    // Buscar el punto con la mayor distancia
    float maxDistance = 0;
    size_t index = 0;
    for (size_t i = 1; i < puntos.size() - 1; ++i) {
        float dist = distanciaPerpendicular(puntos[i], puntos[0], puntos.back());
        if (dist > maxDistance) {
            maxDistance = dist;
            index = i;
        }
    }

    // Si la distancia máxima es mayor que epsilon, se simplifica
    if (maxDistance > epsilon) {
        // Hacemos llamadas recursivas para los segmentos izquierdo y derecho
        vector<vector<float>> left = douglasPeucker(vector<vector<float>>(puntos.begin(), puntos.begin() + index + 1), epsilon);
        vector<vector<float>> right = douglasPeucker(vector<vector<float>>(puntos.begin() + index, puntos.end()), epsilon);

        // Combinamos los resultados
        left.pop_back();  // Y removemos los puntos duplicados
        left.insert(left.end(), right.begin(), right.end());

        return left;
    } else {
        // retornamos los puntos extremos
        return {puntos.front(), puntos.back()};
    }
}

int main() {
    // Example usage
    vector<vector<float>> puntos;
    int num_points = 100;
    float a = 0.1f; // Spiral coefficient
    float b = 0.2f; // Spiral coefficient

    for (int i = 0; i < num_points; ++i) {
        float theta = i * 0.1f;
        float x = (a + b * theta) * cos(theta);
        float y = (a + b * theta) * sin(theta);
        puntos.push_back({x, y});
    }

    float epsilon = 1.0;

    vector<vector<float>> simplified_points = douglasPeucker(puntos, epsilon);

    cout << "Simplified puntos:\n";
    for (const auto& punto : simplified_points) {
        cout << "(" << punto[0] << ", " << punto[1] << ")\n";
    }
    // Find the bounding box of the puntos
    float minX = numeric_limits<float>::max(), minY = numeric_limits<float>::max();
    float maxX = numeric_limits<float>::lowest(), maxY = numeric_limits<float>::lowest();

    for (const auto& punto : puntos) {
        if (punto[0] < minX) minX = punto[0];
        if (punto[1] < minY) minY = punto[1];
        if (punto[0] > maxX) maxX = punto[0];
        if (punto[1] > maxY) maxY = punto[1];
    }

    // Calculate scale and margin
    int margin = 50;
    float scaleX = (1000.0f - 2 * margin) / (maxX - minX);
    float scaleY = (1000.0f - 2 * margin) / (maxY - minY);
    float scale = min(scaleX, scaleY);

    // Create an image with a margin
    cv::Mat image(1000 + 2 * margin, 1000 + 2 * margin, CV_8UC3, cv::Scalar(255, 255, 255));

    // Draw original puntos in blue
    for (const auto& punto : puntos) {
        cv::circle(image, cv::Point((punto[0] - minX) * scale + margin, 1000 - (punto[1] - minY) * scale + margin), 5, cv::Scalar(255, 0, 0), -1);
    }

    // Draw simplified puntos in red
    for (const auto& punto : simplified_points) {
        cv::circle(image, cv::Point((punto[0] - minX) * scale + margin, 1000 - (punto[1] - minY) * scale + margin), 5, cv::Scalar(0, 0, 255), -1);
    }

    // Draw lines between original puntos
    for (size_t i = 0; i < puntos.size() - 1; ++i) {
        cv::line(image, cv::Point((puntos[i][0] - minX) * scale + margin, 1000 - (puntos[i][1] - minY) * scale + margin), 
                cv::Point((puntos[i + 1][0] - minX) * scale + margin, 1000 - (puntos[i + 1][1] - minY) * scale + margin), 
                cv::Scalar(255, 0, 0), 1);
    }

    // Draw lines between simplified puntos
    for (size_t i = 0; i < simplified_points.size() - 1; ++i) {
        cv::line(image, cv::Point((simplified_points[i][0] - minX) * scale + margin, 1000 - (simplified_points[i][1] - minY) * scale + margin), 
                cv::Point((simplified_points[i + 1][0] - minX) * scale + margin, 1000 - (simplified_points[i + 1][1] - minY) * scale + margin), 
                cv::Scalar(0, 0, 255), 1);
    }

    cv::imwrite("points_DO.png", image);

    return 0;
}
