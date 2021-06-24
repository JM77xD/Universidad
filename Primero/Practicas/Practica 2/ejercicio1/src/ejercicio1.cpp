#include <iostream>
#include "utilidades.h"

using namespace std;

int main() {
    double array1[] = {5, 6.3, 7.5, 8.3, 9.2};          //Declaramos los arrays
    double array2[] = {1, 3.4, 6.3};
    const int TAM_MAX = 100;
    double ArrayMezcla[TAM_MAX];
    int tamanioArray1 = sizeof(array1)/sizeof(*array1);     //Declaramos el tamaño de cada array
    int tamanioArray2 = sizeof(array2)/sizeof(*array2);
    for (int i = 0; i < mezclar(array1, array2, tamanioArray1, tamanioArray2, ArrayMezcla); i++) {      //Repetimos el bucle tantas veces como elementos tenga el array resultado
        cout << ArrayMezcla[i] << " ";
    }
    cout << endl;
}
