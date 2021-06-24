void descomponer(int numero, int factores[], int &numeroFactores) {
    numeroFactores = 0;
    for (int primo = 2; primo <= numero; primo++) {     //Repetimos el bucle hasta que el numero primo sea igual que el numero
        int divisores = 0;                              //inicializamos el numero de divisores a 0
        for (int i = 1; i <= primo; i++) {              //Usamos este bucle para ver si la variable primo se trata de un numero primo
            if (primo%i == 0) divisores++;
        }
        if (divisores == 2) {                   //Si primo tiene 2 divisores, significa que solo puede ser dividido por 1 y por el propio numero, siendo entonces primo
            while (numero%primo == 0) {     //Mientras que el número sea divisible
                numero = numero/primo;      //Dividimos el número
                factores[numeroFactores] = primo;       //Añadimos el primo a la lista
                numeroFactores++;           //Sumamos 1 al numero de factores
            }
        }
    }
}