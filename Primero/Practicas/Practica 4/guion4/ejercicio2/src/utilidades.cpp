#include <iostream>
#include "polilinea.h"
#include "punto.h"
#include "utilidades.h"

using namespace std;

ostream& operator<<(ostream &o, const Polilinea &mostrar) {
    o << endl;
    for (int i = 0; i < mostrar.num; i++) {
        o << "(" << mostrar.p[i].devolverX() << ", " << mostrar.p[i].devolverY() << ") ";
    }
    o << endl;
    return o;
}