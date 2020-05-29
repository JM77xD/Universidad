#include <iostream>
#include "columnas.h"
#include "fila.h"
#include "matriz2d.h"

using namespace std;

int main() {
    int filas, col;                                     //Preguntamos al usuario por el numero de columnas y filas
    cout << "Introduzca el num de filas y columnas: ";
    cin >> filas;
    cin >> col;

    if (filas < 0 || col < 0) {
        cout << "\nValores no válidos";
        return 0;
    }

    Matriz2D MatrizOriginal(filas, col);            //Creamos la matriz

    cout << "\nMatriz original:\n";                 //Mostramos la matriz
    MatrizOriginal.mostrar();

    Matriz2D *copiaOriginal = MatrizOriginal.copiarMatriz();            //Creamos una copia de la matriz
    cout << "\nMatriz copiada de la original:\n";
    copiaOriginal->mostrar();
    delete copiaOriginal;               //Borramos la matriz copia

    
    int filaI, filaF, colI, colF;
    cout << "\nDe que fila a que fila desea extraer la submatriz(x y)? ";
    cin >> filaI >> filaF;

    cout << "\nDe que columna a que columna desea extraer la submatriz(x y)? ";
    cin >> colI >> colF;

    Matriz2D *subMatriz = MatrizOriginal.extraerSubmatriz(filaI-1, filaF-1, colI-1, colF-1);      //Obtenemos una submatriz de la matriz
    cout << "\nSubmatriz desde el (" << filaI << ", " << colI << ") al (" << filaF << ", " << colF << "):\n";
    subMatriz->mostrar();
    delete subMatriz;                   //Borramos la submatriz

    MatrizOriginal.eliminarFila(0);                             //Quitamos una fila a la matriz original
    cout << "\nMatriz original sin la primera fila:\n";
    MatrizOriginal.mostrar();

    MatrizOriginal.eliminarColumna(1);                          //Quitamos una columna a la matriz original
    cout << "\nMatriz original sin primera fila y sin primera columna:\n";
    MatrizOriginal.mostrar();
    
               
    
}