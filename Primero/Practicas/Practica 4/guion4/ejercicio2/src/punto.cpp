#include <iostream>
#include "punto.h"

using namespace std;

Punto::Punto() {               //Constructor por defecto
    x=0;
    y=0;
};

void Punto::cambiarValores(int nx, int ny) {       //Cambia los valores guardados en x e y
    x = nx;
    y = ny;
};