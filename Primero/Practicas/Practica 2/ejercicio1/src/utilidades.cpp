#include "utilidades.h"

int mezclar(double Array1[], double Array2[], int tamanioA1, int tamanioA2, double ArrayResultado[]) {
    int contadorA1 = 0, contadorA2 = 0, tamanioResultado = tamanioA1 + tamanioA2, contadorResultado = 0;
    for (int i = 0; i < tamanioA1; i++) {           //Si hay algún numero repetido, el tamaño del array resultante se reduce en 1, puesto que tendremos que eliminar ese numero
        for (int j = 0; j < tamanioA2; j++) {
            if (Array1[i] == Array2[j]) {
                tamanioResultado -= 1;
            }
        }
    }
    while (contadorResultado != tamanioResultado) {
        if (Array1[contadorA1] != Array2[contadorA2]) {     //En el caso de que haya 2 numeros iguales, se descarta uno
            if (Array1[contadorA1] <= Array2[contadorA2] && contadorA1 < tamanioA1) {       //Si el numero de array1 es menor que el de array2, colocamos ese
                ArrayResultado[contadorResultado] = Array1[contadorA1];
                contadorA1++;
                contadorResultado++;
            } else if (Array2[contadorA2] < Array1[contadorA1] && contadorA2 < tamanioA2) {     //Si el del array2 es menor que el del array1, colocamos ese
                ArrayResultado[contadorResultado] = Array2[contadorA2];
                contadorA2++;
                contadorResultado++;
            } else if (contadorA2 == tamanioA2) {               //Si el array2 ha sido recorrido y no se cumple ninguna condicion anterior, imprimimos el array1
                ArrayResultado[contadorResultado] = Array1[contadorA1];
                contadorA1++;
                contadorResultado++;
            } else {            //Si el array1 ha sido recorrido y no se cumple ninguna condicion anterior, terminamos de imprimir el array2
                ArrayResultado[contadorResultado] = Array2[contadorA2];
                contadorA2++;
                contadorResultado++;
            } 
        } else {
            if (contadorA2 != tamanioA2 - 1) {      //Si son iguales y podemos descartar el numero del array2, descartamos ese, si no, descartamos el del array1
                contadorA2++;
            } else {
                contadorA1++;
            }
        }
    }
    return tamanioResultado;        //Devolvemos el tamaño del array resultante
}
