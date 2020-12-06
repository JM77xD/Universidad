/**
 * @file pila_max_VD.h
 * @brief Fichero cabecera del TDA Pila
 *
 * Gestiona una secuencia de elementos con facilidades para la inserción y
 * borrado de elementos en un extremo
 *
 */

#ifndef PILA_MAX_VD_H_
#define PILA_MAX_VD_H_

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief struct elemento
 * 
 * 
 * Una instancia @e p del tipo elemento es un elemento formado por el valor
 * asociado dicha @c elemento y el máximo de los valores de todas las Elementos
 * almacenadas
 */
struct elemento{
  int valor = 0;   /**< valor del elemento */
  int max = 0;     /**< valor máximo almacenado en la pila */
 };

 /**
   * @brief Sobrecarga del operador <<
   * @param flujo Flujo de salida
   * @param p @c elemento que se quiere escribir
   */
ostream& operator << (ostream &flujo, const elemento &p);

/**
 * 
 *  @class Pila_max_VD
 * 
 *  @brief T.D.A. Pila_max_VD
 *
 * Una instancia @e v del tipo de datos abstracto Pila sobre el tipo @c T es
 * una lista de elementos del mismo con un funcionamiento @e LIFO (Last In,
 * First Out). En una pila, las operaciones de inserción y borrado de elementos
 * tienen lugar en uno de los extremos denominado @e Tope. Una pila de longitud
 * @e n la denotamos

 * - [a1,a2,a3,..,an>

 * donde @e ai es el elemento de la posición i-ésima.

 * En esta pila, tendremos acceso únicamente al elemento del @e Tope, es decir,
 * a @e an. El borrado o consulta de un elemento será sobre  @e an, y la
 * inserción de un nuevo elemento se hará sobre éste. Quedando el elemento
 * insertado como @e Tope de la pila.

 * Si @e n=0 diremos que la pila está vacía.

 * El espacio requerido para el almacenamiento es O(n). Donde n es el número de
 * elementos de la Pila.
 *
 * Además, esta Pila almacena Elementos de @b valor @b | @b máximo, donde máximo
 * denota el valor máximo de los elementos inferiores en la Pila. Esto permite
 * conocer el máximo de los valores de la pila en todo momento.
 *
 * Para la implementación de la Pila, se ha usado una estructura vector,
 * situando el @e tope de la Pila en la última posición ocupada del vector.
 *
 * @author José María Ramírez González
 * @date Noviembre 2020
 */
class Pila_max_VD{
    private:
        vector<elemento> elementos; /**< vector de elementos de la Pila */

    public:
        // ---------------  Constructores ----------------
        
        /**
         * @brief Constructor por defecto
         */
        Pila_max_VD():elementos(){}
        /**
         * @brief Constructor de copias
         * @param otra La pila de la que se hará la copia.
         */
        Pila_max_VD(const Pila_max_VD & otra);

        // --------------- Otras funciones ---------------

        /**
         * @brief Sobrecarga del operador de asignación
         * @param otra La pila que se va a asignar.
         */
        Pila_max_VD& operator= (const Pila_max_VD& otra);

        /**
         * @brief Comprueba si la pila está vacía
         */
        bool vacia() const;
        /**
         * @brief Devuelve el elemento del tope de la pila
         */
        elemento& tope ();
        /**
         * @brief Devuelve el elemento del tope de una pila constante
         */
        const elemento& tope () const;
        /**
         * @brief Añade un elemento "encima" del tope de la pila
         * @param n elemento que se va a añadir.
         */
        void poner(const int &n);
        /**
         * @brief Quita el elemento del tope de la pila
         */
        void quitar();

        /**
         * @brief Devuelve el número de elementos de la pila
         */
        int getNelementos() const;

        /**
         * @brief Devuelve el valor máximo almacenado en la pila
         */
        int maximo() const;
};

//#include "../src/pila_max_VD.cpp"

#endif