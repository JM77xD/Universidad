#include <iostream>
#include "pareja.h"
#include "precuencias.h"
#include "utilidades.h"

using namespace std;

ostream & operator<<(ostream &o, const Precuencias &mostrar) {
    for (int i = 0; i < mostrar.nParejas; i++) {
        o << "Dato: " << mostrar.parejas[i].devolverDato() << "\tNúmero de veces: " << mostrar.parejas[i].devolverNVeces() << endl;
    }
    return o;
}