#ifndef PILA_DINAMICA_H_
#define PILA_DINAMICA_H_

typedef char base;  /**<-tipo de dato que se usará en la pila*/
const int TAM = 10; /** <-numero de elementos que admite la pila de base */

/**
 * @brief Pila tipo LIFO con un tamaño dinámico
 */
class PilaDinamica {
    private:

        base *datos;        /** <-Puntero en el que se almacenarán los datos de la pila */

        int reservados;     /**<-contador del tamaño reservado en un instante de tiempo*/

        int nElem;          /**<-contador del numero de elementos en un instante de tiempo que se encuentran en la pila*/
    
    public:

        /**
         * @brief constructor por defecto, que también admite un parámetro
         * @param tam Tamaño que se le desea dar a la pila
         */
        PilaDinamica(int tam = TAM);

        /**
         * @brief constructor de copia
         * @param p elemento de la clase PilaDinamica que se desea copiar
         */
        PilaDinamica(const PilaDinamica &p);

        /**
         * @brief destructor de la PilaDinamica
         */
        ~PilaDinamica();

        /**
         * @brief sobrecarga del operador =
         * @param p Pila sobre la que actua el operador
         * @return Devuelve una Pila exactamente igual a p
         */
        PilaDinamica & operator=(const PilaDinamica &p);
        
        /**
         * @return Devuelve true si la pila está vacía
         */
        bool vacia() const;

        /**
         * @brief Inserta un elemento en la pila, sobrecarga del operador +=
         * @param p elemento a insertar en la pila
         */
        void operator+=(const base &p);

        /**
         * @brief quita el ultimo elemento de la pila, sobrecarga del operador --
         */
        void operator--();

        /**
         * @brief obtiene el último elemento de la pila
         * @return Devuelve el último elemento de la pila
         */
        base & tope();

        /**
         * @brief obtiene el último elemento de la pila como const
         * @return Devuelve el último elemento de la pila como const
         */
        const base & tope() const;

    private:

        /**
         * @brief método auxiliar para copiar una pila
         * @param p pila a copiar
         */
        void copiar(const PilaDinamica &p);

        /**
         * @brief método auxiliar que cambia el tamaño de la pila
         * @param n tamaño que se le desea dar a la pila
         */
        void resize(int n);

        /**
         * @brief método auxiliar que libera espacio de la pila
         */
        void liberar();

        /**
         * @brief método auxiliar que reserva el espacio solicitado para la pila
         * @param n espacio a reservar en la pila
         */
        void reservar(int n);

};

#endif