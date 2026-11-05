#include <iostream>

using namespace std;
using ll = long long;

// Operaciones seguras
ll add(ll a, ll b, ll m) { return ((a % m) + (b % m)) % m; }
ll mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
ll sub(ll a, ll b, ll m) { return ((a % m) - (b % m) + m) % m; } // +m evita negativos

// Calcula (a^b) % m de forma iterativa
ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        // Si el bit menos significativo de b es 1 (b es impar)
        if (b & 1) res = res * a % m;
        
        a = a * a % m;
        b >>= 1; // b = b / 2
    }
    return res;
}

// O(logM)
ll modInverse(ll b, ll m) {
    // Solo funciona si m es primo
    return binpow(b, m-2, m);
}

// Para hacer (a/b) % m
ll modDivide(ll a, ll b, ll m) {
    a %= m;
    ll inv = modInverse(b, m);
    return (a * inv) % m;
}
