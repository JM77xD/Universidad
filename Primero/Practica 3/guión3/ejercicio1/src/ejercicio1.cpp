#include <iostream>
#include <ctime>
#include <cstdlib>
#include "utilidades.h"

using namespace std;


int main() {
    int tamanio, opcion;
    cout << "Cuantos números desea incluir en el array? ";
    cin >> tamanio;                 //Preguntamos el tamaño del array de enteros
    int arrayEnt[tamanio];          //Declaración del array de enteros
    cout << "\nDesea que los numeros sean aleatorios (1 para si, 0 para no)? ";
    cin >> opcion;
    if (opcion == 1) {
        srand(time(0));
        for (int i = 0; i < tamanio; i++) arrayEnt[i] = -100 + rand() % (101 - (-100));         //Generación de valores aleatorios entre -100 y 100 para el array  
    } else if (opcion == 0) {
        cout << "\nIntroduzca los numeros: ";
        for (int i = 0; i < tamanio; i++) {                     //leemos los números metidos por el usuario
            cin >> arrayEnt[i];
        }
    } else {
        cout << "\nOpcion no válida";                           //Salimos del programa
        return 0;
    }
    int **arrayPtr = new int *[tamanio];         //Creacion del array de punteros
    ordenarPunteros(arrayEnt, tamanio, arrayPtr);       //Ejecutamos el método
    mostrarArray(arrayEnt, tamanio);        //Mostramos el array de enteros
    mostrarArrayPtr(arrayPtr, tamanio);     //Mostramos el array de punteros
    delete [] arrayPtr;                     //Liberamos el espacio
}