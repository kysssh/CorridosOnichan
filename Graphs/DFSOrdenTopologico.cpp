#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector<vector<int>> adj;
vector<int> state;
vector<int> orden_top;
bool hayCiclo = false;

void dfs_cycle(int u) {
    state[u] = 1;
    for(int v : adj[u]) {
        if(state[v] == 1) {
            hayCiclo = true;
            return;
        }
        if(state[v] == 0) {
            dfs_cycle(v);
            if(hayCiclo) return;
        }
    }
    state[u] = 2;
    orden_top.pb(u);
}

void solve () {
    int n, m; cin >> n >> m;
    adj.assign(n+1, vector<int>());
    orden_top.clear();
    state.assign(n+1, 0);
    hayCiclo = false;
    for(int i=0; i<m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
    }
    for(int i=n; i>0; --i) {
        if(state[i] == 0) {
            dfs_cycle(i);
            if(hayCiclo) return;
        }
    }
    reverse(orden_top.begin(), orden_top.end());
    for(int x : orden_top) {
        cout << x << " ";
    }
    cout << "\n";
}