
/*
    Tema: Operaciones Basicas de Bitwise y Bitmask
    Una mascara representa un conjunto de elementos.
    Cada bit representa la presencia (1) o ausencia (0)
    de un elemento.

    IMPORTANTE:
    - Las posiciones empiezan desde 0.
    - uint64_t permite representar 64 bits.
    - Los indices de bits deben estar entre 0 y 63.
*/

#include <bits/stdc++.h>
using namespace std;
using ull = uint64_t;

// 1. OPERACIONES SOBRE BITS INDIVIDUALES

// Comprobar si el bit i esta encendido.
bool check_bit(ull mask, int i) {
    return (mask >> i) & 1ULL;
}

// Encender el bit i.
ull set_bit(ull mask, int i) {
    return mask | (1ULL << i);
}

// Apagar el bit i.
ull clear_bit(ull mask, int i) {
    return mask & ~(1ULL << i);
}

// Cambiar el estado del bit i.
ull toggle_bit(ull mask, int i) {
    return mask ^ (1ULL << i);
}

// 2. OPERACIONES ESPECIALES

// Obtener el bit encendido menos significativo.
ull lowest_bit(ull mask) {
    return mask & -mask;
}

// Eliminar el bit encendido menos significativo.
ull remove_lowest_bit(ull mask) {
    return mask & (mask - 1);
}

// Comprobar si un numero positivo es potencia de dos.
bool is_power_of_two(ull x) {
    return x > 0 && (x & (x - 1)) == 0;
}

// Contar la cantidad de bits encendidos.
int count_bits(ull mask) {
    return __builtin_popcountll(mask);
}

// Contar ceros consecutivos desde la derecha.
// Requiere que mask != 0.
int trailing_zeros(ull mask) {
    return __builtin_ctzll(mask);
}

// Contar ceros consecutivos desde la izquierda.
// Requiere que mask != 0.
int leading_zeros(ull mask) {
    return __builtin_clzll(mask);
}

// 3. OPERACIONES ENTRE CONJUNTOS


// Union: elementos que pertenecen a A o B.
ull union_mask(ull A, ull B) {
    return A | B;
}

// Interseccion: elementos presentes en ambos.
ull intersection_mask(ull A, ull B) {
    return A & B;
}

// Diferencia: elementos de A que no pertenecen a B.
ull difference_mask(ull A, ull B) {
    return A & ~B;
}

// Diferencia simetrica: elementos presentes en
// exactamente uno de los dos conjuntos.
ull symmetric_difference_mask(ull A, ull B) {
    return A ^ B;
}

// Complemento limitado a los primeros n bits.
// Requiere 0 <= n <= 64.
ull complement_mask(ull mask, int n) {
    if (n == 0) return 0;

    if (n == 64) return ~mask;

    ull valid_mask = (1ULL << n) - 1;

    return (~mask) & valid_mask;
}

// 4. ITERAR SOBRE TODOS LOS BITS

// Recorrer todas las posiciones de una mascara.
void iterate_all_bits(ull mask) {
    for (int i = 0; i < 64; i++) {
        if (check_bit(mask, i)) {
            // El bit i esta encendido.
            cout << i << " ";
        }
    }
}

// Recorrer solamente los bits encendidos.
void iterate_set_bits(ull mask) {
    while (mask) {
        // Aislar el bit encendido menos significativo.
        ull bit = mask & -mask;

        // Obtener su posicion.
        int pos = __builtin_ctzll(mask);

        cout << pos << " ";

        // Eliminar el bit procesado.
        mask -= bit;
    }
}

// 5. ENUMERAR TODAS LAS SUBMASCARAS

// Recorrer todas las submascaras NO vacias de mask.
void iterate_submasks(ull mask) {
    for (ull sub = mask; sub > 0; sub = (sub - 1) & mask) {
        // Procesar la submascara actual.
        cout << sub << "\n";
    }
}

// Recorrer todas las submascaras, incluyendo la vacia.
void iterate_submasks_with_empty(ull mask) {
    for (ull sub = mask; ; sub = (sub - 1) & mask) {
        // Procesar la submascara actual.
        cout << sub << "\n";

        if (sub == 0) break;
    }
}

