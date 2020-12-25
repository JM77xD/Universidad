/**
  * @file almacen_rutas.h
  * @brief Fichero con la definición e implementación de la clase Almacen_Rutas
  *
  * Permite el trabajo con un conjunto de Ruta
  * 
  * @see Ruta
  *
  */

#ifndef _RUTAS_
#define _RUTAS_

#include "ruta.h"
#include <set>
#include <map>

using namespace std;

/**
 * @class Almacen_Rutas
 * 
 * @brief Permite y facilita el almacenamiento y manejo de un conjunto de Ruta
 * 
 * @see Ruta
 * 
 */
class Almacen_Rutas{
  	private:

		/**
		 * @brief Conjunto de Rutas
		 * 
		 * @see Ruta
		 * 
		 */
    	set<Ruta> datos;
		
		/**
		 * @brief Numero de puntos de interés de las diferentes rutas
		 * 
		 */
		int nInteres = 0;


		/**
		 * @brief Puntos de interes de las rutas
		 * 
		 * @see Punto
		 * 
		 */
		map<Punto, string> puntosInteres;

  	public:

		/**
		 * @brief Obtiene una ruta determinada
		 * 
		 * @param a Código de la ruta a obtener
		 * @return Devuelve un objeto ruta
		 */
        Ruta GetRuta(const string a) {
            iterator it;
            for (it = begin(); it != end() && !((*it)==a); ++it);
            return *it;
        }

		/**
		 * @brief Constructor por defecto
		 * 
		 */
    	Almacen_Rutas(){}

		/**
		 * @brief Inserta una nueva Ruta en el conjunto de Rutas
		 * 
		 * @param R Ruta a insertar
		 */
    	void Insertar(const Ruta &R){
	  		datos.insert(R);
      	}

		/**
		 * @brief Borra una Ruta del conjunto de Rutas
		 * 
		 * @param R Ruta a borrar
		 */
      	void Borrar(const Ruta &R){
	  		datos.erase(R);
      	}

		/**
		 * @class iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Almacen_Rutas de manera más cómoda
		 * 
		 */
		class iterator{
			private:

				/**
				 * @brief Iterador de un conjunto de Rutas
				 * 
				 */
			    set<Ruta>::iterator r;

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
					++r;
					return * this;
			    }

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve una referencia a si mismo 
				 */
			    iterator & operator --(){
					--r;
					return * this;
			    }

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterator del que asignar
				 * @return Devuelve una referencia a si mismo
				 */
                iterator & operator = (const iterator & it) {
                    r = it.r;
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
					return it.r ==r;
			    }

				/**
				 * @brief Operador de desigualdad
				 * 
				 * @param it iterator con el que comparar
				 * @return true si no tienen el mismo valor
				 * @return false si tienen el mismo valor
				 */
			    bool operator !=(const iterator  & it){
					return it.r !=r;
			    }

				/**
				 * @brief Operador de acceso
				 * 
				 * @return Devuelve una referencia al elemento de la clase Ruta sobre el que itera
				 */
			    const Ruta & operator*()const{
					return *r;
			    }

			    friend class Almacen_Rutas;

			    friend class const_iterator;

		};

		/**
		 * @class const_iterator
		 * 
		 * @brief Permite recorrer un objeto de la clase Almacen_Rutas de manera más cómoda
		 * 
		 */
		class const_iterator{
			private:

				/**
				 * @brief Iterador constante de un conjunto de Rutas
				 * 
				 */
			    set<Ruta>::const_iterator r;

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
			    	r=it.r;
			    }

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterator del que asignar
				 * @return Devuelve una referencia a si mismo
				 */
			    const_iterator & operator=(const iterator & it){
					r=it.r;
					return *this;
			    }

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve una referencia a si mismo
				 */
			    const_iterator & operator ++(){
					++r;
					return * this;
			    }

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve una referencia a si mismo 
				 */
			    const_iterator & operator --(){
					--r;
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
					return it.r ==r;
			    }

				/**
				 * @brief Operador de desigualdad
				 * 
				 * @param it const_iterator con el que comparar
				 * @return true si no tienen el mismo valor
				 * @return false si tienen el mismo valor
				 */
			    bool operator !=(const const_iterator  & it){
					return it.r !=r;
			    }

				/**
				 * @brief Operador de acceso
				 * 
				 * @return Devuelve una referencia de solo lectura al elemento de la clase Ruta sobre el que itera
				 */
			    const Ruta &operator*()const {
					return *r;
			    }

			    friend class Almacen_Rutas;

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
			it.r = datos.begin();
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
			it.r = datos.begin();
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
			it.r = datos.end();
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
			it.r = datos.end();
			return it;
		}

		/**
		 * @brief Encuentra una Ruta en el conjunto de rutas actual
		 * 
		 * @param r Ruta a encontrar
		 * @return Devuelve un iterator sobre la Ruta r
		 */
		iterator find(const Ruta &r){
		    iterator it;
		    set<Ruta>::iterator i;
		    for (i=datos.begin(); i!=datos.end() && !((*i)==r);++i);
		    it.r=i;
		    return it;
		}

		/**
		 * @brief Operador de entrada
		 * 
		 * @param is Flujo de entrada desde el que se van a leer los datos
		 * @param R Objeto de la clase Almacen_Rutas en el que se introducen los datos leidos
		 * @return Devuelve un flujo de entrada, permitiendo la concatenación de entradas
		 */
		friend istream & operator>>(istream & is, Almacen_Rutas & R){
		    Almacen_Rutas rlocal;
		    //leemos el comentario
		    if (is.peek()=='#'){
				string a;
				getline(is,a);
		    }

		    Ruta P;

		    while (is.peek() != '#' && !is.eof()){
				is >> P;
				rlocal.Insertar(P);
				is.ignore(100, '\n');
		    }

			if (is.peek() == '#') {
				string a;
				getline (is,a);
				while (!is.eof()) {
					rlocal.nInteres++;
					pair<Punto, string> p;
					is >> p.first;
					getline(is, p.second);
					rlocal.puntosInteres.insert(p);
				}
			}

		    R=rlocal;
		    return is;
		}
		
		/**
		 * @brief Operador de salida
		 * 
		 * @param os Flujo de salida por el que se van a sacar los datos
		 * @param R Objeto de la clase Almacen_Rutas del que se van a leer los datos
		 * @return Devuelve un flujo de salida, permitiendo la concatenación de salidas
		 */
		friend ostream & operator<<(ostream & os, const Almacen_Rutas &R){
		
		    Almacen_Rutas::const_iterator it;
		    for (it=R.begin(); it!=R.end(); ++it){
			os<<*it<<"\n";
		    }
			if (R.nInteres > 0) {
				os << "\nLos puntos de interés:\n";
				map<Punto,string>::const_iterator i;
				for (i = R.puntosInteres.begin(); i != R.puntosInteres.end(); ++i) {
					os << (*i).first << (*i).second << endl;
				}
			}
		    return os;
		}
};

#endif