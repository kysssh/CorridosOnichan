#include <bits/stdc++.h>
using namespace std;
using ll = long long;        
using v = vector<ll>;           
using pii = pair<int, int>;       
#define pb push_back             
#define all(x) (x).begin(), (x).end() 
vector<vector<ll>> adj;
vector<bool> vis;

void dfs(ll u) {
    vis[u] = true;
    for(ll v : adj[u]) {
        if(!vis[v]) {
            dfs(v); // Se encarga de marcar como true todos los nodos (o vertices) conectados 
        }
    }
}
void solve() {
    ll n, m; cin >> n >> m;
    adj.assign(n+1, vector<ll>());
    vis.assign(n + 1, false);
    for(ll i=0; i<n; ++i) {
        ll u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    ll comp = 0; // Variable que detecta las componentes conexas de un grafo
    for(ll i=1; i<=n; ++i) {
        if(!vis[i]) {
            comp++; 
            dfs(i); // Cada ves que se encuentre una nueva componente conexa, el dfs busca todos los lugares por donde este conectado
        }
    }
}
