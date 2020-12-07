#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>


using namespace std;

/**
 * @struct data
 * 
 * @brief Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
 *	no se repite (DNI p.ej.) y list<U> es una lista de datos (string p.ej) asociados a la clave
 *	de tipo T. El diccionario está ordenado de menor a mayor clave.
 */
template <class T,class U>
struct data {
    T clave;
    list<U> info_asoci;
};

 
/**
  * @brief Comparador de datos. Ordena 2 registros de acuerdo a la clave de tipo T. Puede usarse como
  *	un funtor.
  */
template <class T, class U>
bool operator< (const data<T,U> &d1,const data <T,U>&d2){
	   if (d1.clave < d2.clave)
		     return true;
	   return false;
}	   

/**
 * @class Diccionario
 * 
 * @brief Un diccionario es una lista de datos de los definidos anteriormente. Cuidado porque se
 *	manejan listas de listas. Se añaden 2 funciones privadas que hacen más facil la implementación
 *	de algunos operadores o funciones de la parte pública. Copiar copia un diccioario en
 *	otro y borrar elimina todos los elementos de un diccionario. La implementación de copiar
 *	puede hacerse usando iteradores o directamente usando la función assign.
 */
template <class T,class U>
class Diccionario{

	private:
		    
		  
 		list<data<T,U>> datos;

		/**
		 * @brief Copia de un diccionario
		 * 
		 * @param D Diccionario del que copiar
		 */
		void Copiar(const Diccionario<T,U>& D);
		    
		/**
		 * @brief Borra la lista de datos
		 * 
		 */
		void Borrar();      
			   
			       
	public:


//-------------------------------Definición de iteradores---------------------------

		/**
		 * @class Diccionario<T,U>::iterator
		 * 
		 * @brief Iterador no constante para recorrer la lista de datos
		 * 
		 */
		class iterator{

			private:

				typename list<data<T,U>>::iterator vit;

				/**
				 * @brief Constructor con parámetros
				 * 
				 * @param it Iterador de una lista de datos
				 * 
				 */
				iterator(typename list<data<T,U>>::iterator it){vit=it;}

				friend class Diccionario<T,U>;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
				iterator(){}

				/**
				 * @brief Constructor de copia
				 * 
				 * @param it Iterador a copiar
				 */
				iterator(const iterator &it);

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterador a asignar
				 * @return Devuelve el iterador
				 */
				iterator &operator=(const iterator &it);

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve el propio iterador incrementado en una unidad
				 * 
				 */
				iterator & operator++();

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve el propio iterador decrementado en una unidad
				 * 
				 */
				iterator & operator--();

				/**
				 * @brief Operador de puntero
				 * 
				 * @return Devuelve una referencia a un elemento tipo dato
				 */
				data<T,U> & operator*();
				
				/**
				 * @brief Operador distinto de
				 * 
				 * @param it Iterador a comparar
				 * @return Devuelve true si un iterador es distinto de otro y false en caso contrario
				 */
				bool operator!=(const iterator &it) const;

				/**
				 * @brief Operador igual que
				 * 
				 * @param it Iterador a comparar
				 * @return Devuelve true si un iterador es similar que otro y false en caso contrario
				 */
				bool operator==(const iterator &it) const;

		};

		/**
		 * @brief Método begin para obtener un iterador
		 * 
		 * @return Devuelve un iterador al primer elemento de datos
		 */
		iterator begin();

		/**
		 * @brief Método end para obtener un iterador
		 * 
		 * @return Devuelve un iterador al último elemento de datos
		 */
		iterator end();
		

		/**
		 * @class Diccionario::const_iterator
		 * 
		 * @brief Iterador constante para recorrer la lista de datos
		 * 
		 */
		class const_iterator {

			private:
				typename list<data<T,U>>::const_iterator vit;

				/**
				 * @brief Constructor con parámetros
				 * 
				 * @param it Iterador de una lista de datos
				 */
				const_iterator(typename list<data<T,U>>::const_iterator it){vit=it;}

				friend class Diccionario<T,U>;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
				const_iterator(){}

				/**
				 * @brief Constructor por parámetros
				 * 
				 * @param it Iterador desde el que construir el nuevo objeto
				 * 
				 */
				const_iterator(const const_iterator &it);

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it Iterador a asignar
				 * @return Devuelve un el propio iterador
				 */
				const_iterator & operator=(const const_iterator &it);

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve el propio iterador incrementado en una unidad 
				 */
				const_iterator & operator++();

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve el propio iterador decrementado en una unidad 
				 */
				const_iterator & operator--();

				/**
				 * @brief Operador de puntero
				 * 
				 *  @return Devuelve una referencia constante a un elemento tipo dato
				 * 
				 */
				const data<T,U> & operator*() const;

				/**
				 * @brief Operador distinto de
				 * 
				 * @param it Iterador a comparar
				 * @return Devuelve true si un iterador es distinto de otro y false en caso contrario
				 */
				bool operator!=(const const_iterator &it) const;

				/**
				 * @brief Operador igual que
				 * 
				 * @param it Iterador a comparar
				 * @return Devuelve true si un iterador es similar que otro y false en caso contrario
				 */
				bool operator==(const const_iterator &it) const;

		};

		/**
		 * @brief Método cbegin para obtener un iterador
		 * 
		 * @return Devuelve un iterador constante al primer elemento de datos
		 */
		const_iterator cbegin() const;

		/**
		 * @brief Método cend para obtener un iterador
		 * 
		 * @return Devuelve un iterador constante al último elemento de datos
		 */
		const_iterator cend() const;


//-------------------------------Definición de métodos---------------------------


	     /**
	      * @brief Constructor por defecto
	      * 
	      */
		Diccionario():datos(list<data<T,U> >()){}
		 
		/**
		 * @brief Constructor de copia
		 * 
		 * @param D Diccionario que copiar
		 *  
		 */
		Diccionario(const Diccionario &D){
			Copiar(D);
		}

		/**
		 * @brief Destructor
		 * 
		 */
		~Diccionario(){}

		/**
		 * @brief Operador de asignación
		 * 
		 * @param D Diccionario que tomar como referencia
		 * @return Devuelve un diccionario nuevo
		 */
		Diccionario<T,U> & operator=(const Diccionario<T,U> &D);

		/**
		 * @brief Busca la clave p en el diccionario. Si está devuelve un iterador a
		 *	dónde está clave. Si no está, devuelve end() y deja el iterador de salida
		 *	apuntando al sitio dónde debería estar la clave
		 * 
		 * @param p Clave que verificar si existe
		 * @param it_out Iterador sobre el que se comprueba la clave
		 * @return Devuelve true o false, dependiendo si existe la clave o no
		 */
		bool Esta_Clave(const T &p, typename  list<data<T,U> >::iterator &it_out);

	 	/**
	 	 * @brief Inserta un nuevo registro en el diccionario. Lo hace a través de la clave
	 	 *	e inserta la lista con toda la información asociada a esa clave. Si el 
	 	 *	diccionario no estuviera ordenado habría que usar la función sort()
	 	 * 
	 	 * @param clave Clave en la que insertar la información
	 	 * @param info Información a insertar
	 	 */
	 	void Insertar(const T& clave,const list<U> &info);

		/**
		 * @brief Añade una nueva informacion asocida a una clave que está en el diccionario.
		 *	La nueva información se inserta al final de la lista de información.
         *	Si no esta la clave la inserta y añade la informacion asociada.
		 * 
		 * @param s Información a añadir
		 * @param p Clave donde añadirla
		 */
		void AddSignificado_Palabra(const U & s ,const T &p);

	 	/**
	 	 * @brief Devuelve la información (una lista) asociada a una clave p. Podrían 
	 	 *	haberse definido operator[] como
	 	 *	data<T,U> & operator[](int pos){ return datos.at(pos);}
	 	 *	const data<T,U> & operator[](int pos)const { return datos.at(pos);}
	 	 * 
	 	 * @param p Clave asociada a la info a devolver
	 	 * @return list<U> 
	 	 */
	 	list<U>  getInfo_Asoc(const T & p);		   



		/**
		 * @brief Consultor del tamaño del diccionario
		 * 
		 * @return Devuelve el tamaño del diccionario
		 * 
		 */
		int size()const{
			return datos.size();
		}

};

#include <../src/diccionario.cpp>

#endif