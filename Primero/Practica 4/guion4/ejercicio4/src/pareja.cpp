#include "pareja.h"


Pareja::Pareja() {
    dato = -1;  //Incluimos que el dato por defecto sea -1 ya que no vamos a trabajar con datos negativos
    nVeces = 0;
}

Pareja::Pareja(int dato, int veces) {
    this->dato = dato;
    this->nVeces = veces;
}

Pareja Pareja::operator=(const Pareja &igualar) {       //Sobrecarga del operador "="
    this->dato = igualar.dato;      //Igualamos los valores de "this" a la que queremos igualar
    this->nVeces = igualar.nVeces;
}

void Pareja::crear(int dato) {
    this->dato = dato;
    nVeces = 1;
}

bool Pareja::operator==(const Pareja &otra) {       //Sobrecarga del operador "=="
    if (this->dato == otra.dato && this->nVeces == otra.nVeces) {   //Si los datos y el número de veces que aparece ese dato coinciden, las 2 parejas son iguales
        return true;
    } else return false;
}