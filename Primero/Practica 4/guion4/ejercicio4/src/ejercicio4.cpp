#include <iostream>
#include <string>
#include "pareja.h"
#include "precuencias.h"
#include "utilidades.h"

using namespace std;

int main() {
    string secuencia, secuencia2;
    cout << "Introduzca una secuencia de numeros enteros (123456789): ";
    getline(cin, secuencia);
    Precuencias primeraSecuencia(secuencia);
    cout << endl << primeraSecuencia;

    cout << "Introduzca otra secuencia para comparar: ";
    getline(cin, secuencia2);
    Precuencias segundaSecuencia(secuencia2);
    cout << endl << segundaSecuencia;

    if (primeraSecuencia == segundaSecuencia) cout << "\nLas secuencias son iguales\n\n";
    if (primeraSecuencia != segundaSecuencia) cout << "\nLas secuencias no coinciden\n\n";
}