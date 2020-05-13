#include <iostream>
#include "celda.h"
#include "lista.h"

using namespace std;

int main(){
    double numeros[] = {1,2,3,4,5,6,7,8,9,10};          //Inicializamos los valores y la lista
    Lista original(10, numeros);

    cout << "Lista inicial:\n";             //Mostramos la lista inicial y su longitud
    original.mostrarLista();
    cout << "\nLongitud: " << original.obtenerLongitud();

    for (int i = 0; i < 3; i++) original.eliminarFinal();       //Borramos las 3 últimas celdas
    cout << "\nLista inicial sin las 3 últimas celdas:\n";        //Mostramos la lista sin las 3 últimas celdas y su longitud
    original.mostrarLista();
    cout << "\nLongitud: " << original.obtenerLongitud();

    original.agregarInicio(0);          //Insertamos 0 al inicio
    cout << "\nLista anterior añadiendo un 0 a la posición inicial:\n";       //Mostramos la lista y su longitud
    original.mostrarLista();
    cout << "\nLongitud: " << original.obtenerLongitud();

    cout << "\nLa lista inversa es:\n";
    original.mostrarInverso();

    int ultimaPos = original.obtenerLongitud() - 1;         //Obtenemos la última posicion
    Celda *primero = original.obtenerCelda(0);  //puntero al primer elemento
    Celda *ultima = original.obtenerCelda(ultimaPos);   //puntero al ultimo elemento
    Celda *tercera = original.obtenerCelda(3);      //puntero al tercer elemento

    cout << "\nElemento en posicion 3: ";           //enunciamos los distintos valores
    tercera->mostrar();

    cout << "\nElemento en primera posicion: ";
    primero->mostrar();

    cout << "\nElemento en última posicion: ";
    ultima->mostrar();

    cout << endl;

    original.liberarEspacio();          //Liberamos el espacio
}