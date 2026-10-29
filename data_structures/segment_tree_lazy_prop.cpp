#include <bits/stdc++.h>
#include <concepts>
using namespace std;
template <typename T>
concept AptObj = requires(T a, T b) {
    { a + b } -> convertible_to<T>;    
} && totally_ordered<T>;
template <AptObj T>
struct SegTree {
    vector<T> nodes, lazy;
    int n;
    T NEUT, NEUT_LAZY;
    SegTree(vector<T> &x, T neut = T{}, T neut_lazy = T{}) : n(x.size()), NEUT(neut), NEUT_LAZY(neut_lazy){
        nodes.assign(2 * n, NEUT), lazy.assign(2 * n, NEUT_LAZY);
        build(x, 1, 0, n - 1);
    }
    T f(T a, T b){
         return a + b;
    }
    void aply(T val, int id, int l, int r){
        nodes[id] += (r - l - 1) * val;
        lazy[id] += val;
    }
    void build(vector<T> &x, int id, int l, int r){
        if(l == r) nodes[id] = x[l]; //el nodo es una hoja, se asigna el valor del vector original
        else{ //caso contrario, nota: los indices para nodes y lazy usan un recorrido inorder
            int m = (l + r) / 2;
            int idl = id + 1;
            int idr = id + 2*(m - l + 1);
            build(x, idl, l, m);
            build(x, idr, m+1, r);
            nodes[id] = f(idl, idr);
        }
    }
    void push(int id, int l, int r){
        if(l == r || lazy[id] == NEUT_LAZY) return;
        int m = (l + r) / 2;
        int idl = id + 1;
        int idr = id + 2*(m - l - 1);
        aply(lazy[id], idl, l, m);
        aply(lazy[id], idr, m+1, r);
        lazy[id] = NEUT_LAZY;
    }
    void update(int ql, int qr, T val, int id, int l, int r){
        if(ql <= l && r <= qr){
            aply(val, id, l, r);
            return;
        }
        else if(r < ql || l > qr){
            return;
        }
        push(id, l, r); //empujar cualquier lazy ya existente
        int m = (l + r)/2;
        int idl = id + 1;
        int idr = id + 2*(m - l - 1);
        update(ql, qr, val, idl, l, m);
        update(ql, qr, val, idr, m+1, r);
        nodes[id] = f(nodes[idl], nodes[idr]);
    }
    T query(int ql, int qr, int id, int l, int r){
        if(r < ql && l > qr){
            return NEUT;
        }
        else if(ql <= l && r <= qr){
            return nodes[id];
        }
        push(id, l, r);
        int m = (l + r) / 2;
        int idl = id + 1;
        int idr = id + 2*(m - l - 1);
        return f(query(ql, qr, idl, l, m), query(ql, qr, idr, m+1, r));
    }
};
