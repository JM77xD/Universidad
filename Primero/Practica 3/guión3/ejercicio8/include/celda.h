#ifndef celda_h
#define celda_h

using namespace std;

class Celda {
    private:
        double info;            //Valor de la celda
        Celda *sig;             //Puntero a la celda siguiente
    public:
        Celda() {               //Constructor por defecto de la celda
            info = 0;
            sig = 0;
        }

        Celda *SiguienteCelda() {       //Devuelve el puntero a la celda siguiente
            return this->sig;
        }

        void insertarValor(double valor) {      //Permite cambiar el valor de la celda
            info = valor;
        }

        void crearCelda() {                     //Crea una celda nueva celda en la posicion siguiente
            sig = new Celda;
        }

        void mostrar() {                        //Muestra el valor de la celda
            cout << info << " ";
        }

        void cambiarSiguiente(Celda *nueva) {       //Cambia la celda siguiente
            sig = nueva;
        }
        
};

#endif