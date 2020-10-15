#ifndef PILA_ESTATICA_H_
#define PILA_ESTATICA_H_

typedef char base;  /**<-tipo de dato que se usará en la pila*/
const int TAM = 500; /** <-numero de elementos que admite la pila */

/**
 * @brief Pila tipo LIFO con un tamaño limitado, admite TAM numero de elementos
 */
class PilaEstatica {
    private:

        base datos[TAM];    /** <-vector para almacenar los datos de la pila */

        int nElem;          /**<-contador del numero de elementos en un instante de tiempo que se encuentran en la pila*/
    
    public:

        /**
         * @brief constructor por defecto
         */
        PilaEstatica();

        /**
         * @brief constructor de copia
         * @param p elemento de la clase PilaEstatica que se desea copiar
         */
        PilaEstatica(const PilaEstatica &p);

        /**
         * @brief Establece el destructor al destructor por defecto
         */
        ~PilaEstatica() = default;

        /**
         * @brief sobrecarga del operador =
         * @param p Pila sobre la que actua el operador
         * @return Devuelve una Pila exactamente igual a p
         */
        PilaEstatica & operator=(const PilaEstatica &p);
        
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
         * @brief método privado para copiar una pila
         * @param p pila a copiar
         */
        void copiar(const PilaEstatica &p);

};

#endif