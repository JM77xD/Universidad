#include <iostream>
#include "matriz2d.h"
#include "fila.h"
#include "columnas.h"

using namespace std;

void Matriz2D::mostrar() {
            Fila *aux = this->matriz;                           //Creamos un puntero auxiliar
            while (aux != 0) {                                  //Hasta que no sea nulo
                aux->mostrar();                                 //Mostramos el contenido de las columnas
                aux = aux->sigF;                                //Avanzamos a la siguiente fila
            }
            aux = 0;
            delete aux;                                         //Borramos el puntero auxiliar
        }

Matriz2D *Matriz2D::copiarMatriz() {
            Matriz2D *copia = new Matriz2D(numFilas, numColumnas);          //Crea una nueva matriz en memoria dinámica
            Fila *p = copia->devolverFila();                                 //Puntero auxiliar para movernos por la matriz copia
            Fila *aux = this->matriz;                                       //Puntero auxiliar para movernos por la matriz a copiar
            for (int i = 0; i <= numFilas; i++) {                           //Copiamos fila a fila de la matriz original
                p->copiarColumnas(aux);
                p = p->sigF;                                                //Avanzamos a la siguiente fila en cada ejecución
                aux = aux->sigF;
            }
            p = 0;
            aux = 0;
            delete p;                                                       //Borramos punteros auxiliares
            delete aux;
            return copia;                                                   //Devolvemos el puntero a la matriz copiada
        }

Matriz2D *Matriz2D::extraerSubmatriz(int filaInicio, int filaFinal, int columnaInicio, int columnaFinal) {
            int tamanioFilas = filaFinal - filaInicio, tamanioColumnas = columnaFinal - columnaInicio;//Calculamos el numero de filas y columnas que tendrá la matriz
            Matriz2D *copia = new Matriz2D(tamanioFilas, tamanioColumnas);          //Creamos una copia de la matriz
            Fila *p = copia->devolverFila();                                          //Puntero auxiliar
            Fila *aux = this->matriz;
            for (int i = 0; i <filaInicio; i++) aux = aux->sigF;                   //Avanzamos en la matriz original hasta la fila de inicio
            for (int i = 0; i <= tamanioFilas; i++) {                                                        //No paramos hasta rellenar la matriz
                p->subColumnas(aux, columnaInicio, tamanioColumnas);                              //Copiamos las columnas
                p = p->sigF;                                                        //avanzamos en las filas
                aux = aux->sigF;
            }
            aux = 0;
            p = 0;
            delete aux;                                                             //Borramos punteros auxiliares
            delete p;
            return copia;                                                           //Devolvemos la submatriz
        }

void Matriz2D::eliminarFila(int fila) {
            Fila *aux = this->matriz;                                               //Creamos un puntero auxiliar
            for (int i = 0; i < fila; i++) aux = aux->sigF;                         //Vamos hasta la fila anterior de la que queremos borrar
            Fila *p = aux->sigF->sigF;                                              //Copiamos la direccion de la fila siguiente a la que queremos borrar
            delete aux->sigF;                                                       //Borramos la fila
            aux->sigF = p;                                                          //Sustituimos la fila que queríamos borrar por la siguiente a esa
            p = 0;
            aux = 0;
            delete aux;                                                             //Borramos punteros auxiliares
            delete p;
            numFilas--;                                                             //Reducimos en 1 el numero de filas
        };

void Matriz2D::eliminarColumna(int columna) {
            Fila *aux = this->matriz;                                               //Creamos puntero auxiliar
            for (int i = 0; i <= numFilas; i++) {                                   //Vamos recorriendo fila a fila
                aux->borrarColumna(columna);                                        //Borramos la columna de cada fila
                aux = aux->sigF;
            }
            numColumnas--;                                                          //Reducimos en 1 el numero de columnas
            aux = 0;
            delete aux;
        }