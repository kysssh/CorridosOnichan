
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

void solve() {
    int n, m;
    cin >> n >> m;
    // Valores de los elementos disponibles.
    vector<int> monedas(m);
    for (int i = 0; i < m; i++) {
        cin >> monedas[i];
    }

    // dp[s] = cantidad minima de elementos
    // necesarios para alcanzar la suma s.
    vector<int> dp(n + 1, INF);

    // Para alcanzar suma 0 necesitamos 0 elementos.
    dp[0] = 0;

    // Calculamos la respuesta para cada suma.
    for (int s = 1; s <= n; s++) {
        // Probamos cada elemento disponible.
        for (int x : monedas) {
            if (s >= x && dp[s - x] != INF) {
                // Utilizamos un elemento x adicional.
                dp[s] = min(dp[s], dp[s - x] + 1);
            }
        }
    }
    // Verificamos si existe una forma de alcanzar n.
    if (dp[n] == INF) {
        cout << "-1" << "\n";
    } else {
        cout << dp[n] << "\n";
    }
}

