#include <iostream>
#include <string>
#include "bigint.h"
#include "utilidades.h"

using namespace std;

int main() {
    BigInt numeroGrande1, numeroGrande2;
    cout << "Numero 1\n";
    numeroGrande1.agregarValores();
    cout << "\nEl numero 1 es: " << numeroGrande1 << "\n\nNumero 2\n";
    numeroGrande2.agregarValores();
    BigInt numeroSuma(numeroGrande2 + numeroGrande1);
    cout << "\nEl numero 2 es : " << numeroGrande2  << "\n\nLa suma de ambos es: " << numeroSuma << endl; 
}