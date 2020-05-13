#include <iostream>
#include "fila.h"
#include "columnas.h"

using namespace std;

        void Fila::mostrar() {
            Columnas *p = this->columna;        //Creamos el puntero auxiliar
            while (p != 0) {                    //Hasta que el valor del puntero no sea nulo
                cout << p->numero << "\t";      //Vamos nombrando los valores de la matriz
                p = p->sigC;                    //Avanzamos de columna
            }
            cout << endl;
            p = 0;
            delete p;                           //Borramos el puntero auxiliar
        }

        void Fila::copiarColumnas(Fila *original) {
            Columnas *auxOriginal = original->devolverColumna();      //Creamos un puntero auxiliar para la fila de la que queremos la copia
            Columnas *p = this->columna;                            //Puntero auxiliar para la fila sobre la que copiamos los datos
            while (auxOriginal != 0) {                              //Hasta que no terminemos de copiar, se ejecuta el bucle
                p->numero = auxOriginal->numero;                    //Copiamos el valor de la columna
                p = p->sigC;                                        //avanzamos a la siguiente columna
                auxOriginal = auxOriginal->sigC;
            }
            p = 0;
            auxOriginal = 0;
            delete p;                                               //Borramos los punteros auxiliares
            delete auxOriginal;
        }

        void Fila::subColumnas(Fila *original, int ColInicio, int tamanio) {
            Columnas *auxOriginal = original->devolverColumna();
            Columnas *p = this->columna;
            for (int i = 0; i < ColInicio ; i++) {             //Usamos un for para llegar a la columna de inicio de copia
                auxOriginal = auxOriginal->sigC;                //Vamos avanzando por las columnas
            }
            for (int i = 0; i <= tamanio; i++) {                            //No paramos hasta llenar la submatriz
                p->numero = auxOriginal->numero;        //Copiamos el valor de la columna original a la copia
                p = p->sigC;                            //Avanzamos por las columnas
                auxOriginal = auxOriginal->sigC;
            }
            p = 0;
            auxOriginal = 0;
            delete p;                                   //Borramos punteros auxiliares
            delete auxOriginal;
        }

        void Fila::borrarColumna(int columna) {
            Columnas *auxiliar = this->columna;                             //Creamos puntero auxiliar
            for (int i = 0; i < columna - 1; i++) auxiliar = auxiliar->sigC;    //Vamos a la columna anterior a la queremos borrar
            Columnas *p = auxiliar->sigC->sigC;                             //Guardamos la direccion de la columna siguiente a la que queremos borrar
            delete auxiliar->sigC;                                          //Borramos la columna en cuestión
            auxiliar->sigC = p;                                             //Sustituimos la columna que hemos borrado por su siguiente
            auxiliar = 0;
            p = 0;
            delete p;                                                       //Borramos punteros auxiliares
            delete auxiliar;
        }