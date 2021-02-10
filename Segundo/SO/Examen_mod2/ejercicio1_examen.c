#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/wait.h>
#include<time.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {    //Comprobación de argumentos
        printf("\nTiene que pasar un argumento <nombreArchivo>");
        exit(0);
    }

    struct stat atributos;

    if (lstat(argv[1], &atributos) < 0) {   //Analizamos los atributos del archivo
        perror("\nError al obtener los datos del archivo");
        exit(-1);
    }

    if (S_ISDIR(atributos.st_mode)) {   //Si es un directorio
        
        char buf[256];  //Buffer para meter la fecha ya con su formato
        struct timespec tiempo; //esto almacena el tiempo de última modificación en segundos

        tiempo = atributos.st_mtim; //Sacamos el tiempo de los atributos del archivo

        struct tm *timer = localtime(&tiempo.tv_sec);   //Convertimos en una estructura de tiempo

        strftime(buf, sizeof(buf), "%D %T", timer); //Le damos formato Fecha y hora
        
        printf("\nLa última vez que se modificó fue el %s\n", buf); //Lo sacamos por pantalla
    } else {
        printf("\nEl archivo %s no es un directorio\n", argv[1]);
    }
    exit(0);
}