#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <set>
#include <tuple>

using namespace std;

// Funcion para calcular el área de un triángulo dado por sus vértices
float areaTriangulo(const vector<float>& p1, const vector<float>& p2, const vector<float>& p3) {
    return fabs(p1[0] * (p2[1] - p3[1]) +
                p2[0] * (p3[1] - p1[1]) +
                p3[0] * (p1[1] - p2[1])) / 2.0;
}

// Visvalingam-Whyatt
vector<vector<float>> visvalingamWhyatt(const vector<vector<float>>& puntos, size_t k) {
    if (puntos.size() <= k) {
        return puntos;
    }

    // Un vector para almacenar las áreas de los triángulos
    vector<float> areas(puntos.size(), numeric_limits<float>::max());

    // Set para almacenar las áreas de los triángulos
    set<pair<float, size_t>> areaSet;

    // Calcular las áreas de los triángulos
    for (size_t i = 1; i < puntos.size() - 1; ++i) {
        float area = areaTriangulo(puntos[i - 1], puntos[i], puntos[i + 1]);
        areas[i] = area;
        areaSet.insert({area, i});
    }

    // Un vector para marcar los puntos que se han eliminado
    vector<bool> puntosActu(puntos.size(), true);
    size_t numPuntos = puntos.size();

    // Remover los puntos hasta que queden k puntos
    while (numPuntos > k) {
        // Obtener el triángulo con el área mínima
        auto [minArea, index] = *areaSet.begin();
        areaSet.erase(areaSet.begin());
        puntosActu[index] = false;
        numPuntos--;

        // Recalcular las áreas de los triángulos adyacentes
        if (index > 1 && puntosActu[index - 1] && puntosActu[index + 1]) {
            areaSet.erase({areas[index - 1], index - 1});
            areas[index - 1] = areaTriangulo(puntos[index - 2], puntos[index - 1], puntos[index + 1]);
            areaSet.insert({areas[index - 1], index - 1});
        }

        if (index < puntos.size() - 2 && puntosActu[index + 1] && puntosActu[index - 1]) {
            areaSet.erase({areas[index + 1], index + 1});
            areas[index + 1] = areaTriangulo(puntos[index - 1], puntos[index + 1], puntos[index + 2]);
            areaSet.insert({areas[index + 1], index + 1});
        }
    }

    // Construir el vector de puntos simplificados
    vector<vector<float>> simplifiedPoints;
    for (size_t i = 0; i < puntos.size(); ++i) {
        if (puntosActu[i]) {
            simplifiedPoints.push_back(puntos[i]);
        }
    }

    return simplifiedPoints;
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

    size_t k = 5;

    vector<vector<float>> simplified_points = visvalingamWhyatt(puntos, k);

    cout << "Simplified puntos:\n";
    for (const auto& point : simplified_points) {
        cout << "(" << point[0] << ", " << point[1] << ")\n";
    }

    // float minX = numeric_limits<float>::max(), minY = numeric_limits<float>::max();
    // float maxX = numeric_limits<float>::lowest(), maxY = numeric_limits<float>::lowest();

    // for (const auto& point : puntos) {
    //     if (point[0] < minX) minX = point[0];
    //     if (point[1] < minY) minY = point[1];
    //     if (point[0] > maxX) maxX = point[0];
    //     if (point[1] > maxY) maxY = point[1];
    // }

    // int margin = 50;
    // float scaleX = (1000.0f - 2 * margin) / (maxX - minX);
    // float scaleY = (1000.0f - 2 * margin) / (maxY - minY);
    // float scale = min(scaleX, scaleY);

    // // Create an image with a margin
    // cv::Mat image(1000 + 2 * margin, 1000 + 2 * margin, CV_8UC3, cv::Scalar(255, 255, 255));

    // // Draw original puntos in blue
    // for (const auto& point : puntos) {
    //     cv::circle(image, cv::Point((point[0] - minX) * scale + margin, 1000 - (point[1] - minY) * scale + margin), 5, cv::Scalar(255, 0, 0), -1);
    // }

    // // Draw simplified puntos in red
    // for (const auto& point : simplified_points) {
    //     cv::circle(image, cv::Point((point[0] - minX) * scale + margin, 1000 - (point[1] - minY) * scale + margin), 5, cv::Scalar(0, 0, 255), -1);
    // }

    // // Draw lines between original puntos
    // for (size_t i = 0; i < puntos.size() - 1; ++i) {
    //     cv::line(image, cv::Point((puntos[i][0] - minX) * scale + margin, 1000 - (puntos[i][1] - minY) * scale + margin), 
    //             cv::Point((puntos[i + 1][0] - minX) * scale + margin, 1000 - (puntos[i + 1][1] - minY) * scale + margin), 
    //             cv::Scalar(255, 0, 0), 1);
    // }

    // // Draw lines between simplified puntos
    // for (size_t i = 0; i < simplified_points.size() - 1; ++i) {
    //     cv::line(image, cv::Point((simplified_points[i][0] - minX) * scale + margin, 1000 - (simplified_points[i][1] - minY) * scale + margin), 
    //             cv::Point((simplified_points[i + 1][0] - minX) * scale + margin, 1000 - (simplified_points[i + 1][1] - minY) * scale + margin), 
    //             cv::Scalar(0, 0, 255), 1);
    // }

    // cv::imwrite("Visvalingam-Whyatt.png", image);

    return 0;
}
