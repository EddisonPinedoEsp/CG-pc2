#include <vector>
using namespace std;

const int MOD = 1000000007;

vector<long int> numeros_catalan(int k) {
    vector<long int> catalan(k + 1, 0);
    catalan[0] = 1;  // C_0 es 1

    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < i; ++j) {
            catalan[i] = (catalan[i] + 1LL * catalan[j] * catalan[i - 1 - j]) % MOD;
        }
    }

    return catalan;
}

int num_of_triangulations(int n) {
    if (n < 3) {
        return 0;  // No es posible hacer triangulaciones en polígonos con menos de 3 lados
    }

    vector<long int> catalan = numeros_catalan(n - 2);

    return catalan[n - 2];
}
