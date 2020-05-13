#include <iostream>
#include <cstring>
#include "menu.h"
using namespace std;

/**
* @brief Constructor por defecto
* 
*/

Menu::Menu() {
    this->titulo = 0;
    this->opc = 0;
    this->nopc = 0;
} 

/**
 * @brief Constructor por argumentos
 * 
 * @param titulo titulo inicial
 * @param opcion opcion inicial
 */

Menu::Menu(const char *titulo, const char *opcion) {
    this->setTitulo(titulo);                        //Definimos el titulo
    this->nopc = 1;                                 //Declaramos que hay una sola opción
    this->opc = new char* [this->nopc];             //Creamos una fila
    *this->opc = new char [strlen(opcion)];         //Creamos una columna de la longitud adecuada
    for (int i = 0; i < strlen(opcion); i++) {      //Copiamos los valores char
        *(*(this->opc) + i) = opcion[i];
    }
}



/**
* @brief Constructor de copia
* 
*/

Menu::Menu(const Menu &copia) {
    this->nopc = copia.nopc;                                    //Copiamos el numero de opciones
    this->setTitulo(copia.titulo);                              //Definimos el titulo para que sea el mismo
    this->opc = new char *[this->nopc];                         //Creamos tantas filas como necesitamos
    for (int i = 0; i < this->nopc; i++) {                      //Copiamos fila a fila el contenido
        *(this->opc + i) = new char [strlen(*(copia.opc + i))]; //Creando las columnas en el proceso
        for (int j = 0; j < strlen(*(copia.opc + i)); j++ ) {
            *(*(this->opc + i) + j) = *(*(copia.opc + i) + j);
        }
    }
}


/**
 * @brief Destructor implementar
 * 
 */

Menu::~Menu() {
    for (int i = 0; i < this->nopc; i++) {  //Borramos el array de cada columna de la matriz
        delete [] *(this->opc + i);
    }
    delete [] this->opc;                    //Borramos el array de las filas
    delete [] this->titulo;                 //Borramos el titulo
}




void Menu::setTitulo(const char * titulo){
    this->titulo = new char [ strlen ( titulo )];
    
    for ( int i=0; i < strlen(titulo); i++)
    {
        this->titulo[i] = titulo[i];
    }
    
}

void Menu::setNumeroOpciones(int nopc){
    this->nopc = nopc;
}

const char * Menu::getTitulo(){
    return this->titulo;
}

int Menu::getNumeroOpciones(){
    return this->nopc;
}


/**
 * @brief agregarOpcion
 * 
 * @param opcion cadena para inicializar el constructor
 */

void Menu::agregarOpcion(const char * opcion) {
    char **aux = this->opc;                                         //Creamos un auxiliar que apunte a la matriz
    this->opc = new char* [this->nopc + 1];                         //Creamos una nueva matriz con el numero de filas necesario

    for (int i = 0; i < this->nopc; i++) {                          //Copiamos los valores que ya teníamos desde el auxiliar
        *(this->opc + i) = new char [strlen(*(aux + i))];           //Creamos las columnas en cada fila
        for (int j = 0; j < strlen(*(aux + i)); j++) {
            *(*(this->opc + i) + j) = *(*(aux + i ) + j);
        }
    }

    for (int i = 0; i < this->nopc; i++) delete [] *(aux + i);      //Borramos puntero auxiliar
    delete [] aux;

    *(this->opc + nopc) = new char [strlen(opcion)];           //Introducimos el valor nuevo
    for (int i = 0; i < strlen(opcion); i++) {
        *(*(this->opc + nopc) + i) = *(opcion + i);
    }

    this->nopc++;                                                   //Aumentamos el numero de opciones
}




/**
 * @brief Sobrecarga del operador <<
 * 
 * @param ios Objeto de buffer de entrada
 * @param b Objeto Menu
 * @return ostream& 
 */
ostream & operator << ( ostream &os, Menu &m){
    os << endl;
    os << m.getTitulo() << endl;
    os << "=================" << endl;
    for ( int i=0; i< m.getNumeroOpciones(); i++ ){
        os <<  * ( m.opc + i )  << endl;
    }
    os << endl;
    return os;
}