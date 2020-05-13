#include <iostream>
#include "valor.h"

Valor::Valor(){            //Constructor por defecto, inicializa todos los valores a 0
    fila = 0;
    columna = 0;
    valor = 0;
}

Valor::Valor(int vFila, int vColumna, double vValor) {     //Constructor que permite inicializar los valores a aquellos proporcionados por el usuario
    fila = vFila;
    columna = vColumna;
    valor = vValor;
}

Valor::Valor(const Valor &copiar) {        //Constructor de copia de la clase valor
    this->fila = copiar.fila;
    this->columna = copiar.columna;
    this->valor = copiar.valor;
}

void Valor::asignar(int vFila, int vColumna, double vValor) {      //Permite cambiar los valores de las variables de la clase
    fila = vFila;
    columna = vColumna;
    valor = vValor;
}

Valor Valor::operator=(const Valor &otro) {        //Sobrecarga del operador "=" para simplificar la tarea de igualar 2 valores
    if (this != &otro) {    //Si no estamos igualando el mismo objeto
        this->fila = otro.fila;
        this->columna = otro.columna;
        this->valor = otro.valor;
    }
    return *this;
}