
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    // Opciones que podemos utilizar.
    // ADAPTAR SEGUN EL PROBLEMA.
    vector<int> opciones = {1, 2, 3, 4, 5, 6};

    // dp[s] = cantidad de secuencias ordenadas
    // que permiten obtener la suma s.
    vector<ll> dp(n + 1, 0);
    // Existe una manera de obtener suma 0:
    // no elegir ningún elemento.
    dp[0] = 1;

    // Calculamos las respuestas para cada suma.
    for (int s = 1; s <= n; s++) {
        // Probamos cada opción disponible.
        for (int x : opciones) {

            if (s >= x) {
                dp[s] = (dp[s] + dp[s - x]) % MOD;
            }
        }
    }
    cout << dp[n] << "\n";
}
// Complejidad: O(n*k) tiempo y O(n) memoria