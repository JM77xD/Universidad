#include <iostream>
#include "Valor.h"
#include "utilidades.h"

using namespace std;

int main() {
    Valor array1[] = { Valor (1 , 1 , 0.7) , Valor (1 , 3 , 9.4) , Valor (2 , 1 , 8.3) , Valor (3 , 1 , 6.45) , Valor (3 , 3 , 2.75) };     //Declaramos los arrays
    Valor array2[] = { Valor (0 , 0 , 10) , Valor (1 , 1 , 0.3) , Valor (1 , 2 , 4.3) , Valor (2 , 2 , 1.5) , Valor (3 , 2 , 0.25) };
    const int TAM_MAX = 100;
    Valor Suma[TAM_MAX];            //Declaramos el array suma
    int tamanio1 = sizeof(array1)/sizeof(*array1);      //Declaramos los tamaños de cada array
    int tamanio2 = sizeof(array2)/sizeof(*array2);
    int tamanioTotal = 0;
    combinarSuma(array1, array2, tamanio1, tamanio2, Suma, tamanioTotal);
    for (int i = 0; i < tamanioTotal; i++){
        Suma[i].mostrar();          //Mostramos los elementos de la suma de ambos arrays
    }
}