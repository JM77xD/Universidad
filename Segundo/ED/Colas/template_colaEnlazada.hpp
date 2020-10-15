#ifndef COLA_ENLAZADA_H_
#define COLA_ENLAZADA_H_

#include <cassert>

/**
 * @brief Estructura para una celda enlazada
 */
template<typename base>
struct CeldaCola {
    base elemento;  /** @param elemento Valor de tipo primitivo que contendrá la celda */
    CeldaCola *sig; /** @param sig Puntro que apunta a la siguiente celda */
};

/**
 * @brief ColaEnlazada formada a partir de listas enlazadas
 */
template<class T>
class ColaEnlazada {
    private:
        CeldaCola<T>    *primera,   /** @param primera Puntero a la primera celda de la cola */
                        *ultima;    /** @param ultima Puntero a la última celda de la cola */
    public:
    
        /**
         * @brief constructor por defecto
         */
        ColaEnlazada() {
            primera = ultima = 0;
        }

        /**
         * @brief constructor de copia
         * @param c ColaEnlazada a copiar
         */
        ColaEnlazada(const ColaEnlazada &c) {
            this->copiar(c);
        }

        /**
         * @brief destructor de la Clase
         */
        ~ColaEnlazada() {
            this->liberar();
        }

        /**
         * @brief sobrecarga del operador de asignación (=)
         * @param c ColaEnlazada a asignar a this
         * @return Devuelve un elemento de la clase ColaEnlazada
         * @pre c != this
         */
        ColaEnlazada & operator=(const ColaEnlazada &c) {
            if(this != &c) {
                this->liberar();
                this->copiar(c);
            }
            return *this;
        }

        /**
         * @brief controla si la cola está vacía
         * @return Devuelve true si la cola está vacía y false en caso contrario
         */
        bool vacia() const {
            return (primera == 0);
        }

        /**
         * @brief sobrecarga del operador += para añadir elementos a la cola
         * @param p elemento a añadir a la cola
         * @pre p tiene que ser del mismo tipo que el resto de elementos de la cola
         */
        void operator+=(const T &p) {
            CeldaCola<T> *nueva = new CeldaCola<T>;
            nueva->elemento = p;
            nueva->sig = 0;
            if (primera == 0)
                primera = ultima = nueva;
            else {
                ultima->sig = nueva;
                ultima = nueva;
            }
        }

        /**
         * @brief sobrecarga del operador --, quita un elemento de la cola
         * @pre Es necesario que haya algún elemento en la cola
         */
        void operator--() {
            assert(primera!=0);
            CeldaCola<T> *aux;
            aux = primera;
            primera = primera->sig;
            delete aux;
            if (primera == 0) 
                ultima = 0;
        }

        /**
         * @brief Devuelve el primer elemento en la cola
         * @return Devuelve elemento de la clase que elijamos para la cola
         * @pre La cola no puede estar vacía
         */
        T frente() const {
            assert(!vacia());
            return primera->elemento;
        }
        

    private:

        /**
         * @brief libera el espacio ocupado por la cola
         */
        void liberar() {
            CeldaCola<T> *aux;
            while (primera != 0) {
                aux = primera;
                primera = primera->sig;
                delete aux;
            }
            ultima = 0;
        }

        /**
         * @brief copia la cola pasada por parámetros
         * @param c cola a copiar
         */
        void copiar(const ColaEnlazada &c) {
            if (c.primera == 0)
                primera = ultima = 0;
            else {
                primera = new CeldaCola<T>;
                primera->elemento = c.primera->elemento;
                ultima = primera;
                CeldaCola<T> *aux = c.primera;

                while (aux->sig != 0) {
                    aux = aux->sig;
                    ultima->sig = new CeldaCola<T>;
                    ultima = ultima->sig;
                    ultima->elemento = aux->elemento;
                }

                ultima->sig = 0;
            }
        }
};

#endif