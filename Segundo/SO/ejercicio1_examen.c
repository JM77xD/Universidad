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

int main(int argc, char *argv[]) {
    if (argc != 3 ) {
        printf("Error en el número de argumentos\nLos argumentos son <directorio_entrada> <directorio_salida>\n");
    }

    DIR *directorio_in, *directorio_out;

    //Abrimos los directorios
    if ((directorio_in = opendir(argv[1])) == NULL) {
        perror("Error al abrir el primer directorio");
        exit(-1);
    }

    if ((directorio_out = opendir(argv[2])) == NULL) {
        mkdir(argv[2], S_IRWXU);
        if ((directorio_out = opendir(argv[2])) == NULL) {
            closedir(directorio_in);
            perror("Error al abrir el segundo directorio");
            exit(-1); 
        }

    }

    //Declaramos las variables para trabajar con los archivos
    struct dirent * archivo_act;
    struct stat atributos; 
    int copiados;
    char mensajeCopia[400], cadenaArch1[400], cadenaArch2[400];

    umask(S_IXUSR | S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH);

    if ((copiados = open("copiados.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0) { //Abrimos el copiados.txt para llevar la cuenta de los elementos que copiamos
        closedir(directorio_in);
        closedir(directorio_out);
        perror("Error abriendo copiados.txt\n");
        exit(-1);
    }

    while ((archivo_act = readdir(directorio_in)) != NULL) {

        sprintf(cadenaArch1, "%s%s", argv[1], archivo_act->d_name); //Obtenemos la ruta al primer archivo

        if (stat(cadenaArch1, &atributos) < 0) {//Si no logramos acceder a los atributos del archivo
            closedir(directorio_in);
            closedir(directorio_out);
            close(copiados);
            perror("\nError al obtener los datos del archivo\n");
            exit(-1);
        }

        if(S_ISREG(atributos.st_mode) && atributos.st_size > 1023) {    //Si es regular y su tamaño es >= 1KB

            sprintf(mensajeCopia, "%s|%o|%ld%s", archivo_act->d_name, atributos.st_mode, atributos.st_size, "\n");
            write(copiados, mensajeCopia, strlen(mensajeCopia));
            sprintf(cadenaArch2, "%s%s", argv[2], archivo_act->d_name);

            /*
            //Creamos un hijo que ejecute la operación de copia
            pid_t pid;
            if ((pid = fork()) < 0) {
                closedir(directorio_in);
                closedir(directorio_out);
                close(copiados);
                perror("\nError en el fork\n");
                exit(-1);
            }
            if (pid == 0) {
                execl("/bin/cp", "cp", cadenaArch1, cadenaArch2, (char *) NULL);
            } else {
                signal(SIGCHLD, SIG_IGN);
            }

            */

            int fd_in, fd_out;

            if ((fd_in = open(cadenaArch1, O_RDONLY | __O_LARGEFILE, S_IRWXU)) < 0) {
                perror("\nError en el open del primer archivo\n");
                exit(-1);
            }

            if ((fd_out = open(cadenaArch2, O_WRONLY | O_CREAT | O_TRUNC | __O_LARGEFILE, S_IRWXU)) < 0) {
                perror("\nError en el open del segundo archivo\n");
                exit(-1);
            }

            int leidos;
            char leyendo[100];

            while ((leidos = read(fd_in, leyendo, 100)) > 0) {
                write(fd_out, leyendo , leidos);
            }

            close(fd_in);
            close(fd_out);

        }
    }

    closedir(directorio_in);
    closedir(directorio_out);
    close(copiados);
    
}