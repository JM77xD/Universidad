#ifndef punto_h
#define punto_h

#include <iostream>

using namespace std;

class Punto {
    int x, y;       //Coordenadas

    public:

        Punto();

        void cambiarValores(int nx, int ny);

        inline int devolverX() const {
            return x;
        }

        inline int devolverY() const {
            return y;
        }
};

#endif