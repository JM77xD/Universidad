#include <iostream>
#include "celda.h"
#include "lista.h"

using namespace std;

        void Lista::mostrarLista() {
            static int vecesLlamada = 0;
            if (vecesLlamada < this->obtenerLongitud()) {
                Celda *p = this->contenido;
                for (int i = 0; i < vecesLlamada; i++) p = p->SiguienteCelda();
                vecesLlamada++;
                p->mostrar();
                return mostrarLista();
            } else vecesLlamada = 0;
        }

        void Lista::mostrarInverso() {
            static int llamadaInverso = this->obtenerLongitud() - 1;
            if (llamadaInverso >= 0) {
                Celda *p = this->contenido;
                for (int i = 0; i < llamadaInverso; i++) p = p->SiguienteCelda();
                p->mostrar();
                llamadaInverso--;
                return mostrarInverso();
            } else llamadaInverso = this->obtenerLongitud() - 1;
        }

        int Lista::obtenerLongitud() {
            if (this->contenido) {          //Si tenemos celdas
                int longitud = 0;
                Celda *p = this->contenido;     //Puntero auxiliar
                while (p != 0) {                //Hasta que no sea nulo
                    longitud++;                 //Aumentamos el numero de celdas
                    p = p->SiguienteCelda();    //Avanzamos a la siguiente
                }
                p = 0;                      //Borramos puntero auxiliar
                delete p;
                return longitud;            //Devolvemos la longitud
            } else {            //Si no hay celdas, la lista está vacía
                cout << "\nLista vacía";
                return 0;
            }
        }

        void Lista::eliminarFinal() {
            if (this->contenido) {          //Si hay celdas
                Celda *p = this->contenido;     //Creamos puntero auxiliar
                while (p->SiguienteCelda()->SiguienteCelda() != 0) p = p->SiguienteCelda();     //Vamos avanzando hasta llegar hasta la penúltima celda
                delete p->SiguienteCelda();     //Borramos la última celda
                p->cambiarSiguiente(0);     //Establecemos el valor de siguiente a nulo
                p = 0;      //Borramos puntero auxiliar
                delete p; 
            }
        }

        void Lista::agregarFinal(double valor) {
            if (this->contenido) {      //Si tenemos celdas
                Celda *p = this->contenido;     //Puntero auxiliar
                while (p->SiguienteCelda() != 0) p = p->SiguienteCelda();      //Hasta que la siguiente celda no sea nula, avanzamos por las celdas
                p->crearCelda();            //Creamos una nueva celda
                p = p->SiguienteCelda();    //Vamos a ella
                p->insertarValor(valor);    //Insertamos el valor
                p = 0;      //Borramos el puntero auxiliar
                delete p;
            } else {        //Si no hay celdas
                this->contenido = new Celda;        //Creamos una
                this->contenido->insertarValor(valor);  //Insertamos el valor
            }
        }

        void Lista::agregarInicio(double valor) {
            if (this->contenido) {      //Si tenemos celdas
                Celda *p = this->contenido;     //Puntero auxiliar a la primera celda
                this->contenido = new Celda;    //Creamos una celda nueva en el primer lugar
                this->contenido->insertarValor(valor);  //Le insertamos el valor
                this->contenido->cambiarSiguiente(p);   //Establecemos la siguiente a la nueva como la que era anteriormente la primera
                p = 0;      //Borramos puntero auxiliar
                delete p;
            } else {        //Si no hay celdas
                this->contenido = new Celda;        //Creamos una
                this->contenido->insertarValor(valor);      //Insertamos el valor
            }
        }

        Celda *Lista::obtenerCelda(int posicion) {
            if (posicion < this->obtenerLongitud() && posicion >= 0) {       //Si la posición es menor que la longitud de la lista
                Celda *p = this->contenido;     //Puntero auxiliar
                for (int i = 0; i < posicion; i++) p = p->SiguienteCelda();     //Avanzamos hasta llegar a la celda
                return p;   //Devolvemos el puntero
            } else {        //Si la posición es mayor que la lista o negativa
                cout << "\nPosicion no válida\n";
                return 0;
            }
        }

        void Lista::agregarPosicion(int posicion, double valor) {
            if (posicion < this->obtenerLongitud() && posicion >= 0) {      //Si la posicion es válida
                Celda *p = this->contenido;     //Puntero auxiliar
                for (int i = 0; i < posicion; i++) p = p->SiguienteCelda();     //Avanzamos hasta llegar a la celda
                Celda *temporal = p;                //Guardamos la posicion
                p = new Celda;      //Creamos una nueva en su lugar
                p->insertarValor(valor);        //Insertamos el valor
                p->cambiarSiguiente(temporal);      //Sustituimos la siguiente
                p = 0;          //Borramos punteros auxiliares
                temporal = 0;
                delete p;
                delete temporal;
            } else {       //Si la posición no es válida
                cout <<"\nPosicion no válida\n";
            }
        }

        void Lista::liberarEspacio() {
            if (this->contenido) {      //Si existe la lista
                while (this->contenido->SiguienteCelda() != 0) {        //Hasta que la siguiente a la primera no sea nula
                    this->eliminarFinal();
                }
                delete this->contenido;     //Borramos la última celda que queda
                this->contenido = 0;        //Inicializamos contenido como nulo
            } else cout << "\nLa lista estaba vacía\n";     //Si la lista está vacía, lo enunciamos
        }