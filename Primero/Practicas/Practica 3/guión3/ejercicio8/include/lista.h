#ifndef lista_h
#define lista_h

class Lista{
    private:
        Celda *contenido;       //Puntero a la primera celda
    public:
        Lista() {               //Constructor por defecto que no crea ninguna celda
            this->contenido = 0;
        }

        Lista(int numeroCeldas) {           //Constructor si se proporciona el numero de celdas, que las inicializa todas a 0
            this->contenido = new Celda;
            Celda *p = this->contenido;
            for (int i = 1; i < numeroCeldas; i++) {
                p->crearCelda();
                p = p->SiguienteCelda();
            }
            p = 0;
            delete p;
        }

        Lista(int numeroCeldas, double valores[]) {         //Constructor que permite un vector para añadir los valores
            this->contenido = new Celda;        //Crea la primera celda
            Celda *p = this->contenido;         //Puntero auxiliar 
            p->insertarValor(valores[0]);       //Inserta el primer valor
            for (int i = 1; i < numeroCeldas; i++) {    //Repetimos tantas veces como celdas haya
                p->crearCelda();
                p = p->SiguienteCelda();
                p->insertarValor(valores[i]);
            }
            p = 0;          //Borramos puntero auxiliar
            delete p;
        }

        void mostrarLista();

        void mostrarInverso();

        int obtenerLongitud();

        void eliminarFinal();

        void agregarFinal(double valor);

        void agregarInicio(double valor);

        Celda *obtenerCelda(int posicion);

        void agregarPosicion(int posicion, double valor);

        void liberarEspacio();
};

#endif