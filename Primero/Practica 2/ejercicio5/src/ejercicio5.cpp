#include <iostream>
#include "utilidades.h"

using namespace std;

int main() {
    char base[] = "cadena base para prueba de insercion";           //Declaramos la cadena base y la cadena a insertar
    char aInsertar[] = "-agregado-";
    const int TAM_MAX = 1000;
    char Insertada[TAM_MAX];                                        //Declaramos la cadena en la que vamos a realizar la inserción
    int insertarEn = 0;                                             //Declaramos la posicion en la que queremos insertar la cadena
    int Tamaniobase = sizeof(base)/sizeof(*base) - 1, TamanioInsertar = sizeof(aInsertar)/sizeof(*aInsertar) - 1;       //Restamos 1 a los tamaños para eliminar el elemento \0
    if (InsertarCadena(base, aInsertar, Tamaniobase, TamanioInsertar, insertarEn, Insertada)) {     //Si podemos realizar la insercion, enunciamos la cadena insertada
        cout << "Inserción en la posicion: " << insertarEn << "\nInserción posible: 1\n";
        for (int i = 0; i < TamanioInsertar + Tamaniobase; i++) cout << Insertada[i];    
    } else {                                                                                        //Si no podemos realizar la inserción, decimos el error
        cout << "Inserción en la posición inválida: " << insertarEn << "\nInseción posible: 0\n";
    }
}