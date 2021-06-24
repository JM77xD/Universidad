#ifndef fila_h
#define fila_h

#include "columnas.h"

class Fila{
    private:
        Columnas *columna;
    public:
        Fila *sigF;                             //Puntero que apunta a la siguiente fila


        Fila(int numero){
            this->columna = new Columnas;       //Crea una sola columna, si el numero es mayor que 1, entonces se crean más
            Columnas *p = this->columna;
            p->numero = 0;
            for (int i = 1; i <= numero; i++) {
                p->sigC = new Columnas;
                p = p->sigC;
                p->numero = i;
            }
            p->sigC = 0;                        //La siguiente columna se inicializa a 0
            p = 0;
            delete p;                           //Borra el puntero auxiliar
        }

        void mostrar();

        Columnas *devolverColumna() {           //Devuelve el puntero columna de la fila
            return columna;
        }

        void copiarColumnas(Fila *original);

        void subColumnas(Fila *original, int ColInicio, int tamanio);

        void borrarColumna(int columna);

};

#endif