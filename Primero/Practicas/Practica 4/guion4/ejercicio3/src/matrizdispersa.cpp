#include <iostream>
#include "valor.h"
#include "matrizdispersa.h"

using namespace std;

MatrizDispersa MatrizDispersa::operator+(const MatrizDispersa &otra) const {
    MatrizDispersa copia(otra);         //Creamos una copia de una de las matrices
    bool coincide = false;  //Booleano para ver si algún valor coincide
    if (this->nfilas > otra.nfilas) copia.nfilas = this->nfilas;            //El número de filas y de columnas será el de la matriz que mayor número tenga
    if (this->ncolumnas > otra.ncolumnas) copia.ncolumnas = this->ncolumnas;
    for (int i = 0; i < this->nValores; i++) {
        coincide = false;
        for (int j = 0; j < otra.nValores; j++) {
                                    //Si algún valor coincide el num de filas y columnas, cambiamos el valor para que sea suma de los 2 valores
            if (this->valor[i].devolverFila() == otra.valor[j].devolverFila() && this->valor[i].devolverColumna() == otra.valor[j].devolverColumna()) {
                copia.valor[j].asignar(this->valor[i].devolverFila(), this->valor[i].devolverColumna(), this->valor[i].devolverValor() + otra.valor[j].devolverValor());
                coincide = true;
            }
        }
        if (!coincide) {        //Si no coincide con ningún valor
            Valor *auxiliar = copia.valor;
            copia.valor = new Valor[copia.nValores + 1];    //Agregamos un hueco en la matriz
            for (int j = 0; j < copia.nValores; j++) copia.valor[j] = auxiliar[j];      //Copiamos los valores tal y como los teníamos en el array original
            copia.valor[copia.nValores] = this->valor[i]; //insertamos el nuevo valor
            copia.nValores++;   //Aumentamos el numero de valores en 1
            delete [] auxiliar;     //Borramos el puntero auxiliar
        }
    }
    return copia;       //Devolvemos la matrizDispersa sumada
}

void MatrizDispersa::inicializarMatriz() {          //Método para incializar la matriz dispersa
    cout << "\nCuantos valores significativos desea introducir? ";      //Introducimos el numero de valores significativos que tiene la matriz
    cin >> nValores;
    while (nValores < 1) {      //Verificamos que el número de valores es válido
        cout << "\nNúmero de valores no válido, introduzca un número positivo mayor que 0\nCuantos valores desea introducir? ";
        cin >> nValores;
    }
    this->valor = new Valor[nValores];          //Creamos el array de valores significativos
    for (int i = 0; i < nValores; i++) {
        cout << "\nValor " << i+1 << ", introduzca los datos:\n";  //Vamos preguntando las filas, columnas y valores númericos de esos valores significativos
        int fila, columna;
        double avalor;
        cout << "fila(mayor que 0): ";
        cin >> fila;
        cout << "columna(mayor que 0): ";
        cin >> columna;
        cout << "valor: ";
        cin >> avalor;
        if (fila > nfilas) nfilas = fila;               //Si la fila o la columna son mayores que el numero de filas y columnas que tiene
        if (columna > ncolumnas) ncolumnas = columna;   //Nuestra matriz, actualizamos dichos valores
        this->valor[i].asignar(fila, columna, avalor);  //Asignamos los valores a su respectiva posición en el array
    }
}

MatrizDispersa::MatrizDispersa() {          //Constructor por defecto, inicializa todo a 0
    nfilas = 0;
    ncolumnas = 0;
    valor = 0;
    nValores = 0;
}

MatrizDispersa::~MatrizDispersa() {         //Destructor de la clase
    if (valor) {
        delete [] valor;    //Borra el array de valores
    }
}

MatrizDispersa::MatrizDispersa(int filas[], int columnas[], double valores[], int numValores) {
    nValores = numValores;
    this->valor = new Valor[nValores];
    for (int i = 0; i < numValores; i++) {
        if (filas[i] > nfilas) this->nfilas = filas[i];
        if (columnas[i] > ncolumnas) this->ncolumnas = columnas[i];
        this->valor[i].asignar(filas[i], columnas[i], valores[i]);
    }
}

MatrizDispersa::MatrizDispersa(const MatrizDispersa &copiar) {      //Constructor de copia de la clase
    this->ncolumnas = copiar.ncolumnas;     //Iguala los diferentes valores de las variables
    this->nfilas = copiar.nfilas;
    this->nValores = copiar.nValores;
    this->valor = new Valor[nValores];          //Crea el array de valores significativos
    for (int i = 0; i < nValores; i++) {
        this->valor[i] = copiar.valor[i];       //Va igualando los valores del array de valores significativos
    }
}