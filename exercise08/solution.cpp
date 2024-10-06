#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>

using namespace std;

// A utility function to find the distance between two points
double dist(const vector<float>& p1, const vector<float>& p2) {
    return sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) +
                (p1[1] - p2[1]) * (p1[1] - p2[1]));
}

// A utility function to find the distance between the closest points of strip of given size. All points in strip[] are sorted according to y coordinate. They all have an upper bound on minimum distance as d.
double stripClosest(vector<vector<float>>& strip, double d, pair<vector<float>, vector<float>>& closestPair) {
    double min = d; // Initialize the minimum distance as d

    sort(strip.begin(), strip.end(), [](const vector<float>& p1, const vector<float>& p2) {
        return p1[1] < p2[1];
    });

    // Pick all points one by one and try the next points till the difference between y coordinates is smaller than d.
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j][1] - strip[i][1]) < min; ++j) {
            double distance = dist(strip[i], strip[j]);
            if (distance < min) {
                min = distance;
                closestPair = {strip[i], strip[j]};
            }
        }
    }

    return min;
}

// A recursive function to find the smallest distance. The array P contains all points sorted according to x coordinate
double closestUtil(vector<vector<float>>& P, size_t n, pair<vector<float>, vector<float>>& closestPair) {
    // If there are 2 or 3 points, then use brute force
    if (n <= 3) {
        double min = DBL_MAX;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                double distance = dist(P[i], P[j]);
                if (distance < min) {
                    min = distance;
                    closestPair = {P[i], P[j]};
                }
            }
        }
        return min;
    }

    // Find the middle point
    size_t mid = n / 2;
    vector<float> midPoint = P[mid];

    // Consider the vertical line passing through the middle point calculate the smallest distance dl on left of middle point and dr on right side
    pair<vector<float>, vector<float>> leftPair, rightPair;
    double dl = closestUtil(P, mid, leftPair);
    double dr = closestUtil(P, n - mid, rightPair);

    // Find the smaller of two distances
    double d = min(dl, dr);
    closestPair = (dl < dr) ? leftPair : rightPair;

    // Build an array strip[] that contains points close (closer than d) to the line passing through the middle point
    vector<vector<float>> strip;
    for (size_t i = 0; i < n; i++) {
        if (abs(P[i][0] - midPoint[0]) < d) {
            strip.push_back(P[i]);
        }
    }

    // Find the closest points in strip. Return the minimum of d and closest distance in strip[]
    double stripDist = stripClosest(strip, d, closestPair);
    if (stripDist < d) {
        d = stripDist;
    }

    return d;
}

// The main function that finds the smallest distance
pair<vector<float>, vector<float>> closest(vector<vector<float>>& P) {
    size_t n = P.size();
    sort(P.begin(), P.end(), [](const vector<float>& p1, const vector<float>& p2) {
        return p1[0] < p2[0];
    });

    pair<vector<float>, vector<float>> closestPair;
    closestUtil(P, n, closestPair);
    return closestPair;
}

int main() {
    vector<vector<float>> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    pair<vector<float>, vector<float>> closestPair = closest(P);
    cout << "The closest pair of points are: (" << closestPair.first[0] << ", " << closestPair.first[1] << ") and ("
         << closestPair.second[0] << ", " << closestPair.second[1] << ")" << endl;
    return 0;
}



