/**
  * @file ruta.h
  * @brief Fichero con la definición e implementación de la clase Ruta
  *
  * Permite el trabajo con objetos de la misma clase
  * 
  * @see Punto
  * @see Almacen_Rutas
  *
  */

#ifndef _RUTA_
#define _RUTA_

#include "Punto.h"
#include <list>
#include <string>
#include <cassert>
#include <iostream>


using namespace std;

/**
 * @class Ruta
 * 
 * @brief Permite y facilita el trabajo con los conjuntos de datos que constituyen una ruta de vuelo (puntos de parada, nombre de la ruta y número de puntos)
 * 
 * @see Punto
 * 
 * @see Almacen_Rutas
 * 
 */
class Ruta {

    private:

		/**
		 * @brief Nombre de la Ruta
		 * 
		 */
        string nombreRuta;

		/**
		 * @brief Numero de Puntos que tiene la Ruta
		 * 
		 */
        int nPuntos;

		/**
		 * @brief Conjunto de Puntos
		 * 
		 * @see Punto
		 * 
		 */
        list<Punto> puntos;

    public:

		/**
		 * @brief Constructor por defecto
		 * 
		 */
        Ruta() {}

		/**
		 * @brief Constructor a partir de un nombre y una lista de puntos
		 * 
		 * @param nombre Nombre de la ruta
		 * @param p Lista de puntos que forman la ruta
		 */
        Ruta(string nombre, list<Punto> p) {
            nombreRuta = nombre;
            puntos = p;
            nPuntos = p.size();
        }

		/**
		 * @brief Constructor de copia
		 * 
		 * @param r Ruta de la que copiar los valores
		 */
        Ruta(const Ruta &r) {
            nombreRuta = r.nombreRuta;
            nPuntos = r.nPuntos;
            puntos = r.puntos;
        }

		/**
		 * @brief Permite obtener el Punto en una posición concreta
		 * 
		 * @param pos Posición de la que obtener el punto
		 * @return Devuelve el objeto de la clase Punto en la posición pos
		 */
        Punto getPunto(int pos) {
            assert(pos < puntos.size());
            list<Punto>::iterator it = puntos.begin();
            for (int i = 0; i < pos; i++)
                ++it;
            return *it;
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si la Ruta tiene el mismo nombre
		 * @return false Si el nombre de la Ruta es distinto
		 */
        bool operator==(const Ruta &r) {
            return (nombreRuta == r.nombreRuta);
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si la Ruta tiene el mismo nombre
		 * @return false Si el nombre de la Ruta es distinto
		 */
        bool operator==(const Ruta &r) const {
            return (nombreRuta == r.nombreRuta);
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param s String a comparar
		 * @return true Si s es igual al nombre de la Ruta
		 * @return false Si s es distinto al nombre de la Ruta
		 */
        bool operator==(const string &s) {
            return (nombreRuta == s);
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param s String a comparar
		 * @return true Si s es igual al nombre de la Ruta
		 * @return false Si s es distinto al nombre de la Ruta
		 */
        bool operator==(const string &s) const {
            return (nombreRuta == s);
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param p Punto a comparar
		 * @return true Si p está en la Ruta
		 * @return false Si p no está en la Ruta
		 */
        bool operator==(const Punto &p){
            list<Punto>::const_iterator i;

            for (i = puntos.cbegin(); i != puntos.cend(); ++i) {
                if ((*i) == p)
                    return true;
            }

            return false;
        }

		/**
		 * @brief Comparativa de igualdad
		 * 
		 * @param p Punto a comparar
		 * @return true Si p está en la Ruta
		 * @return false Si p no está en la Ruta
		 */
        bool operator==(const Punto &p) const{
            list<Punto>::const_iterator i;

            for (i = puntos.cbegin(); i != puntos.cend(); ++i) {
                if ((*i) == p)
                    return true;
            }

            return false;
        }

		/**
		 * @brief Comparación de inferioridad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si el nombre de la Ruta this es menor al nombre de la Ruta r
		 * @return false Si el nombre de la Ruta this es mayor al nombre de la Ruta r
		 */
        bool operator<(const Ruta & r) {
            return nombreRuta < r.nombreRuta;
        }

		/**
		 * @brief Comparación de inferioridad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si el nombre de la Ruta this es menor al nombre de la Ruta r
		 * @return false Si el nombre de la Ruta this es mayor al nombre de la Ruta r
		 */
        bool operator<(const Ruta & r) const {
            return nombreRuta > r.nombreRuta;
        }

		/**
		 * @brief Comparación de inferioridad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si el nombre de la Ruta this es mayor al nombre de la Ruta r
		 * @return false Si el nombre de la Ruta this es menor al nombre de la Ruta r
		 */
        bool operator>(const Ruta & r) {
            return nombreRuta > r.nombreRuta;
        }

		/**
		 * @brief Comparación de inferioridad
		 * 
		 * @param r Ruta a comparar
		 * @return true Si el nombre de la Ruta this es mayor al nombre de la Ruta r
		 * @return false Si el nombre de la Ruta this es menor al nombre de la Ruta r
		 */
        bool operator>(const Ruta & r) const {
            return nombreRuta > r.nombreRuta;
        }

		/**
		 * @brief Operador de salida
		 * 
		 * @param os Flujo de salida
		 * @param r Objeto de la clase Ruta del que se van a leer los datos
		 * @return Devuelve un flujo de salida, permitiendo la concatenación de salidas
		 */
        friend ostream &operator<<(ostream &os, const Ruta &r) {
            os << r.nombreRuta << "\t" << r.nPuntos << "\t";

            list<Punto>::const_iterator it;

            for (it = r.puntos.cbegin(); it != r.puntos.cend(); ++it)
                os << *it;

            return os;
        }

		/**
		 * @brief Operador de entrada
		 * 
		 * @param is Flujo de entrada desde el que se van a leer los datos
		 * @param r Objeto de la clase Ruta en el que se introducen los datos leidos
		 * @return Devuelve un flujo de entrada, permitiendo la concatenación de entradas
		 */
        friend istream & operator>>(istream &is , Ruta & r) {
            is >> r.nombreRuta >> r.nPuntos;

            for (int i = 0; i < r.nPuntos; i++) {
                Punto p;
                is >> p;
                r.puntos.push_back(p);
            }

            return is;
        }


//------------------------------------------------------ITERADORES----------------------------------------

		/**
		 * @class iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Ruta de manera más cómoda
		 * 
		 */
        class iterator{
			private:

				/**
				 * @brief Iterador de una lista de Puntos
				 * 
				 */
			    list<Punto>::iterator p;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
			    iterator(){}

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve una referencia a si mismo
				 */
			    iterator & operator ++(){
					++p;
					return * this;
			    }

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve una referencia a si mismo 
				 */
			    iterator & operator --(){
					--p;
					return * this;
			    }

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterator del que asignar
				 * @return Devuelve una referencia a si mismo
				 */
                iterator & operator = (const iterator & it) {
                    p = it.p;
                    return *this;
                }

				/**
				 * @brief Operador de igualdad
				 * 
				 * @param it iterator con el que comparar
				 * @return true si tienen el mismo valor
				 * @return false si no tienen el mismo valor
				 */
			    bool operator ==(const iterator  & it){
					return it.p ==p;
			    }

				/**
				 * @brief Operador de desigualdad
				 * 
				 * @param it iterator con el que comparar
				 * @return true si no tienen el mismo valor
				 * @return false si tienen el mismo valor
				 */
			    bool operator !=(const iterator  & it){
					return it.p !=p;
			    }

				/**
				 * @brief Operador de acceso
				 * 
				 * @return Devuelve una referencia al elemento de la clase Punto sobre el que itera
				 */
			    const Punto & operator*()const{
					return *p;
			    }
				
			    friend class Ruta;

			    friend class const_iterator;

		};


		/**
		 * @class const_iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Ruta de manera más cómoda
		 * 
		 */
		class const_iterator{
			private:

				/**
				 * @brief Iterador de solo lectura de una lista de Puntos
				 * 
				 */
			    list<Punto>::const_iterator p;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
			    const_iterator(){}

				/**
				 * @brief Constructor a partir de un elemento iterator
				 * 
				 * @param it iterator desde el que construir el nuevo const_iterator
				 */
			    const_iterator(const iterator & it){
			    	p=it.p;
			    }

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterator del que asignar
				 * @return Devuelve una referencia a si mismo
				 */
			    const_iterator & operator=(const iterator & it){
					p=it.p;
					return *this;
			    }

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve una referencia a si mismo
				 */
			    const_iterator & operator ++(){
					++p;
					return * this;
			    }

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve una referencia a si mismo 
				 */
			    const_iterator & operator --(){
					--p;
					return * this;
			    }

				/**
				 * @brief Operador de igualdad
				 * 
				 * @param it const_iterator con el que comparar
				 * @return true si tienen el mismo valor
				 * @return false si no tienen el mismo valor
				 */
			    bool operator ==(const const_iterator  & it){
					return it.p ==p;
			    }

				/**
				 * @brief Operador de desigualdad
				 * 
				 * @param it const_iterator con el que comparar
				 * @return true si no tienen el mismo valor
				 * @return false si tienen el mismo valor
				 */
			    bool operator !=(const const_iterator  & it){
					return it.p !=p;
			    }

				/**
				 * @brief Operador de acceso
				 * 
				 * @return Devuelve una referencia de solo lectura al elemento de la clase Punto sobre el que itera
				 */
			    const Punto &operator*()const {
					return *p;
			    }

			    friend class Ruta;

		};

		/**
		 * @brief Apunta al comienzo de puntos
		 * 
		 * @return Devuelve un iterator sobre el comienzo de puntos
		 * 
		 * @see iterator
		 */
		iterator begin(){
			iterator it;
			it.p = puntos.begin();
			return it;
		}  

		/**
		 * @brief Apunta al comienzo de puntos
		 * 
		 * @return Devuelve un const_iterator sobre el comienzo de puntos
		 * 
		 * @see const_iterator
		 */
		const_iterator begin()const{
			const_iterator it;
			it.p = puntos.begin();
			return it;
		}

		/**
		 * @brief Apunta al final de puntos
		 * 
		 * @return Devuelve un iterator sobre el final de puntos
		 * 
		 * @see iterator
		 */
		iterator end(){
			iterator it;
			it.p = puntos.end();
			return it;
		}

		/**
		 * @brief Apunta al final de puntos
		 * 
		 * @return Devuelve un const_iterator sobre el final de puntos
		 * 
		 * @see const_iterator
		 */
		const_iterator end()const{
			const_iterator it;
			it.p = puntos.end();
			return it;
		}

		/**
		 * @brief Encuentra si el Punto p se encuentra en la Ruta actual
		 * 
		 * @param p Punto a encontrar
		 * @return Devuelve un iterator sobre el Punto que coincide con P
		 */
		iterator find(const Punto &p){
		    iterator it;
		    list<Punto>::iterator i;
		    for (i=puntos.begin(); i!=puntos.end() && !((*i)==p);++i);
		    it.p=i;
		    return it;
		}
        


};

#endif