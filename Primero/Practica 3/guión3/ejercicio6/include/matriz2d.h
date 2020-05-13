#ifndef matriz2d_h
#define matriz2d_h

#include "fila.h"



class Matriz2D {
    private:
        Fila *matriz;
        int numFilas,numColumnas;                               //Llevamos el conteo de filas y columnas para que sea más fácil realizar las operaciones
    public:
        Matriz2D(int filas = 0, int columnas = 0) {
            numFilas = filas;
            numColumnas = columnas;
            this->matriz = new Fila(columnas);              //Crea una sola fila con el numero de columnas especificado
            Fila *p = this->matriz;
            for (int i = 1; i <= filas; i++) {
            p->sigF = new Fila(columnas);
            p = p->sigF;
            }
            p->sigF = 0;
            p = 0;
            delete p;                                       //Borra el puntero auxiliar                           
        }

        void mostrar();

        Fila *devolverFila() {                            //Devuelve el puntero fila de la matriz
            return matriz;
        }

        Matriz2D *copiarMatriz();

        Matriz2D *extraerSubmatriz(int filaInicio, int filaFinal, int columnaInicio, int columnaFinal);

        void eliminarFila(int fila);

        void eliminarColumna(int columna);

};

#endif