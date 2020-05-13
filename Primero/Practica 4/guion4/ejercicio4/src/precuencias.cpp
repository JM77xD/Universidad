#include <iostream>
#include <string>
#include "pareja.h"
#include "precuencias.h"

using namespace std;

Precuencias::Precuencias() {
    parejas = 0;
    nParejas = 0;
}

Precuencias::Precuencias(string secuencia) {        //Constructor a partir de un string
    bool coincide;  //Booleano para determinar cuando 2 dígitos son iguales
    this->nParejas = 0; //Establecemos el número de parejas a 0
    for (int i = 0; i < secuencia.length(); i++) {      //Miramos cada dígito de la secuencia
        coincide = false;   //Al comienzo de cada ciclo establecemos que no coincide
        for (int j = 0; j < nParejas; j++) {    //Comprobamos cada pareja existente
            if (secuencia[i]-48 == this->parejas[j].devolverDato()) {   //Si el dato de alguna coincide con el dígito de la secuencia
                this->parejas[j].incrementar(); //Aumentamos el contador del mismo
                coincide = true;    //Establecemos que coincide
            }//--------------------------------------------------Restamos 48 para compensar el valor en ASCII de los dígitos--------------------------------
        }
        if (!coincide) this->crearPareja(secuencia[i]-48);      //Si no coincide, creamos un hueco en el vector
    }
}

Precuencias::~Precuencias() {       //Destructor de la clase
    delete [] this->parejas;
}

Precuencias::Precuencias(const Precuencias &copiar) {       //Constructor de copia
    this->nParejas = copiar.nParejas;   //Igualamos el numero de parejas
    this->parejas = new Pareja[this->nParejas]; //Creamos un array del tamaño adecuado
    for (int i = 0; i < this->nParejas; i++) this->parejas[i] = copiar.parejas[i];      //Vamos copiando las parejas de 1 en 1
}

void Precuencias::crearPareja(int numeroEntero) {       //Método para crear una nueva pareja
    if (parejas) {      //Si existe el array
        Pareja *aux = parejas;  //Creamos un array auxiliar
        this->parejas = new Pareja[nParejas+1]; //Creamos un nuevo array con el tamaño actualizado
        for (int i = 0; i < nParejas; i++) this->parejas[i] = aux[i];  //Copiamos las parejas que teníamos
        this->parejas[nParejas].crear(numeroEntero);       //Añadimos la pareja nueva
        this->nParejas++;       //Incrementamos el número de parejas        
        delete [] aux;  //Borramos el array auxiliar
    } else {        //Si no teníamos parejas
        this->parejas = new Pareja(numeroEntero);   //Creamos una sola pareja con el número en cuestión
        nParejas = 1;   //Establecemos el número de parejas a 1
    }
    
}

void Precuencias::agregarValor(int numero) {    //Método para agregar un valor a una Precuencia
    bool coincide = false;  //Booleano para ver si ya existe una pareja con ese dato
    for (int i = 0; i < this->nParejas; i++) {      //Comprobamos todas las parejas
        if (this->parejas[i].devolverDato() == numero) {    //Si existe, aumentamos el contador y cambiamos el valor del booleano a true
            this->parejas[i].incrementar();
            coincide = true;
        }
    }
    if (!coincide) this->crearPareja(numero);   //Si no existe, la creamos
}

bool Precuencias::operator==(const Precuencias &otra) const {       //Sobrecarga del operador "=="
    int coincidencias = 0;  //Número de coincidencias de parejas
    for (int i = 0; i < this->nParejas; i++) {      //Miramos pareja a pareja
        for (int j = 0; j < otra.nParejas; j++) {
            if(this->parejas[i] == otra.parejas[j]) coincidencias++;    //Si coinciden 2 parejas, aumentamos el número de coincidencias
        }
    }
    if (coincidencias == nParejas && this->nParejas == otra.nParejas) {     //Si el número de coincidencias es igual que el nParejas y ambos tienen el mismo nParejas
        return true;    //Devolvemos que son iguales
    } else return false;    //Si no, devolvemos que son distintas
}

bool Precuencias::operator!=(const Precuencias &otra) {
    bool coincide;          //Booleano para ver si coincide
    for (int i = 0; i < this->nParejas; i++) {      //Recorremos todas las parejas
        coincide = false;
        for (int j = 0; j < otra.nParejas; j++) {
            if (this->parejas[i] == otra.parejas[j]) coincide = true;       //Si alguna de las parejas coincide, cambiamos el valor del booleano
        }
        if (!coincide) return true;     //Si no coincide alguna, devolvemos que son distintas (true)
    }
    return false;   //Si todas coinciden, devolvemos false, ya que son iguales
}