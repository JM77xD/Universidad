#include <iostream>
#include "Valor.h"

using namespace std;

void Valor::insertar(int newF, int newC, double newValue) {             //Cambiamos el valor de uno de los elementos
        fila = newF;
        columna = newC;
        valor = newValue;
}