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

vector<vector<float>> puntos = {
    {0.0, 0.0},
    {1.0, 1.0},    
    {2.0, 2.0},     
    {3.0, 1.0},
    {4.0, 0.5},    
    {5.0, 0.0},     
    {6.0, 0.2},
    {7.0, 0.4},
    {8.0, 0.2},     
    {9.0, 0.0},     
    {10.0, 0.0},    
    {11.0, -0.5},
    {12.0, -1.0},   
    {13.0, -0.5},  
    {14.0, 0.0}
};

    float epsilon = 1.0;

    vector<vector<float>> simplified_points = douglasPeucker(puntos, epsilon);

    cout << "Simplified puntos:\n";
    for (const auto& punto : simplified_points) {
        cout << "(" << punto[0] << ", " << punto[1] << ")\n";
    }

    // float minX = numeric_limits<float>::max(), minY = numeric_limits<float>::max();
    // float maxX = numeric_limits<float>::lowest(), maxY = numeric_limits<float>::lowest();

    // for (const auto& punto : puntos) {
    //     if (punto[0] < minX) minX = punto[0];
    //     if (punto[1] < minY) minY = punto[1];
    //     if (punto[0] > maxX) maxX = punto[0];
    //     if (punto[1] > maxY) maxY = punto[1];
    // }

    // int margin = 50;
    // float scaleX = (1000.0f - 2 * margin) / (maxX - minX);
    // float scaleY = (1000.0f - 2 * margin) / (maxY - minY);
    // float scale = min(scaleX, scaleY);

    // cv::Mat image(1000 + 2 * margin, 1000 + 2 * margin, CV_8UC3, cv::Scalar(255, 255, 255));

    // for (const auto& punto : puntos) {
    //     cv::circle(image, cv::Point((punto[0] - minX) * scale + margin, 1000 - (punto[1] - minY) * scale + margin), 5, cv::Scalar(255, 0, 0), -1);
    // }

    // for (const auto& punto : simplified_points) {
    //     cv::circle(image, cv::Point((punto[0] - minX) * scale + margin, 1000 - (punto[1] - minY) * scale + margin), 5, cv::Scalar(0, 0, 255), -1);
    // }

    // for (size_t i = 0; i < puntos.size() - 1; ++i) {
    //     cv::line(image, cv::Point((puntos[i][0] - minX) * scale + margin, 1000 - (puntos[i][1] - minY) * scale + margin), 
    //             cv::Point((puntos[i + 1][0] - minX) * scale + margin, 1000 - (puntos[i + 1][1] - minY) * scale + margin), 
    //             cv::Scalar(255, 0, 0), 1);
    // }

    // for (size_t i = 0; i < simplified_points.size() - 1; ++i) {
    //     cv::line(image, cv::Point((simplified_points[i][0] - minX) * scale + margin, 1000 - (simplified_points[i][1] - minY) * scale + margin), 
    //             cv::Point((simplified_points[i + 1][0] - minX) * scale + margin, 1000 - (simplified_points[i + 1][1] - minY) * scale + margin), 
    //             cv::Scalar(0, 0, 255), 1);
    // }

    // cv::imwrite("Douglas-Peucker.png", image);

    return 0;
}
