#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

using namespace std;

class BigInt {
    private:
        int *p;             //Puntero de enteros

        int numDigitos;     //Contador del numero de digitos
        
        friend ostream& operator<<(ostream &o, const BigInt &mostrar);  //Hacemos que la sobrecarga del operador << sea amigo de la clase
    public:
        BigInt();

        BigInt(string numeroGrande);

        void agregarValores();         //Método para inicializar desde 0 un objeto BigInt

        ~BigInt();

        BigInt(const BigInt &copiar);

        BigInt operator+(const BigInt &otro) const;        //Sobrecarga del operador suma, para tener un método que sume 2 BigInts
};

#endif