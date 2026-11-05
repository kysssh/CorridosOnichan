#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

// En C++, los arreglos globales se inicializan automáticamente en 0.
int spf[MAXN];
int phi[MAXN];
int mobius[MAXN];
vector<int> primos;

void criba_lineal() {
    // Casos base matemáticos para el número 1
    spf[1] = 1;
    phi[1] = 1;
    mobius[1] = 1;

    for (int i = 2; i < MAXN; i++) {
        // PASO 1: Descubrir primos.
        // Si spf[i] sigue siendo 0, significa que nadie lo tachó. ¡Es primo!
        if (spf[i] == 0) {
            spf[i] = i;              // Su menor factor primo es él mismo
            phi[i] = i - 1;          // Regla: si P es primo, tiene P-1 coprimos
            mobius[i] = -1;          // Regla: tiene 1 factor primo (cantidad impar) -> -1
            primos.push_back(i);
        }

        // PASO 2: Tachar compuestos usando los primos descubiertos hasta ahora.
        for (int p : primos) {
            // Si nos salimos del límite del arreglo, detenemos el for interno
            if (i * p >= MAXN) break;

            // El menor factor primo del nuevo número (i * p) SIEMPRE será 'p', 
            // porque 'p' viene de la lista de primos ordenada de menor a mayor.
            spf[i * p] = p;
            
            // CASO A: 'i' ya era divisible por 'p' (el primo se está repitiendo)
            if (i % p == 0) { 
                mobius[i * p] = 0;              // Al tener un factor repetido, mobius es 0
                phi[i * p] = phi[i] * p;        // Por fórmula matemática de Euler
                
                // Rompemos el ciclo aquí para garantizar que (i * p) solo sea 
                // tachado por su MENOR factor primo. Si no rompemos, haríamos trabajo repetido.
                break; 
            } 
            // CASO B: 'i' y 'p' son diferentes (es la primera vez que agregamos 'p' a este número)
            else {
                mobius[i * p] = -mobius[i];          // Cambia de signo
                phi[i * p] = phi[i] * (p - 1);       // Multiplicamos por phi(p) que es (p-1)
            }
        }
    }
}

/*
    Al final de todo:
    1. SPF[X] guarda: El número primo más pequeño que divide a X
    Factorizar números masivos al instante haciendo saltos de división en O(logX)
    2. phi[X] (Función Phi de Euler): guarda la cantidad exacta de números entre 1 y X que son coprimos con X (es decir, que su GCD con X es 1)
    Te permite calcular el Inverso Modular cuando el problema te da un módulo M que no es primo. Usas el Teorema de Euler.
    3. mobius[X] (Función de Möbius): guarda una "etiqueta" que solo puede valer 0, 1 o -1, indicando la estructura interna de los primos de X.
    Guarda 0: Si X es divisible por el cuadrado de algún primo
    Guarda 1: Si X está formado por una cantidad par de primos distintos
    Guarda -1: Si X está formado por una cantidad impar de primos distintos
    Es el motor del Principio de Inclusión-Exclusión avanzado. 
    Si te piden contar "cuántos pares de un arreglo tienen GCD = 1 ", la función de Möbius te indica si debes sumar (1),
    restar (-1) o ignorar (0) los múltiplos durante el conteo para no duplicar datos
*/