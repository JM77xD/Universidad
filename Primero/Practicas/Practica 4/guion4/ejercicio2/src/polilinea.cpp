#include <iostream>
#include "punto.h"
#include "polilinea.h"

using namespace std;

void Polilinea::agregarPunto(int x, int y) {
    Punto *aux = p;         //Creamos un puntero auxiliar que apunta al array
    p = new Punto[num+1];   //Declaramos un nuevo array con el tamaño correcto y hacemos que p apunte a ese array
    for (int i = 0; i < num; i++) (p+i)->cambiarValores((aux+i)->devolverX(), (aux+i)->devolverY());    //Asignamos los valores que teníamos antes
    (p+num)->cambiarValores(x, y);      //Insertamos el nuevo punto
    num++;  //Aumentamos el numero de puntos
    delete [] aux;      //Borramos el array antiguo
};


void Polilinea::inicializarPolilinea() {
    cout << "\nCuantos puntos desea introducir? ";      //Preguntamos el número de puntos
    int puntos;
    cin >> puntos;
    for (int i = 0; i < puntos; i++) {      //Introducimos el número de puntos solicitado
        cout << "\nIntroduzca el punto " << i+1 << ":";
        cout << "\nx: ";
        int coordX;
        cin >> coordX;
        cout << "y: ";
        int coordY;
        cin >> coordY;
        this->agregarPunto(coordX, coordY);     //Vamos añadiendo uno a uno
    }
};


Polilinea Polilinea::operator+(const Polilinea &sumar) const {       //Sobrecarga de la suma
    Polilinea copia(sumar);     //Creamos una copia de la 2a polilinea
    bool coincide;
    for (int i = 0; i < this->num; i++) {
        coincide = false;
        for (int j = 0; j < sumar.num; j++) if (this->p[i].devolverX() == sumar.p[j].devolverX() && this->p[i].devolverY() == sumar.p[j].devolverY()) coincide = true;
        if (!coincide) copia.agregarPunto(this->p[i].devolverX(), this->p[i].devolverY());     //Agregamos los valores de la primera
    }
    return copia;   //Devolvemos la nueva polilinea
};


Polilinea::Polilinea(const Polilinea &otra){       //Constructor de copia
    this->num = otra.num;       //Igualamos el tamaño de los array
    this->p = new Punto[num];   //Creamos un nuevo array
    for (int i = 0; i < num; i++) this->p[i].cambiarValores(otra.p[i].devolverX(), otra.p[i].devolverY());  //Copiamos los valores del array a copiar
};


Polilinea::~Polilinea() {          //Destructor
    if (this->p) {          //Si p no es nulo
        delete [] p;        //Borramos el array
    }
}


Polilinea::Polilinea() {           //Constructor por defecto
    p=0;        //Apunta a null
    num = 0;    //No hay puntos
}