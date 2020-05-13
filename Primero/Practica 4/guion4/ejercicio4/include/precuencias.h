#ifndef precuencias_h
#define precuencias_h

#include <string>
#include <iostream>
#include "pareja.h"

using namespace std;

class Precuencias {
    private:
        Pareja *parejas;

        int nParejas;

        friend ostream & operator<<(ostream &o, const Precuencias &mostrar);
    public:
        Precuencias();

        Precuencias(string secuencia);

        ~Precuencias();

        Precuencias(const Precuencias &copiar);

        void crearPareja(int numeroEntero);

        void agregarValor(int numero);

        bool operator==(const Precuencias &otra) const;

        bool operator!=(const Precuencias &otra);
};

#endif