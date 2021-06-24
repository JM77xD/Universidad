#include <iostream>

using namespace std;

int main() {
    const int TAM_MAX = 100;
    int cadena_ent[TAM_MAX], cadena_creciente[TAM_MAX], utiles, longitud_cadena, longitud_creciente = 0, posicion, contador;
    cout << "¿Cuantos numeros desea introducir? ";
    cin >> utiles;
    if (utiles > TAM_MAX || utiles < 1) {
        cout <<"\nValor erróneo, introduzca un numero entre 1 y 100\n";
        return 0;
    }
    for (int i = 0; i < utiles; i++) {
        cin >> cadena_ent[i];
    }
    for (int i = 0; i + 1 < utiles; i++) {
        if (cadena_ent[i] < cadena_ent[i+1]) {
            contador = i;
            longitud_cadena = 0;
            while (cadena_ent[contador] < cadena_ent[contador+1]) {
                contador++;
                longitud_cadena++;
            }
            if (longitud_cadena > longitud_creciente) {
                longitud_creciente = longitud_cadena;
                posicion = i;
            }
            i = contador;
        }
    }
    for (int i = 0; i <= longitud_creciente; i++) {
        cadena_creciente[i] = cadena_ent[posicion];
        posicion++;
    }
    cout << "\nEl intervalo monotono creciente más largo es:\n";
    for (int i = 0; i <= longitud_creciente; i++) {
        cout << cadena_creciente[i] << " ";
    }
    cout << endl;

}