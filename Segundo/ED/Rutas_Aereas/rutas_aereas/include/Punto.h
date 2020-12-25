
/**
  * @file Punto.h
  * @brief Fichero con la definición e implementación de la clase Punto
  *
  * Permite el trabajo con un Punto con 2 coordenadas
  * 
  * @see Ruta
  * @see Pais
  *
  */
#ifndef _PUNTO_

#define _PUNTO_

/**
 * @class Punto
 * 
 * @brief Permite y facilita el manejo de un punto asociado a un mapa, es decir, una latitud y una longitud 
 * 
 */
class Punto {
    
    private:
        
        /**
         * @brief Valor de la latitud
         * 
         */
        double latitud;

        /**
         * @brief Valor de la longitud
         * 
         */
        double longitud;

        /**
         * @brief Separador
         * 
         */
        char separador;

    public:
        
        /**
         * @brief Consultor del valor de la latitud
         * 
         * @return Devuelve la latitud del Punto 
         */
        double GetLatitud() const {
            return latitud;
        }

        /**
         * @brief Consultor del valor de la longitud
         * 
         * @return Devuelve la longitud del Punto 
         */
        double GetLongitud() const {
            return longitud;
        }

        /**
         * @brief Constructor por defecto
         * 
         */
        Punto(){}

        /**
         * @brief Constructor a partir de la latitud, longitud y un separador de tipo char
         * 
         * @param lat Latitud del Punto
         * @param lon Longitud del Punto
         * @param sep Separador
         */
        Punto(double lat, double lon, char sep) {
            latitud = lat;
            longitud = lon;
            separador = sep;
        }

        /**
         * @brief Constructor de copia
         * 
         * @param p Punto que copiar
         */
        Punto(const Punto &p) {
            latitud = p.latitud;
            longitud = p.longitud;
            separador = p.separador;
        }

        /**
         * @brief Operador de igualdad
         * 
         * @param p Punto con el que comparar
         * @return true Si los elementos de ambos objetos coinciden
         * @return false Si uno (o varios) elementos de los objetos no coinciden
         */
        bool operator==(const Punto & p) const {
            return (latitud == p.latitud && longitud == p.longitud && separador == p.separador);
        }

        /**
         * @brief Comparación de inferioridad
         * 
         * @param p Punto con el que comparar
         * @return true Si la latitud de this es menor a la de P
         * @return false Si la latitud de this es mayor o igual a la de p
         */
        bool operator<(const Punto & p) const {
            return (latitud < p.latitud);
        }

        /**
         * @brief Comparación de superioridad
         * 
         * @param p Punto con el que comparar
         * @return true Si la latitud de this es mayor a la de P
         * @return false Si la latitud de this es menor o igual a la de p
         */
        bool operator>(const Punto & p) const {
            return (latitud > p.latitud);
        }

        /**
		 * @brief Operador de salida
		 * 
		 * @param os Flujo de salida por el que se van a sacar los datos
		 * @param p Objeto de la clase Punto del que se van a leer los datos
		 * @return Devuelve un flujo de salida, permitiendo la concatenación de salidas
		 */
        friend ostream & operator<<(ostream &os, const Punto &p) {
            os << "(" << p.latitud << ", " << p.longitud << ")" << p.separador;
            return os;
        }

        /**
		 * @brief Operador de entrada
		 * 
		 * @param is Flujo de entrada desde el que se van a leer los datos
		 * @param p Objeto de la clase Punto en el que se introducen los datos leidos
		 * @return Devuelve un flujo de entrada, permitiendo la concatenación de entradas
		 */
        friend istream & operator>>(istream &is, Punto &p) {
            is.ignore( 1000 , '(' );
            is >> p.latitud;
            is.ignore( 1000 , ',');
            is >> p.longitud;
            is.ignore( 1000 , ')' );
            p.separador = ' ';
            return is;
        }

};

#endif