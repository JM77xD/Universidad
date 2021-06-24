#ifndef columnas_h
#define columnas_h

struct Columnas {
    double numero;                              //Valor de la matriz en esa posición
    Columnas *sigC;                             //Puntero que apunta a la siguiente columna
};

#endif