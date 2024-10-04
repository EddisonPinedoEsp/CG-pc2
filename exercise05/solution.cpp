#include<iostream>
#include<vector>
#include<cmath>

using namespace std;


// Given a non-crossed polygon P ∈ R2 and a points A, write a function to decide if A ∈ P

bool point_in_polygon(const vector<vector<float>>& P, const vector<float>& A) {
    int n = P.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((P[i][1] > A[1]) != (P[j][1] > A[1])) &&
            (A[0] < (P[j][0] - P[i][0]) * (A[1] - P[i][1]) / (P[j][1] - P[i][1]) + P[i][0])) {
            inside = !inside;
        }
    }
    return inside;
}

void test() {
    vector<vector<float>> P = {
        {1.2, 5.47},
        {8.55, 17.83},
        {16.74, 7.64},
        {14.6, 3.73},
        {8.45, 1.35},
        {4.55, 1.07},
        {1.4, 1.49},
        {0.5, 3.35}
    };

    vector<vector<float>> points = {
                {1.2, 5.47},
        {8.55, 17.83},
        {16.74, 7.64},
        {14.6, 3.73},
        {8.45, 1.35},
        {4.55, 1.07},
        {1.4, 1.49},
        {0.5, 3.35},
        {3.35, 6.48},
        {4.16, 8.61},
        {5, 10},
        {7.15, 11.83},
        {4.53, 11.07},
        {10.83, 14.82},
        {15.48, 5.88},
        {12.33, 2.86},
        {6.69, 1.42},
        {2.7, 1.32},
        {3.53, 4.01},
        {5.48, 2.63},
        {14.8, 7.46},
        {13.53, 8.55},
        {12.38, 10.85},
        {11.23, 12.98}
    };

    for (const auto& A : points) {
        cout << "Point (" << A[0] << ", " << A[1] << ") is " 
            << (point_in_polygon(P, A) ? "1" : "0");
        cout << endl; 
    }
}

int main() {
    test();
    return 0;
}
