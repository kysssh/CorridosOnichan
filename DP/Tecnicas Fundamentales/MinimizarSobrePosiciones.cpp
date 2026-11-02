#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // dp[i] = costo minimo para llegar al estado i
    vector<ll> dp(n, INF);

    // El estado inicial no tiene costo
    dp[0] = 0;
    // Calculamos el costo minimo para cada estado
    for (int i = 1; i < n; ++i) {
        // Probamos todas las posiciones anteriores
        // desde las que podemos llegar a i.
        for (int j = 1; j <= i && j <= k; ++j) {
            // Calculamos el costo de ir desde i-j hasta i
            // ADAPTAR ESTA LINEA SEGUN EL PROBLEMA.
            ll cost = abs(a[i] - a[i-j]);
            // Costo acumulado: llegar al estado anterior
            // y despues realizar la transicion
            ll sum = dp[i-j] + cost;
            // Nos quedamos con el menor costo
            dp[i] = min(dp[i], sum);
        }
    }
    cout << dp[n-1] << "\n";
}
