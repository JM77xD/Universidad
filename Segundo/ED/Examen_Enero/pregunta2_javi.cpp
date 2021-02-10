#include<list>
#include<iostream>
#include<cassert>

using namespace std;

int max_sublist_m(list<int> &L, int m) {
    assert(m > 0 && m <= L.size());

    list<int>::iterator it = L.begin(), aux;

    int suma, suma_aux;

    while(aux != L.end()) {
        suma_aux = 0;
        aux = it;

        for (int i = 0; i < m; i++, aux++) {
            suma_aux += *aux;
        }

        if (suma_aux > suma)
            suma = suma_aux;

        it++;
    }

    return suma;

}