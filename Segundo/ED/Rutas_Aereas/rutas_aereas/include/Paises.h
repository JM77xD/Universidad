/**
  * @file Paises.h
  * @brief Fichero con la definición e implementación de la clase Paises
  *
  * Permite el trabajo con un conjunto de Pais
  * 
  * @see Pais
  *
  */

#ifndef _PAISES_
#define _PAISES_


#include "Pais.h"
#include <set>


using namespace std;

/**
 * @class Paises
 * 
 * @brief Permite y facilita el almacenamiento y manejo de un conjunto de Pais
 * 
 * @see Pais
 * 
 */
class Paises{
  	private:

		/**
		 * @brief Conjunto de Paises
		 * 
		 * @see Pais
		 * 
		 */
    	set<Pais> datos;

  	public:

		/**
		 * @brief Constructor por defecto
		 * 
		 */
    	Paises(){}

		/**
		 * @brief Inserta un nuevo Pais en el conjunto de paises
		 * 
		 * @param P Pais a insertar
		 */
    	void Insertar(const Pais &P){
	  		datos.insert(P);
      	}

		/**
		 * @brief Borra un Pais del conjunto de paises
		 * 
		 * @param P Pais a borrar
		 */
      	void Borrar(const Pais &P){
	  		datos.erase(P);
      	}

		/**
		 * @class iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Paises de manera más cómoda
		 * 
		 */
		class iterator{
			private:

				/**
				 * @brief Iterador de un conjunto de Paises
				 * 
				 */
			    set<Pais>::iterator p;

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
				iterator & operator=(const iterator & it) {
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
				 * @return Devuelve una referencia al elemento de la clase Pais sobre el que itera
				 */
			    const Pais & operator*()const{
					return *p;
			    }

			    friend class Paises;

			    friend class const_iterator;

		};

		/**
		 * @class const_iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Paises de manera más cómoda
		 * 
		 */
		class const_iterator{
			private:

				/**
				 * @brief Iterador constante de un conjunto de Paises
				 * 
				 */
			    set<Pais>::const_iterator p;

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
				 * @return Devuelve una referencia de solo lectura al elemento de la clase Pais sobre el que itera
				 */
			    const Pais &operator*()const {
					return *p;
			    }

			    friend class Paises;

		};

		/**
		 * @brief Apunta al comienzo de datos
		 * 
		 * @return Devuelve un iterator sobre el comienzo de datos
		 * 
		 * @see iterator
		 */
		iterator begin(){
			iterator it;
			it.p = datos.begin();
			return it;
		}  

		/**
		 * @brief Apunta al comienzo de datos
		 * 
		 * @return Devuelve un const_iterator sobre el comienzo de datos
		 * 
		 * @see const_iterator
		 */
		const_iterator begin()const{
			const_iterator it;
			it.p = datos.begin();
			return it;
		}
		
		/**
		 * @brief Apunta al final de datos
		 * 
		 * @return Devuelve un iterator sobre el final de datos
		 * 
		 * @see iterator
		 */
		iterator end(){
			iterator it;
			it.p = datos.end();
			return it;
		}

		/**
		 * @brief Apunta al final de datos
		 * 
		 * @return Devuelve un const_iterator sobre el final de datos
		 * 
		 * @see const_iterator
		 */
		const_iterator end()const{
			const_iterator it;
			it.p = datos.end();
			return it;
		}

		/**
		 * @brief Encuentra un Pais en el conjunto de paises actual
		 * 
		 * @param p Pais a encontrar
		 * @return Devuelve un iterator sobre el Pais p
		 */
		iterator find(const Pais &p){
		    iterator it;
		    set<Pais>::iterator i;
		    for (i=datos.begin(); i!=datos.end() && !((*i)==p);++i);
		    it.p=i;
		    return it;
		}

		/**
		 * @brief Encuentra un Pais que se localice en un Punto concreto en el conjunto de paises actual
		 * 
		 * @param p Punto a encontrar
		 * @return Devuelve un iterator sobre el Pais cuya localización coincide con p
		 */
		iterator find(const Punto &p){
		    iterator it;
		    set<Pais>::iterator i;
		    for (i=datos.begin(); i!=datos.end() && !((*i)==p);++i);
		    it.p=i;
		    return it;
		}

		/**
		 * @brief Operador de entrada
		 * 
		 * @param is Flujo de entrada desde el que se van a leer los datos
		 * @param R Objeto de la clase Paises en el que se introducen los datos leidos
		 * @return Devuelve un flujo de entrada, permitiendo la concatenación de entradas
		 */
		friend istream & operator>>(istream & is, Paises & R){
		      Paises rlocal;
		      //leemos el comentario
		      if (is.peek()=='#'){
			string a;
			getline(is,a);
		      }	

		      Pais P;
		      while (is>>P){
			  rlocal.Insertar(P);

		      }
		      R=rlocal;
		      return is;
		}
		
		/**
		 * @brief Operador de salida
		 * 
		 * @param os Flujo de salida por el que se van a sacar los datos
		 * @param R Objeto de la clase Paises del que se van a leer los datos
		 * @return Devuelve un flujo de salida, permitiendo la concatenación de salidas
		 */
		friend ostream & operator<<(ostream & os, const Paises &R){
		
		    Paises::const_iterator it;
		    for (it=R.begin(); it!=R.end(); ++it){
			os<<*it<<"\t";
		    }
		    return os;
		}
};
#endif

