#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int> bfs(int n, int m, vector<int>& origenes) {
    unordered_map<int, int> dist;
    queue<int> q;
    vector<int> pos;
    for(int origen : origenes) {
        dist[origen] = 0;
        q.push(origen);
    }
    const int dx[] = {-1, 1};
    while(pos.size() < m && !q.empty()) {
        int u = q.front();
        q.pop();
        for(int i=0; i<2; ++i) {
            int nx = u + dx[i];
            if(dist.find(nx) == dist.end()) {
                dist[nx] = dist[u] + 1;
                q.push(nx);
                pos.pb(nx);
                if(pos.size() == m) {
                    return pos;
                }
            }
        }
    }
    return pos; // Pos sirve para almacenar y retornar el orden en el que el BFS descubre nuevas posiciones en la recta 1D
}