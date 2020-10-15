#ifndef COLA_DINAMICA_H_
#define COLA_DINAMICA_H_

#include <cassert>

const int TAM_BASE = 10;    /** @param TAM_BASE tamaño que tiene la cola por defecto */

/**
 * @brief Cola FIFO dinámica de tipo circular, adaptada a cualquier tipo de variable primitiva
 */
template<class base>
class ColaCircular {
    private:
        base *datos;    /** @param datos puntero a la cola*/
        int reservados; /** @param reservados espacios de la memoria reservada*/
        int nElem;      /** @param nElem número de elementos en la cola en un instante de tiempo*/
        int anterior,   /** @param anterior índice del primer elemento a retirar de la cola*/
            posterior;  /** @param posterior indice del siguiente elemento a insertar en la cola*/

    public:
    
        /**
         * @brief constructor por defecto con sobrecarga de un parámetro
         * @param tam Tamaño a reservar para la cola (por defecto 10)
         */
        ColaCircular(int tam = TAM_BASE) {
            this->reservar(tam);
            anterior = posterior = nElem = 0;
        }

        /**
         * @brief constructor de copia
         * @param c Cola a copiar
         */
        ColaCircular(const ColaCircular &c) {
            this->reservar(c.reservados);
            this->copiar(c);
        }

        /**
         * @brief destructor de la Clase
         */
        ~ColaCircular() {
            this->liberar();
        }

        /**
         * @brief sobrecarga del operador de asignación (=)
         * @param c Cola a asignar a this
         * @return Devuelve un elemento de la clase ColaCircular
         * @pre c != this
         */
        ColaCircular & operator=(const ColaCircular &c) {
            if(this != &c) {
                this->liberar();
                this->reservar(c.reservados);
                this->copiar(c);
            }
            return *this;
        }

        /**
         * @brief controla si la cola está vacía
         * @return Devuelve true si la cola está vacía y false en caso contrario
         */
        bool vacia() const {
            return (nElem == 0);
        }

        /**
         * @brief sobrecarga del operador += para añadir elementos a la cola
         * @param p elemento a añadir a la cola
         * @pre p tiene que ser del mismo tipo que el resto de elementos de la cola
         */
        void operator+=(const base &p) {
            if (nElem == reservados)
                this->redimensionar(2*reservados);
            *(this->datos + posterior) = p;
            posterior = (posterior + 1)%reservados;
            nElem++;
        }

        /**
         * @brief sobrecarga del operador --, quita un elemento de la cola
         * @pre Es necesario que haya algún elemento en la cola
         */
        void operator--() {
            assert(!vacia());
            anterior = (anterior + 1)%reservados;
            nElem--;
            if (nElem < reservados/4)
                this->redimensionar(reservados/2);
        }

        /**
         * @brief Devuelve el primer elemento en la cola
         * @return Devuelve elemento de la clase que elijamos para la cola
         * @pre La cola no puede estar vacía
         */
        base frente() {
            assert(!vacia());
            return *(this->datos + anterior);
        }
        

    private:

        /**
         * @brief reserva espacio de memoria dinámico para la cola
         * @param n tamaño a reservar para la cola
         * @pre n>0
         */
        void reservar(const int n) {
            assert(n>0);
            this->datos = new base[n];
            this->reservados = n;
        }

        /**
         * @brief libera el espacio ocupado por la cola
         */
        void liberar() {
            delete [] this->datos;
            datos = 0;
            reservados = nElem = anterior = posterior = 0;
        }

        /**
         * @brief copia la cola pasada por parámetros
         * @param c cola a copiar
         * @pre Es necesario haber reservado el espacio antes
         */
        void copiar(const ColaCircular &c) {
            assert(this->reservados == c.reservados);
            for (int i = c.anterior; i != c.posterior; i = (i+1)%reservados)
                *(this->datos + i) = c.datos[i];
            anterior = c.anterior;
            posterior = c.posterior;
            nElem = c.nElem;
        }

        /**
         * @brief redimensiona la cola
         * @param n Tamaño al que redimensionar la cola
         * @pre El temaño a redimensionar tiene que ser mayor que nElem y que 0
         */
        void redimensionar(const int n) {
            assert(n>0 && n>nElem);
            base * aux = datos;
            int tam_aux = reservados;
            this->reservar(n);
            for (int i = 0; i <nElem; i++)
                *(this->datos + i) = aux[(anterior+i)%tam_aux];
            anterior = 0;
            posterior = nElem;
            delete [] aux;
        }
};

#endif