#include <iostream>
#include "utilidades.h"

using namespace std;

int main() {
    const int TAM_MAX = 100;
    int numeroDescomponer, divisores[TAM_MAX], numeroDivisores;
    cout << "Que numero desea descomponer? ";       //Leemos el numero a descomponer
    cin >> numeroDescomponer;
    descomponer(numeroDescomponer, divisores, numeroDivisores);     //Lo descomponemos
    if (numeroDivisores == 1) {     //Si el numero de factores es 1, significa que el numero es primo
        cout << "\nEl numero " << numeroDescomponer << " es primo\nSu único factor es: " << numeroDescomponer;
    } else {        //Si tiene mas factores, anunciamos los factores y el numero de ellos
        cout << "\nDescomposición del numero no primo: " << numeroDescomponer << "\nNumero de factores: " << numeroDivisores << endl;
        for (int i = 0; i < numeroDivisores; i++) cout << divisores[i] << " ";
        cout << endl;
    }
}