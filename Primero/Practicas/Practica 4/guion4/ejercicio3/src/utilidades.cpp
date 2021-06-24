#include <iostream>
#include "matrizdispersa.h"
#include "valor.h"
#include "utilidades.h"

using namespace std;

ostream& operator<<(ostream &o, const MatrizDispersa &mostrar) {
    o << "\nLa Matriz dispersa consta de " << mostrar.nfilas << " filas, ";
    o << mostrar.ncolumnas << " columnas y " << mostrar.nValores << " valores significativos:\n";
    for (int i = 0; i < mostrar.nValores; i++) o << "(" << mostrar.valor[i].devolverFila() << ", " << mostrar.valor[i].devolverColumna() << ", " << mostrar.valor[i].devolverValor() << ")\t";
    return o;
}