#ifndef PILA_TEMPLATE_H_
#define PILA_TEMPLATE_H_

#include <cassert>
const int TAM = 10; /** @param TAM <-numero de elementos que admite la pila de base */

/**
 * @brief Template para pila tipo LIFO con un tamaño dinámico adaptada a cualquier tipo de variable primitivo
 */
template<class base> class PilaTemplate {
    private:

        base *datos;        /** @param datos <-Puntero en el que se almacenarán los datos de la pila */

        int reservados;     /** @param reservados <-contador del tamaño reservado en un instante de tiempo*/

        int nElem;          /** @param nElem <-contador del numero de elementos en un instante de tiempo que se encuentran en la pila*/
    
    public:

        /**
         * @brief constructor por defecto, que también admite un parámetro
         * @param tam Tamaño que se le desea dar a la pila
         */
        PilaTemplate(int tam = TAM) {
            assert(tam > 0);
            this->nElem = 0;
            this->reservar(tam);
        }

        /**
         * @brief constructor de copia
         * @param p elemento de la clase PilaTemplate que se desea copiar
         */
        PilaTemplate(const PilaTemplate &p)  {
            assert(p.datos);
            this->nElem = p.nElem;
            this->reservados = p.reservados;
            this->datos = new base[this->reservados];
            for (int i = 0; i < this->nElem; i++) {
                *(this->datos + i) = p.datos[i];
            }
        }

        /**
         * @brief destructor de la PilaTemplate
         */
        ~PilaTemplate() {
            this->liberar();
        }

        /**
         * @brief sobrecarga del operador =
         * @param p Pila sobre la que actua el operador
         * @return Devuelve una Pila exactamente igual a p
         */
        PilaTemplate & operator=(const PilaTemplate &p) {
            if (this != &p) {
                this->liberar()
                this->copiar(p);
            }
            return *this;
        }
        
        /**
         * @return Devuelve true si la pila está vacía
         */
        bool vacia() const {
            return (nElem == 0);
        }

        /**
         * @brief Inserta un elemento en la pila, sobrecarga del operador +=
         * @param p elemento a insertar en la pila
         */
        void operator+=(const base &p) {
            if (nElem == reservados) this->resize(reservados*2);
            *(this->datos + this->nElem) = p;
            this->nElem++;
        }

        /**
         * @brief quita el ultimo elemento de la pila, sobrecarga del operador --
         */
        void operator--() {
            assert(this->nElem > 0);
            nElem--;
            if (nElem < reservados/4) this->resize(reservados/2);
        }

        /**
         * @brief obtiene el último elemento de la pila
         * @return Devuelve el último elemento de la pila
         */
        base & tope() {
            assert(this->nElem > 0);
            return *(this->datos + nElem - 1);
        }

        /**
         * @brief obtiene el último elemento de la pila como const
         * @return Devuelve el último elemento de la pila como const
         */
        const base & tope() const {
            assert(this->nElem > 0);
            return *(this->datos + nElem - 1);
        }

    private:

        /**
         * @brief método auxiliar para copiar una pila
         * @param p pila a copiar
         */
        void copiar(const PilaTemplate &p) {
            assert(p.datos);
            if (this->reservados != p.reservados) this->reservar(p.reservados);
            this->nElem = p.nElem;
            for (int i = 0; i < this->nElem; i++) {
                *(this->datos + i) = p.datos[i];
            }
        }

        /**
         * @brief método auxiliar que cambia el tamaño de la pila
         * @param n tamaño que se le desea dar a la pila
         */
        void resize(int n) {
            assert(n > 0);
            base *aux = this->datos;
            this->reservados = n;
            this->datos = new base[n];
            for (int i = 0; i < this->nElem; i++) {
                *(this->datos + i) = *(aux + i);
            }
            delete [] aux;
        }

        /**
         * @brief método auxiliar que libera espacio de la pila
         */
        void liberar() {
            delete [] this->datos;
            datos = 0;
            this->reservados = 0;
            this->nElem = 0;
        }

        /**
         * @brief método auxiliar que reserva el espacio solicitado para la pila
         * @param n espacio a reservar en la pila
         */
        void reservar(int n) {
            assert(n > 0);
            this->reservados = n;
            this->datos = new base[n];
        }

};

#endif