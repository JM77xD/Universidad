#include <iostream>
#include "valor.h"
#include "matrizdispersa.h"
#include "utilidades.h"

using namespace std;

int main() {
    MatrizDispersa primera;
    primera.inicializarMatriz();
    cout << primera;

    MatrizDispersa segunda;
    segunda.inicializarMatriz();
    cout << segunda;


    MatrizDispersa copia(primera + segunda);
    cout << copia;
}