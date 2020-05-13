#include <iostream>
#include "utilidades.h"

using namespace std;


void orden(double *array, int tamanio) {
    for (int i = 0; i < tamanio - 1; i++) {            //Utilizamos cualquier algoritmo para ordenar el array en orden ascendente (el de burbuja en este caso)
        for (int j = 0; j < tamanio - 1; j++) {
            if (*(array+j) > *(array+j+1)) {            //Comparamos los valores
                int aux;                                //Intercambiamos los valores
                aux = *(array+j);
                *(array+j)= *(array+j+1);
                *(array+j+1) = aux;
            }
        }
    }
}

void mostrar(double *array, int tamanio) {      //Implementamos una función para mostrar los arrays
    cout << "El array es: ";
    for (int i = 0; i < tamanio; i++) cout << *(array + i) << " ";
    cout << endl;
}

int calcularTamRes(double *array1, int tamanio1, double *array2, int tamanio2) {            //Funcion para calcular el tamaño que tendrá el array mezcla
    int tamanioFinal = tamanio1 + tamanio2;
    
    for (int i = 0; i < tamanio1; i++) {
        for (int j = 0; j < tamanio2; j++) {
            if (*(array1 + i) == *(array2 + j)) tamanioFinal--;
        }
    }
    return tamanioFinal;
}

int mezclarUnico(double *array1, int tamanio1, double *array2, int tamanio2, double *mezcla, int const tamanioMezcla) {
    int contadorRes = 0, contador1 = 0, contador2 = 0;
    while (contadorRes != tamanioMezcla) {                  //Un bucle que no para hasta que llenemos el array
        if (*(array1 + contador1) == *(array2 + contador2)) {
            if (contador1 < tamanio1) {
                contador1++;
            } else contador2++;
        }
        if (*(array1 + contador1) < *(array2 + contador2) && contador1 < tamanio1) {       //Si el elemento del array1 es menor que el del array2
            *(mezcla + contadorRes) = *(array1 + contador1);                                //Lo insertamos y avanzamos contadores
            contador1++;
            contadorRes++;
        } else if (*(array1 + contador1) > *(array2 + contador2) && contador2 < tamanio2) {        //Si el elemento del array 1 es mayor que el del array2
            *(mezcla + contadorRes) = *(array2 + contador2);                                //Insertamos el del array 2 y avanzamos contadores
            contador2++;
            contadorRes++;
        } else if (contador1 == tamanio1 && contador2 != tamanio2) {                            //Si ya hemos recorrido el array1 y el array2 falta por recorrer
            *(mezcla + contadorRes) = *(array2 + contador2);                            //Insertamos directamente elementos del array2
            contador2++;
            contadorRes++;
        } else if (contador2 == tamanio2 && contador1 != tamanio1) {                            //Si hemos recorrido el array2 y el array1 falta por recorrer
            *(mezcla + contadorRes) = *(array1 + contador1);                            //Insertamos directamente elementos del array1
            contador1++;
            contadorRes++;
        }
    }
    return tamanioMezcla;                   //Devolvemos el tamaño final
}