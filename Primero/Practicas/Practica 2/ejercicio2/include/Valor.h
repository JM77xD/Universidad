
#ifndef VALOR_H
#define VALOR_H

#include <iostream>

using namespace std;

class Valor{
  private:
    int fila;
    int columna;
    double valor;

  public:
    /**
     * Constructor por defecto
     */
    Valor(){
        fila = 0;
        columna = 0;
        valor = 0;
    }

    /**
     * Constructor de la clase
     * @param fila
     * @param columna
     * @param valor
     */
    Valor(int numeroF, int numeroC, double numeroV){
        fila = numeroF;
        columna = numeroC;
        valor = numeroV;
    }

    /**
     * Metodo paa mostrar el contenido de un objeto
     */
    void mostrar(){
        cout << "Fila: " << fila << "\nColumna: " << columna << "\nValor: " << valor << endl << endl;
    }

    int valorFila() {
        return fila;
    }

    int ValorColumna() {
        return columna;
    }

    double ValorValor() {
        return valor;
    }

    void insertar(int newF, int newC, double newValue);
};
#endif //VALOR_H
