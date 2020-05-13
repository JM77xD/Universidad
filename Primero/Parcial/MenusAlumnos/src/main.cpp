#include <iostream>
#include <cstring>
#include "menu.h"
using namespace std;


int main(){

    Menu m;
    // Prueba de los distintos métodos
    m.setTitulo("Insertar Cliente");
    m.agregarOpcion("1. Seleccionar");
    m.agregarOpcion("2. Ajustar");
    m.agregarOpcion("3. Calcular");

    cout << m;

    //Prueba constructor por argumentos
    Menu m3 ( "Insertar Empresa", "1. Opcion" );
    cout << m3;

    //Prueba constructor de copia
    Menu m2(m);
    m2.agregarOpcion("4.Nueva opcion");
    
    cout << m2;

}