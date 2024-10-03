# include <iostream>
# include <vector>

using namespace std;

// Let P be a polygon, represented as a list of adjacent vertices. For example: if P = [p0, p1, p2, . . . , pn−1], the vertex p2 is adjacent to the vertices p1 and p3, the vertex p5 is adjacent to the vertices p4 and p6, and so on (notice that the vertex pn−1 will be adjacent to pn−2 and to p0).
// Decide if P, represented in the mentioned way, is convex or not. 
// The function should return true if the polygon is convex, and false otherwise.

// bool esConvexo(vector<vector<int>> P) {
//     int cantidaDeVertices = P.size();
//     long long prev = 0;  
//     long long curr = 0; 

//     for (int i = 0; i < cantidaDeVertices; i++) {
//         int x1 = P[(i + 1) % cantidaDeVertices][0] - P[i][0];
//         int y1 = P[(i + 1) % cantidaDeVertices][1] - P[i][1];
//         int x2 = P[(i + 2) % cantidaDeVertices][0] - P[(i + 1) % cantidaDeVertices][0];
//         int y2 = P[(i + 2) % cantidaDeVertices][1] - P[(i + 1) % cantidaDeVertices][1];
//         curr = x1 * y2 - x2 * y1;
//         if (curr != 0) {
//             if (curr * prev < 0) {
//                 return false;
//             }
//             prev = curr;
//         }
//     }
//     return true;
// }


int orientacion(float xa, float ya, float xb, float yb, float xc, float yc) {
    // Calcula el producto cruz para la orientación de tres puntos (xa, ya), (xb, yb), (xc, yc)

    float orientation = (yb - ya) * (xc - xb) - (xb - xa) * (yc - yb);

    // Si el producto cruz es 0, los puntos son colineales
    if (orientation == 0) {
        return 0;
    }

    return (orientation > 0) ? 1 : 2;
}

bool esConvexo(vector<vector<int>> P) {
    if (P.size() < 2) {
        return false;
    }

    vector<int> A;
    vector<int> B;
    vector<int> C;

    for (int i = 2; i <= P.size()+1; i++) {
        A = P[i % P.size()];
        B = P[(i + 1) % P.size()];
        C = P[(i + 2) % P.size()];

        if (orientacion(A[0], A[1], B[0], B[1], C[0], C[1]) == 2) {
            return false;
        }
    }
    
    return true;

}


void test() {
    vector<vector<int>> P = {{0, 0}, {1, 1}, {2, 2}, {2, 1}};
    cout << esConvexo(P) << endl; // 1

    // P = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
    // cout << esConvexo(P) << endl; // 0

    // P = {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {2, 0}};
    // cout << esConvexo(P) << endl; // 1

    P = {{0, 0}, {0, 4}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {3, 0}, {2, 0}};
    cout << esConvexo(P) << endl; // 1
}


int main() {

    test();
    return 0;
}


