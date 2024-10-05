#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <set>
#include <tuple>

using namespace std;

// Function to calculate the area of a triangle formed by three points
float triangleArea(const vector<float>& p1, const vector<float>& p2, const vector<float>& p3) {
    return fabs(p1[0] * (p2[1] - p3[1]) +
                p2[0] * (p3[1] - p1[1]) +
                p3[0] * (p1[1] - p2[1])) / 2.0;
}

// Function to implement the Visvalingam-Whyatt algorithm
vector<vector<float>> visvalingamWhyatt(const vector<vector<float>>& points, size_t k) {
    if (points.size() <= k) {
        return points; // No simplification needed
    }

    // A vector to store areas of triangles at each point
    vector<float> areas(points.size(), numeric_limits<float>::max());

    // Set to store {area, index} for efficient removal of points with the smallest area
    set<pair<float, size_t>> areaSet;

    // Compute the initial triangle areas
    for (size_t i = 1; i < points.size() - 1; ++i) {
        float area = triangleArea(points[i - 1], points[i], points[i + 1]);
        areas[i] = area;
        areaSet.insert({area, i});
    }

    // The simplified points (initially all points are present)
    vector<bool> isPointPresent(points.size(), true);
    size_t numPoints = points.size();

    // Remove points until only k points remain
    while (numPoints > k) {
        // Get the point with the smallest area
        auto [minArea, index] = *areaSet.begin();
        areaSet.erase(areaSet.begin());
        isPointPresent[index] = false; // Mark point as removed
        numPoints--;

        // Recalculate the area for neighbors of the removed point
        if (index > 1 && isPointPresent[index - 1] && isPointPresent[index + 1]) {
            // Recalculate area for the previous point
            areaSet.erase({areas[index - 1], index - 1});
            areas[index - 1] = triangleArea(points[index - 2], points[index - 1], points[index + 1]);
            areaSet.insert({areas[index - 1], index - 1});
        }

        if (index < points.size() - 2 && isPointPresent[index + 1] && isPointPresent[index - 1]) {
            // Recalculate area for the next point
            areaSet.erase({areas[index + 1], index + 1});
            areas[index + 1] = triangleArea(points[index - 1], points[index + 1], points[index + 2]);
            areaSet.insert({areas[index + 1], index + 1});
        }
    }

    // Build the simplified points list based on remaining points
    vector<vector<float>> simplifiedPoints;
    for (size_t i = 0; i < points.size(); ++i) {
        if (isPointPresent[i]) {
            simplifiedPoints.push_back(points[i]);
        }
    }

    return simplifiedPoints;
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

    size_t k = 5;

    vector<vector<float>> simplified_points = visvalingamWhyatt(points, k);

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

    cv::imwrite("points_VW.png", image);

    return 0;
}
