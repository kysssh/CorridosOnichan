#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Estructura que almacenara los resultados que deseamos del BFS
struct BFSResults {
    vector<int> dist;
    vector<int> parent;
};

BFSResults bfs(int origen, int n, vector<vector<int>>& adj) {
    // Inicializamos con -1
    vector<int> dist(n+1, -1);
    vector<int> parent(n+1, -1);
    queue<int> q;

    dist[origen] = 0;
    q.push(origen);

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return {dist, parent};
}

//Obtener el camino mas corto desde el nodo de origen hacia el final o el nodo destino (fin)
vector<int> getPath(int fin, vector<int>& parent) {
    vector<int> path;
    // Retrocedemos desde fin usando el arreglo parent
    // El origen tendra parent -1, por lo que ahi se acaba el ciclo
    for(int v = fin; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj;
    for(int i=0; i<m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Para grafos no dirigidos
    }
    // Queremos ir del nodo 1 al nodo N
    int start_node = 1;
    int end_node = n;
    
    BFSResults ans = bfs(start_node, n, adj);

    if(ans.dist[end_node] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> path = getPath(end_node, ans.parent);
        cout << path.size() << "\n";
        for(int i=0; i<path.size(); ++i) {
            cout << path[i] << (i+1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }
}