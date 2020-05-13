#include "utilidades.h"

void Creciente(int cadena1[], int cadena_crece[], int &utilizados) {
    int longitud_creciente = 0, longitud_cadena, posicion, contador;
    for (int i = 0; i + 1 < utilizados; i++) {
        if (cadena1[i] < cadena1[i+1]) {        //si un elemento es menor que su siguiente, iniciamos el bucle
            contador = i;       //Guardamos la posicion del inicio de la cadena de crecientes y la longitud de la misma
            longitud_cadena = 0;
            while (cadena1[contador] < cadena1[contador+1] && contador+1 < utilizados) {        //Mientras que sea creciente y no lleguemos al final del array de enteros, hacemos el bucle
                contador++;         //Sumamos al contador y la longitud de la cadena
                longitud_cadena++;
            }
            if (longitud_cadena > longitud_creciente) {     //Si la longitud de la cadena es mayor que la anterior
                longitud_creciente = longitud_cadena;       //Guardamos la nueva longitud
                posicion = i;                               //Guardamos la posicion de inicio
            }
            i = contador;                                   //Nos saltamos los elementos que ya hemos visto para que no se vuelva a ejecutar el for en esos elementos
        }
    }
    utilizados = longitud_creciente;                        //Devolvemos la longitud de la cadena creciente en el argumento proporcionado por el usuario
    for (int i = 0; i <= utilizados; i++) {
        cadena_crece[i] = cadena1[posicion];                //Asignamos los valores de la cadena creciente mediante un bucle for
        posicion++;
    }
}
