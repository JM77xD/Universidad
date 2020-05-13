#include "utilidades.h"
#include <iostream>

using namespace std;

int main() {
    int tam1, tam2;

    cout << "Introduzca el tamaño del array 1: ";
    cin >> tam1;
    double *array1 = new double[tam1];                      //Declaramos y damos valor al array1
    cout << "Introduzca los elementos del array: ";
    for (int i = 0; i < tam1; i++) cin >> *(array1 + i);
    orden(array1, tam1);                                    //Ordenamos el array1
    mostrar(array1, tam1);                                  //Mostramos el array ordenado por pantalla

    cout << "\nIntroduzca el tamaño del array 2: ";
    cin >> tam2;
    double *array2 = new double[tam2];                      //Declaramos y damos valor al array2
    cout << "Introduzca los elementos del array: ";
    for (int i = 0; i < tam2; i++) cin >> *(array2 + i);
    orden(array2, tam2);                                    //Ordenamos el array2
    mostrar(array2, tam2);                                  //Mostramos el arrray ordenado por pantalla

    int tamMezcla = calcularTamRes(array1, tam1, array2, tam2);
    double *arrayMezcla = new double[tamMezcla];
    cout << "\nEl tamaño resultante de la mezcla es: " << tamMezcla << endl;
    mostrar(arrayMezcla, mezclarUnico(array1, tam1, array2, tam2, arrayMezcla, tamMezcla));

    cout << endl;

    delete [] array1;
    delete [] array2;
    delete [] arrayMezcla;
}