#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> vis;
bool dfs_cycle(int u, int p) {
    vis[u] = true;
    for(int v : adj[u]) {
        // Si el vecino es el padre inmediato de donde venimos simplemente ignoramos la arista de regreso trivial
        if(v == p) continue;
        // Si el vecino ya estaba visitado y no es el padre, entonces hay un ciclo
        if(vis[v]) return true;
        // Si no ha sido visitado, continuamos la busqueda, u pasa a ser el padre de v
        if(dfs_cycle(v, u)) return true;
    }
    return false; // Si es que no se encuentran ciclos en esta rama
}