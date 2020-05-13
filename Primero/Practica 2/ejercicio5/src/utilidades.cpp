bool InsertarCadena(char cadena[], char insertar[], int tamanioCad, int tamanioIns, int posicion, char cadenaCompleta[]) {
    int contador = 0, conteo = 0;
    if (posicion <= tamanioCad) {       //Podremos realizar la inserción si la posicion en la que se va a insertar es menor o igual que el tamaño de la cadena base   
        for (int i = 0; i < posicion; i++) {            //Insertamos la base hasta llegar a la posición indicada
            cadenaCompleta[i] = cadena[i];
            conteo = i;             //Guardamos la posicion en la que nos quedamos de la base en esta variable
        }
        for (int i = posicion; posicion <= i && i <= posicion + tamanioIns; i++) {  //Insertamos la cadena a insertar desde la posicion hasta el final de la misma
            cadenaCompleta[i] = insertar[contador];
            contador++;         //Usamos esta variable para insertar la cadena a insertar
        }
        for (int i = posicion + tamanioIns; i < tamanioIns + tamanioCad; i++) {     //Insertamos el resto de la base
            cadenaCompleta[i] = cadena[conteo];
            conteo++;
        }
        return true;        //Devolvemos que se ha podido insertar
    } else return false;
}