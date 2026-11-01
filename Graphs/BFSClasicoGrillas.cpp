#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<string> grid;
vector<vector<int>> dist;

const int df[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

void bf(int sf, int sc) {
    dist.assign(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    dist[sf][sc] = 0;
    q.push({sf, sc});

    while(!q.empty()) {
        auto [f, c] = q.front();
        q.pop();
        for(int i=0; i<4; ++i) {
            int nf = f + df[i];
            int nc = c + dc[i];
            if(nf < 0 || nf > n || nc < 0 || nc > n || grid[nf][nc] == '#' || grid[nf][nc] == -1) {
                continue;
            }
            dist[nf][nc] = dist[f][c] + 1;
            q.push({nf, nc});
        }
    }
}

void solve() {
    cin >> n >> m;
    grid.resize(n);
    for(int i=0; i<n; ++i) {
        cin >> grid[i];
    }
    int sf, sc;
    cin >> sf >> sc;
    bf(sf, sc);

    for(int i=0; i<n; ++i) {
        for(int j=0; i<m; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}

