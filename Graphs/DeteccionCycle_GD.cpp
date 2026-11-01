#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using v = vector<ll>;
using pii = pair<int, int>;
#define pb push_back
#define all(x) (x).begin(), (x).end()
vector<vector<ll>> adj;
vector<bool> vis;
vector<ll> state;
vector<ll> parent;
ll n, m;
ll cycle_start = -1, cycle_end = -1;
ll skip_u = -1, skip_v = -1; // Representan la arista que queremos eliminar durante el recorrido
// Las variables globales skip_v y skip_u se usan dentro de la funcion checkDfs

// Funcion Principal: DFS para deteccion de ciclos (1)
bool dfs_cycle(ll u) {
    state[u] = 1;
    for(ll v : adj[u]) {
        if(state[v] == 1) {
            cycle_start = v;
            cycle_end = u;
            return true;
        }
        if(state[v] == 0) {
            parent[v] = u; // El nodo padre de v es u, para reconstruccion de caminos
            if(dfs_cycle(v)) return true;
        }
    }
    state[u] = 2;
    return false;
}
bool checkDfs(ll u) { // Recorre el grafo en profundidad comprobando si existe algun ciclo activo ignorando unicamente la arista skip_u -> skip_v
    state[u] = 1; // Marca como "en proceso / en la pila"
    for(ll v : adj[u]) {
        // SI LA ARISTA ACTUAL ES LA QUE QUEREMOS OMITIR, LA IGNORAMOS
        if(skip_u == u && skip_v == v) continue;
        if(state[v] == 1) return true; // Detectamos un ciclo
        if(state[v] == 0) {
            if(checkDfs(v)) return true;
        }
    }
    state[u] = 2;
    return false; // No se encontro un ciclo
}

bool isDag() { // Funcion que verifica si un grafo dirigido es aciclico
    fill(state.begin(), state.end(), 0); // Sirve para limpiar el estado de todos los nodos a 0 antes de volver a verificar el grafo
    for(ll i=1; i<=n; ++i) {
        if(state[i] == 0) {
            if(checkDfs(i)) return false;
        }
    }
    return true;
}
void solve() {
    cin >> n >> m;
    adj.assign(n+1, vector<ll>());
    state.assign(n+1, 0);
    parent.assign(n+1, -1);
    for(ll i=0; i<m; ++i) {
        ll u, v; cin >> u >> v;
        adj[u].pb(v);
    }
    bool hayCiclo = false;
    // Aqui verificamo si hay un ciclo
    for(ll i=1; i<=n; ++i) {
        if(state[i] == 0) {
            if(dfs_cycle(i)) {
                hayCiclo = true;
                break;
            }
        }
    }
    if(!hayCiclo) {
        cout << "YES\n";
        return;
    }
    vector<pair<ll, ll>> cicloArista; // Guarda la representacion exacta de cada arista del ciclo detectado en forma de pares (origen, destino)
    cicloArista.pb({cycle_end, cycle_start}); // Es la arista de retroceso
    /*
        1. Guarda la arista de retroceso: La arista que cierra el ciclo se guarda como el primer par
        2. Guarda las aristas de avance (reconstruidas con parent)
        El bucle while recorre hacia atras el camino usando parent para recuperar cada una de las aristas que llevaron cycle_start hasta cycle_end
        3. Permite iterar para probar cual arista eliminar: En la fase final, el vector nos permite hacer un bucle limpio
        sobre cada arista del ciclo, asignando en cada intento a skip_u y skip_v para verificar si quitandola el grafo se vuelve un DAG.

        VEAMOS EL CODIGO:
    */

    ll ocurr = cycle_end;
    while(ocurr != cycle_start && ocurr != -1) {
        ll p = parent[ocurr];
        if(p == -1) break;
        cicloArista.pb({p, ocurr});
        ocurr = p;
    }
    for(auto esq : cicloArista) {
        skip_u = esq.first;
        skip_v = esq.second;
        if(isDag()) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// El problema se trata en saber si es o no posible eliminar una arista de tal manera que el grafo dirigido se vuelva aciclico