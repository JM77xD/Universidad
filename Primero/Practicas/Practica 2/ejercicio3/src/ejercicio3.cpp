#include <iostream>
#include "utilidades.h"

using namespace std;

int main() {
    const int TAM_MAX = 100;
    int cadena_ent[TAM_MAX], cadena_creciente[TAM_MAX], utiles = 0, contador = 0, numero;
    cout << "Introduzca los numeros enteros, -1 para parar: ";
    cin >> numero;
    while (numero != -1) {      //Obtenemos la cadena y vamos contando cuantos introducimos, con un -1 para parar
        utiles++;
        cadena_ent[contador] = numero;
        contador++;
        cin >> numero;
    }
    Creciente(cadena_ent,cadena_creciente, utiles);
    cout << "\nEl intervalo monotono creciente más largo es:\n";
    for (int i = 0; i <= utiles; i++) {     //Repetimos el bucle tantas veces como elementos tenga la cadena de crecientes más larga
        cout << cadena_creciente[i] << " ";
    }
    cout << endl;
}