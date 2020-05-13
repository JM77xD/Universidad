#include <iostream>
#include "utilidades.h"

using namespace std;

void mostrarArray(int const array[], int const util) {              //funcion para mostrar el array de enteros
    cout << "\nEl array es: ";
    for (int i = 0; i < util; i++) cout << array[i] << " ";
    cout << endl;
}

void mostrarArrayPtr(int **array,int const util) {              //funcion para mostrar el array de punteros
    cout << "\nEl array de punteros es: ";
    for (int i = 0; i < util; i++) cout << **(array + i) << " ";
    cout << endl;
}

void ordenarPunteros(int *array, int const util, int **resultado){
    for (int i = 0; i < util; i++) *(resultado+i) = (array+i);            //asignamos los punteros al array   
    for (int i = 0; i < util - 1; i++) {            //Utilizamos cualquier algoritmo para ordenar el array de punteros (el de burbuja en este caso)
        for (int j = 0; j < util - 1; j++) {
            if (**(resultado+j) > **(resultado+j+1)) {          //Comparamos los valores
                int *aux;                   //Intercambiamos los punteros de esos valores
                aux = *(resultado+j);
                *(resultado+j)= *(resultado+j+1);
                *(resultado+j+1) = aux;
            }
        }
    }
}