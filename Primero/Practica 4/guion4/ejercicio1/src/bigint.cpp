#include <iostream>
#include <string>
#include "bigint.h"

using namespace std;


BigInt::~BigInt() {         //Destructor
    delete [] p;        //Borramos el array
}

BigInt::BigInt(const BigInt &copiar) {      //Constructor de copia
    this->numDigitos = copiar.numDigitos;       //Se iguala el número de dígitos
    this->p = new int[numDigitos];      //Se crea un nuevo array del tamaño especificado
    for (int i = 0; i < numDigitos; i++) this->p[i] = copiar.p[i];      //Se asigna valor a valor el del array a copiar al array copia
}

BigInt::BigInt(string numeroGrande) {       //Constructor una vez que proporcionamos un string (usado para la sobrecarga de la suma)
    numDigitos = numeroGrande.length();
    p = new int[numDigitos];        //Creamos un array de enteros del tamaño pedido por el usuario
    for (int i = 0; i < numDigitos; i++) *(p+i) = numeroGrande[i] - 48;//Asignamos cada numero al vector, restando 48 para que el valor en ASCII se corresponda al entero que representa
}

BigInt::BigInt() {      //Constructor por defecto
    p=new int[1];       //Creamos un array de tamaño 1
    *p = 0;             //Le asignamos el valor 0
    numDigitos=1;       //Tenemos 1 dígito, el 0
}

BigInt BigInt::operator+(const BigInt &otro) const {        //Sobrecarga del operador suma, para tener un método que sume 2 BigInts
    bool acarreo = false;                           //Booleano que define si hay acarreo o no
    int numero;                     //entero aux para determinar el numero
    string numeroGrande;            //String que vamos a usar para crear el BigInt
    if (this->numDigitos >= otro.numDigitos) {      //Si el primero es mayor que el segundo
        for (int i = 0; i < this->numDigitos; i++) {        //Usamos un for para recorrer el BigInt entero
            if (i < otro.numDigitos) {                  //Mientras que i sea menor que el tamaño del otro BigInt, incluimos a este en la suma
                numero = this->p[i] + otro.p[i];    //El aux es la suma de los valores
                if (acarreo) numero++;  //Si tenemos acarreo sumamos 1
                if (numero > 9) {       //Tenemos acarreo cuando el numero es mayor que 9
                    numero -= 10;       //Le restamos 10 al número
                    acarreo = true;     //Asignamos true al acarreo
                } else acarreo = false;     //Si el numero es menor o igual a 9, no hay acarreo
            } else {                    //Si i es mayor que la longitud del segundo BigInt, no lo incluimos en la suma
                numero = this->p[i];
                if (acarreo) numero++;
                if (numero > 9) {
                    numero -= 10;
                    acarreo = true;
                } else acarreo = false;    
            }
            numeroGrande += to_string(numero);  //Asignamos el numero al string, concatenando los dígitos
        }
    } else {            //Si el segundo es mayor que el primero, mismo procedimiento pero cambiando las condiciones de los for y los if
        for (int i = 0; i < otro.numDigitos; i++) {
            if (i < this->numDigitos) {
                numero = this->p[i] + otro.p[i];
                if (acarreo) numero++;
                if (numero > 9) {
                    numero -= 10;
                    acarreo = true;
                } else acarreo = false;  
            } else {
                numero = otro.p[i];
                if (acarreo) numero++;
                if (numero > 9) {
                    numero -= 10;
                    acarreo = true;
                } else acarreo = false;
            }
            numeroGrande += to_string(numero);
        }
    }
    if (acarreo) numeroGrande += to_string(1);     //Añadimos esto en caso de que haya habido acarreo en el último paso y tengamos que añadir un dígito más
    BigInt suma(numeroGrande);  //Creamos el BigInt con el string obtenido
    return suma;    //Devolvemos el BigInt
};


void BigInt::agregarValores() {         //Método para inicializar desde 0 un objeto BigInt
    cout << "\nIntroduzca el número: ";     //Introducimos el número
    string numero;                          //Creamos un string para leer el numero
    getline(cin, numero);
    delete [] p;       //Borramos el 0 que le habíamos asignado a p
    numDigitos = numero.length();
    for (int i = 0; i < numDigitos/2; i++) swap(numero[i], numero[numDigitos-i-1]);     //Invertimos el string
    p = new int[numDigitos];        //Creamos un array de enteros del tamaño pedido por el usuario
    for (int i = 0; i < numDigitos; i++) {
        *(p+i) = numero[i] - 48;//Asignamos cada numero al vector de enteros, restandole 48, ya que es el valor que tiene el 0 en código ASCII
    }
};