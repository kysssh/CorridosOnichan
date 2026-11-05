#include <iostream>
#include <vector>

using namespace std;

// Implementación estándar de la Criba
vector<int> criba(int n) {
    // Usamos vector<char> en lugar de vector<bool> porque en C++ vector<bool> 
    // está optimizado para memoria (bits), lo que lo hace ligeramente más lento en tiempo.
    vector<char> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    // Solo necesitamos iterar hasta la raíz cuadrada de n
    for (long long i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            // Empezamos a tachar desde i * i. 
            // Los múltiplos anteriores (como i*2, i*3) ya fueron tachados por primos menores.
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}