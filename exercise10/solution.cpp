#include <iostream>
#include <vector>

using namespace std;

// Helper function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to calculate the nth Catalan number
unsigned long long catalan(int n) {
    return factorial(2 * n) / (factorial(n + 1) * factorial(n));
}

// Function to calculate the number of triangulations for a given polygon
int numberOfTriangulations(vector<vector<float>> polygon) {
    int n = polygon.size();

    // A polygon must have at least 3 sides for triangulation
    if (n < 3) {
        cerr << "A polygon must have at least 3 sides for triangulation!" << endl;
        return 0;
    }

    // The number of triangulations for a polygon with n sides is the (n-2)th Catalan number
    return catalan(n - 2);
}

int main() {
    // Example usage with a polygon of 6 vertices
    vector<vector<float>> polygon = {{0, 0}, {1, 0}, {1, 1}, {0.5, 1.5}, {0, 1}, {-0.5, 0.5}};
    cout << "Number of triangulations: " << numberOfTriangulations(polygon) << endl;

    return 0;
}
