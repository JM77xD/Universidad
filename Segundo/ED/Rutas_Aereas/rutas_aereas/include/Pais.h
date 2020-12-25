/**
  * @file Pais.h
  * @brief Fichero con la definición e implementación de la clase Pais
  *
  * Permite el trabajo con objetos de la misma clase
  * 
  * @see Punto
  * @see Paises
  *
  */

#ifndef _PAIS_
#define _PAIS_

#include "Punto.h"

/**
 * @class Pais
 * 
 * @brief Permite y facilita el trabajo con los conjuntos de datos que forman un pais (bandera, nombre y localización)
 * 
 * @see Punto
 * 
 * @see Paises
 * 
 */
class Pais{
  private:

    /**
     * @brief Punto en el que se encuentra el Pais
     * 
     */
    Punto p;

    /**
     * @brief Nombre del Pais
     * 
     */
    string pais;

    /**
     * @brief Nombre del archivo que contiene la bandera del Pais
     * 
     */
    string bandera;
    
  public:

    /**
     * @brief Constructor por defecto
     * 
     */
    Pais(){}

    /**
     * @brief Consultor del Punto
     * 
     * @return Devuelve el Punto asociado al Pais
     */
    Punto GetPunto()const {
        return p;
    }

    /**
     * @brief Consultor del nombre del Pais
     * 
     * @return Devuelve un string con el nombre del Pais
     */
    string GetPais()const {
        return pais;
    }

    /**
     * @brief Consultor de la bandera del Pais
     * 
     * @return Devuelve un string con el nombre del archivo de la bandera del Pais
     */
    string GetBandera()const {
        return bandera;
    }
    
    /**
     * @brief Comparación de inferioridad
     * 
     * @param P Pais a comparar
     * @return true Si el nombre del Pais this es menor al nombre del Pais P
     * @return false Si el nombre del Pais this es mayor al nombre del Pais P
     */
    bool operator<(const Pais &P)const{
	    return pais<P.pais;
    }

    /**
		 * @brief Comparativa de igualdad
		 * 
		 * @param P Pais a comparar
		 * @return true Si el Pais tiene el mismo nombre
		 * @return false Si el nombre del Pais es distinto
		 */
    bool operator==(const Pais &P)const{
	    return pais==P.pais;
    }

    /**
		 * @brief Comparativa de igualdad
		 * 
		 * @param P Punto a comparar
		 * @return true Si el Pais se encuentra en la misma posición que P
		 * @return false Si la localización del Pais es distinta a P
		 */
    bool operator==(const Punto &P)const{
	    return p==P;
    }

    /**
		 * @brief Operador de entrada
		 * 
		 * @param is Flujo de entrada desde el que se van a leer los datos
		 * @param P Objeto de la clase Pais en el que se introducen los datos leidos
		 * @return Devuelve un flujo de entrada, permitiendo la concatenación de entradas
		 */
    friend istream & operator>>(istream & is, Pais & P){
      double lat,lng;

    	is>>lat>>lng>>P.pais>>P.bandera;

    	P.p=Punto(lat,lng,' ');
    	return is;
    }

    /**
		 * @brief Operador de salida
		 * 
		 * @param os Flujo de salida
		 * @param P Objeto de la clase Pais del que se van a leer los datos
		 * @return Devuelve un flujo de salida, permitiendo la concatenación de salidas
		 */
    friend ostream & operator<<(ostream & os, const Pais &P) {
	    os<<P.p<<" "<<P.pais<<" "<<P.bandera<<endl;
	    return os;
    }

};

#endif