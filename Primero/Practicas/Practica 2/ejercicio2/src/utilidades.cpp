#include "utilidades.h"

void combinarSuma(Valor serie1[], Valor serie2[], int tamanioSerie1, int tamanioSerie2, Valor suma[], int &total) {
    total = tamanioSerie1;
    for (int i = 0; i < tamanioSerie1; i++) suma[i].insertar(serie1[i].valorFila(), serie1[i].ValorColumna(), serie1[i].ValorValor());  //Insertamos los valores de los elementos de la serie1 en la suma
    for (int i = 0; i < tamanioSerie2; i++) {
        bool coincide = false;
        for (int j = 0; j < tamanioSerie1; j++) {
            if (serie1[j].valorFila() == serie2[i].valorFila() && serie1[j].ValorColumna() == serie2[i].ValorColumna()) {           //Si algun elemento coincide
                double nuevovalor = serie1[j].ValorValor() + serie2[i].ValorValor();            //Calculamos el equivalente de la suma de sus valores
                suma[j].insertar(serie1[j].valorFila(), serie1[j].ValorColumna(), nuevovalor);  //Lo insertamos sustituyendo al elemento de la suma que tenía la misma fila y columna
                coincide = true;
            }
        }
        if (!coincide) {        //Si el elemento no coincide, lo insertamos en la serie suma
            suma[total].insertar(serie2[i].valorFila(), serie2[i].ValorColumna(), serie2[i].ValorValor());
            total++;
        }
    }
}