#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> state;
//Hablemos sobre el vector state:
/*
    Estado 0 (BLANCO): El nodo aun no ha sido visitado/descubierto
    Estado 1 (GRIS): El DFS ya entro a este nodo, pero aun no termina de explorar todos sus descendientes
    Estado 2 (NEGRO): El DFS entro al nodo, exploro todos sus vecinos y sus ramas y la funcion ya hizo return, el nodo sale de la pila
*/

bool dfs_cycle(int u) {
    state[u] = 1; // Encontramos al nodo, pasa de blanco a gris
    for(int v : adj[u]) {
        if(state[v] == 1) return true; // Encontramos un apuntador a otro nodo gris (apunta a un ancestro que todavia esta en la pila)
        if(state[v] == 0) {
            if(dfs_cycle(v)) return true; // Si es blanco, exploramos recursivamente
        }
        // Si es 2 se ignora de manera segura
    }
    state[u] = 2; // Procesanos todos sus vecinos, pasa a ser negro
    return false;
}

/*
    Clasificacion de las aristas:
    1. Tree Edge: Apunta a un nodo BLANCO. Es la arista por la que descubrimos
    un nuevo nodo por primera vez
    2. Back Edge (Arista hacia atras): Ocurre cuando desde el nodo actual en el que estas parado (que es GRIS) intentas seguir una 
    arista que apunta a un nodo que tambien es GRIS
    3. Forward Edge (Arista hacia adelante): Apunta a un nodo NEGRO que es un descendiente en el arbol DFS, pero no fuiste tu quien lo descubrio directamente
    4. Cross Edge (Arista cruzada): Apunta a un nodo NEGRO que pertenece a otra rama del arbol DFS que ya fue explorada completamente y cerrada
*/