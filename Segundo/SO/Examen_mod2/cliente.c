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

int main(int argc, char*argv[]) {

    if (argc != 3) {
        printf("\nError en el número de argumentos\nLos argumentos son <num_clientes> <directorio>\n");
        exit(0);
    }

    int fifo_escritura;

    if ((fifo_escritura = open("/tmp/fifo_entrada", O_WRONLY, S_IWUSR)) < 0) {
        perror("\nError en la apertura del fifo de escritura desde el cliente");
        exit(-1);
    }

    pid_t pid;

    for (int i = 0; i < atoi(argv[1]) && pid != 0; i++) {
        if ((pid = fork()) < 0) {
            perror("\nError durante la creacion de hijos");
            exit(-1);
        }
    }

    if (pid != 0) {
        wait(NULL); //Esperamos a que los hijos finalicen su ejecución, pero sin recoger su estado de salida
    } else {
        pid = getpid();
        DIR *directorio;
        struct dirent *archivo;
        struct stat atributos_directorio;

        if (stat(argv[2], &atributos_directorio) < 0) {
            perror("\nError obteniendo los atributos del directorio");
            exit(-1);
        }
        if ((directorio = opendir(argv[2])) == NULL) {
            perror("\nError abriendo el directorio");
            exit(-1);
        }

        archivo = readdir(directorio);

        while(S_ISREG(archivo->d_type) != 0) {

            if (archivo == NULL) {
                printf("\nLlegado al final del directorio, saliendo");
                exit(0);
            }

            archivo = readdir(directorio);

        }

        struct stat atributos_archivo;

        if (stat(archivo->d_name, &atributos_archivo) < 0) {
            perror("\nError abriendo el archivo regular desde el cliente");
            exit(-1);
        }

        time_t t;
        srand((unsigned) time(&t));
        int aleatorio = rand() % 50;
        char operacion;
        
        if (aleatorio >=25) {
            operacion = '*';
        } else {
            operacion = '+';
        }

        char escritura[300];
        sprintf(escritura, "%d\n%ld\n%d\n%ld\n", pid, atributos_directorio.st_ino, operacion, atributos_archivo.st_size);


        write(fifo_escritura, escritura, strlen(escritura));


        char vuelta[256];
        sprintf(vuelta, "/tmp/fifo_vuelta_%d", pid);

        mkfifo(vuelta, S_IRUSR|S_IWUSR | S_IRGRP | S_IROTH);

        int fd_vuelta;

        if ((fd_vuelta = open(vuelta, O_RDONLY, S_IRUSR | S_IRGRP)) < 0) {
            perror("\nError en la apertura del fifo de vuelta desde el cliente");
            exit(-1);
        }

        char resultado[50];

        if (read(fd_vuelta, resultado, 50) < 0) {
            perror("\nError leyendo datos del fifo de vuelta desde el cliente");
            exit(-1);
        }

        write(STDOUT_FILENO, resultado, strlen(resultado));


    }

    exit(0);
    
}