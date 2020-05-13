#ifndef matrizdispersa_h
#define matrizdispersa_h

#include <iostream>
#include "valor.h"

using namespace std;

class MatrizDispersa {
    private:
        int nfilas;     //Numero de filas y columnas de la matriz
        int ncolumnas;
        Valor *valor;       //Array de valores significativos
        int nValores;       //Numero de valores significativos
        friend ostream& operator<<(ostream &o, const MatrizDispersa &mostrar);
    public:
        MatrizDispersa();

        ~MatrizDispersa();

        MatrizDispersa(int filas[], int columnas[], double valores[], int numValores);

        MatrizDispersa(const MatrizDispersa &copiar);

        void inicializarMatriz();           //Método para incializar la matriz dispersa

        MatrizDispersa operator+(const MatrizDispersa &otra) const;     //Sobrecarga de la suma
};

#endif