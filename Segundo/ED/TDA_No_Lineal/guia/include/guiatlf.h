#ifndef _GUIA_TLF_H
#define _GUIA_TLF_H
#include <map>
#include <iostream>
#include <string>
using namespace std;
istream & operator>>(istream &is,pair<string,string> &d);

/**
 * @class Guia_Tlf
 * 
 * @brief Permite la lectura de parejas de string y las almacena en formato de guía telefónica.
 * Si quisieramos asignar más de un número de teléfono a un nombre tendríamos que usar un multimap en vez de un map.
 * 
 * Implementa operaciones como la unión de guías telefónicas.
 * 
 */
class Guia_Tlf{
	private:
		map<string,string> datos; 	//si admites que haya nombres repetidos tendrías que usar un multimap
					     
	public:

//------------------------------------Definición de iteradores-----------------------

		/**
		 * @class Guia_Tlf::iterator
		 * 
		 * @brief Iterador no constante para recorrer el mapa
		 * 
		 */
		class iterator{

			private:

				typename map<string,string>::iterator vit;

				/**
				 * @brief Constructor con parámetros
				 * 
				 * @param it Iterador de un mapa de datos
				 * 
				 */
				iterator(const typename map<string,string>::iterator &it){vit=it;}

				friend class Guia_Tlf;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
				iterator(){}
				
				/**
				 * @brief Destructor
				 * 
				 */
				~iterator(){delete &vit;}
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
				 * @return Devuelve una referencia a un elemento tipo pair
				 */
				pair<const string,string> & operator*();
				
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
		Guia_Tlf::iterator begin();

		/**
		 * @brief Método end para obtener un iterador
		 * 
		 * @return Devuelve un iterador al último elemento de datos
		 */
		Guia_Tlf::iterator end();

		/**
		 * @class Guia_Tlf::const_iterator
		 * 
		 * @brief Iterador constante para recorrer el mapa
		 * 
		 */
		class const_iterator{

			private:

				typename map<string,string>::const_iterator vit;

				/**
				 * @brief Constructor con parámetros
				 * 
				 * @param it Iterador de un mapa de datos
				 * 
				 */
				const_iterator(const typename map<string,string>::const_iterator &it){vit=it;}

				friend class Guia_Tlf;

			public:

				/**
				 * @brief Constructor por defecto
				 * 
				 */
				const_iterator(){}

				/**
				 * @brief Destructor
				 * 
				 */
				~const_iterator(){delete &vit;}
				/**
				 * @brief Constructor de copia
				 * 
				 * @param it Iterador a copiar
				 */
				const_iterator(const const_iterator &it);

				/**
				 * @brief Operador de asignación
				 * 
				 * @param it iterador a asignar
				 * @return Devuelve el iterador
				 */
				const_iterator &operator=(const const_iterator &it);

				/**
				 * @brief Operador de incremento
				 * 
				 * @return Devuelve el propio iterador incrementado en una unidad
				 * 
				 */
				const_iterator & operator++();

				/**
				 * @brief Operador de decremento
				 * 
				 * @return Devuelve el propio iterador decrementado en una unidad
				 * 
				 */
				const_iterator & operator--();

				/**
				 * @brief Operador de puntero
				 * 
				 * @return Devuelve una referencia a un elemento tipo pair
				 */
				const pair<const string,string> & operator*() const;
				
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
		 * @brief Método begin para obtener un iterador
		 * 
		 * @return Devuelve un iterador constante al primer elemento de datos
		 */
		Guia_Tlf::const_iterator cbegin() const;

		/**
		 * @brief Método end para obtener un iterador
		 * 
		 * @return Devuelve un iterador constante al último elemento de datos
		 */
		Guia_Tlf::const_iterator cend() const;

//------------------------------------Definición de métodos-----------------------
		/**
		 * @brief Constructor por defecto
		 * 
		 */
		Guia_Tlf(){}

		/**
		 * @brief Constructor de copia
		 * 
		 * @param gt Guia de la que copiar
		 */
		Guia_Tlf(const Guia_Tlf & gt);

		/**
		 * @brief Destructor
		 * 
		 */
		~Guia_Tlf(){delete &datos;}

		/**
		 * @brief Operador de asignación
		 * 
		 * @param gt Guia de la que asignar
		 * @return Devuelve una guía similar a gt
		 */
		Guia_Tlf & operator=(const Guia_Tlf & gt);

		/**
		 * @brief Acceso a un elemento
		 * @param nombre: nombre del elemento  elemento acceder
		 * @return devuelve el valor asociado a un nombre, es decir el teléfono
		 */
		string & operator[](const string &nombre);
		    
		/**
		 * @brief Consultor de un teléfono
		 * 
		 * @param nombre Nombre de la persona cuyo teléfono queremos consultar
		 * @return Devuelve el teléfono asociado a la persona
		 */
		string  gettelefono(const string & nombre);
		     
	    /**
	     * @brief Insert un nuevo telefono 
	     * @param nombre: nombre clave del nuevo telefono
	     * @param tlf: numero de telefono
	     * @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
	     */
	    pair<map<string,string>::iterator,bool>  insert(string nombre, string tlf);
		    
		/**
		 * @brief Insert un nuevo telefono 
		 * @param p: pair con el nombre y el telefono asociado
		 *
		 * @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
		 */
		pair<map<string,string>::iterator,bool>  insert(pair<string,string> p);
		    	    
		/**
		 * @brief Borrar un telefono
		 * @param nombre: nombre que se quiere borrar
		 * @note: en caso de que fuese un multimap borraria todos con ese nombre
		 */
		void borrar(const string &nombre);
		    
		/**
		 * @brief Borrar un telefono
		 * @param nombre: nombre que se quiere borrar
		 * @param tlf: teléfono asociado al nombre
		 * @note: esta funcion nos permite borrar solamente aquel que coincida en nombre y tlf
		 * @note: con map siempre hay uno con multimap puede existir mas de uno
		 */
		void borrar(const string &nombre,const string &tlf);

		/**
		 * @brief  Numero de telefonos 
		 * @return el numero de telefonos asociados
		 */
		int size() const;
      
		/**
		 * @brief Contabiliza cuantos telefonos tenemos asociados a un nombre
		 * @param nombre: nombre sobre el que queremos consultar
		 * @return numero de telefonos asociados a un nombre
		 * @note: al ser un map debe de ser 0 o 1. Si fuese un multimap podríamos tener mas de uno
		 */
		unsigned int contabiliza(const string &nombre);
		    
		/**
		 * @brief Limpia la guia
		 */
		void clear();

		/**
		 * @brief Compara 2 guías y devuelve una guía con los repetidos
		 * 
		 * @param G Guía que comparar
		 * 
		 * @return Devuelve un elemento de la clase guía con los elementos repetidos en this y G
		 * 
		 */
		Guia_Tlf interseccion(Guia_Tlf &G);

		/**
		 * @brief Modifica el teléfono asociado a un nombre
		 * 
		 * @param nombre nombre que modificar
		 * @param tlf nuevo teléfono
		 * 
		 * @note: si es un multimap nos preguntará cúal queremos modificar
		 */
		void modificar(const string &nombre, const string &tlf);

		/**
		 * @brief Consulta números a partir de la primera letra del nombre
		 * 
		 * @param c Carácter sobre el que buscar el nombre
		 * 
		 * @return Devuelve un string con todos los números separados por \n
		 */
		string gettelefonos(char &c);

		/**
		 * @brief Consulta los número de teléfono que se encuentren en un rango determinado
		 * 
		 * @param nombre1 primer nombre del rango
		 * @param nombre2 segundo nombre del rango
		 * @return Devuelve una guía con los elementos que se encuentran en el rango dado
		 * 
		 */
		Guia_Tlf rango(string &nombre1, string &nombre2);

		/**
		 * @brief Union de guias de telefonos
		 * @param g: guia que se une
		 * @return: una nueva guia resultado de unir el objeto al que apunta this y g
		 */
		Guia_Tlf operator+(const Guia_Tlf & g);	   
		    	      
		/**
		 * @brief Diferencia de guias de telefonos
		 * @param g: guia que se une
		 * @return: una nueva guia resultado de la diferencia del objeto al que apunta this y g
		 */
		Guia_Tlf operator-(const Guia_Tlf & g);
		    
		/**
		 * @brief Escritura de la guia de telefonos
		 * @param os: flujo de salida. Es MODIFICADO
		 * @param g: guia de telefonos que se escribe
		 * @return el flujo de salida
		 */  
		friend ostream & operator<<(ostream & os, Guia_Tlf & g);
		    
		/**
		 * @brief Lectura de  la guia de telefonos
		 * @param is: flujo de entrada. ES MODIFICADO
		 * @param g: guia de telefonos. ES MODIFICADO
		 * @return el flujo de entrada
		 */   
		friend istream & operator>>(istream & is, Guia_Tlf & g);

};
#endif