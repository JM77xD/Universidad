#include <iostream>
#include "punto.h"
#include "polilinea.h"
#include "utilidades.h"

using namespace std;

int main() {
    Polilinea nueva;
    cout << "Polilínea 1";
    nueva.inicializarPolilinea();
    cout << nueva;
    Polilinea copia;
    cout << "\nPolilínea 2";
    copia.inicializarPolilinea();
    cout << copia;
    Polilinea suma(nueva + copia);
    cout << "\nPolilínea suma";
    cout << suma;
}