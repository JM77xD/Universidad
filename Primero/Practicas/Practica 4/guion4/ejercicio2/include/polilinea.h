#ifndef polilinea_h
#define polilinea_h

#include <iostream>
#include "punto.h"

using namespace std;

class Polilinea {
    private:
        Punto *p;   //Array de puntos

        int num;    //Numero de puntos en el array

        friend ostream& operator<<(ostream &o, const Polilinea &mostrar);
    public:
        Polilinea();

        ~Polilinea();

        Polilinea(const Polilinea &otra);

        void inicializarPolilinea();

        void agregarPunto(int x, int y);

        Polilinea operator+(const Polilinea &sumar) const;
};

#endif