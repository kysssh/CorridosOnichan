#include <iostream>
#include <vector>

using namespace std;
const int MAXN = 1000005;
vector<int> spf(MAXN);

void build_spf() {
    // 1. Cada número es su propio SPF por defecto (asumimos que todos son primos)
    for (int i = 2; i < MAXN; ++i) {
        spf[i] = i; 
    }
    
    // 2. Modificamos la Criba
    for (long long i = 2; i * i < MAXN; ++i) {
        if (spf[i] == i) { // Si 'i' es primo
            for (long long j = i * i; j < MAXN; j += i) {
                // SOLO lo tachamos si nadie más pequeño lo ha tachado antes
                if (spf[j] == j) { 
                    spf[j] = i;
                }
            }
        }
    }
}

// Retorna los factores primos de X en O(log X)
vector<int> get_factorization(int x) {
    vector<int> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}