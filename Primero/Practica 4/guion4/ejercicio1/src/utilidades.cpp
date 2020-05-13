#include <iostream>
#include <string>
#include "bigint.h"
#include "utilidades.h"

using namespace std;


ostream& operator << (ostream &o, const BigInt &mostrar) {
    for (int i = mostrar.numDigitos - 1; i >= 0; i++) o << mostrar.p[i];
    return o;
}