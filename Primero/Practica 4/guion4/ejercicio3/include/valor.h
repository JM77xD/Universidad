#ifndef valor_h
#define valor_h

#include <iostream>

class Valor {
    private:
        int fila;           //Numero de fila, columna y el valor numérico que toma el valor significativo
        int columna;
        double valor;

    public:
        Valor();

        Valor(int vFila, int vColumna, double vValor);

        Valor(const Valor &copiar);

        void asignar(int vFila, int vColumna, double vValor);

        inline int devolverFila() {         //Funciones para devolver los valores de filas, columnas y el valor
            return this->fila;
        }

        inline int devolverColumna() {
            return this->columna;
        }

        inline double devolverValor() {
            return this->valor;
        }

        Valor operator=(const Valor &otro);
};

#endif