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

void pickZombies(int i) {
    wait(NULL);
}


int main(int argc, char argv[]) {

    pid_t hijo1, hijo2 = 1;

    int fd_hijo1[2];  //Crearemos un cauce, donde fd_hijo1[0] será lectura del hijo1, fd_hijo1[1] escritura del padre al hijo1
    int fd_hijo2[2];  //Crearemos un cauce, donde fd_hijo2[0] será lectura del hijo2, fd_hijo2[1] escritura del padre al hijo2

    if(pipe(fd_hijo1) < 0) {
        perror("\nError al crear el pipe 1");
        exit(-1);
    }


    if ((hijo1 = fork()) < 0) {
        perror("\nError en el fork del hijo1");
        exit(-1);
    }

    if (hijo1 != 0) {
        if (pipe(fd_hijo2) < 0) {
            perror("\nError al crear el pipe 2");
            exit(-1);
        }
        if ((hijo2 = fork()) < 0) {
            perror("\nError en el fork del hijo2");
            exit(-1);
        }
    }

    if (hijo2 == 1) {   //Código del hijo1

        close(fd_hijo1[1]); //Cerramos el cauce de escritura en el hijo 1

        //Declaramos variables que vayamos a usar
        char archivos[100];
        int leidos;
        char cambioCorrecto[] = "\nCambiados los permisos a 0644\n";

        umask(S_IXGRP |  S_IXOTH); //Establecemos la máscara para restringir permisos de escritura y ejecución de los archivos que creemos


        while (1) { //Metemos en un bucle infinito, ya que cuando el padre salga, también saldrán los hijos

            if ((leidos = read(fd_hijo1[0], archivos, 100)) < 0) {  //Leemos los datos del padre
                perror("\nError leyendo del pipe en el hijo 1");
                exit(-1);
            } else if (leidos == 0) {   //Si encontramos EOF, salimos
                printf("\nEncontrado EOF, saliendo desde el hijo1...\n");
                exit(0);
            }

            if (chmod(archivos, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {   //Le cambiamos los permisos
                perror("\nError cambiando los permisos del archivo desde el hijo 1");
                exit(-1);
            }

            write(STDOUT_FILENO, cambioCorrecto, strlen(cambioCorrecto));

        }

        close(fd_hijo1[0]); //Cerramos el cauce de lectura antes de salir
        exit(0);

    } else if (hijo2 == 0) { //Código del hijo2

        close(fd_hijo2[1]); //Cerramos el cauce de escritura en el hijo 2
        close(fd_hijo1[0]); //Cerramos también los cauces correspondientes al hijo 1
        close(fd_hijo1[1]);

        //Declaramos variables que vayamos a usar
        char cambioCorrecto[] = "\nCambiados los permisos a 0666\n";
        int arch;
        char archivos[100];
        int leidos;

        umask(S_IXGRP | S_IWOTH | S_IXOTH); //Establecemos la máscara para restringir permisos de escritura y ejecución de los archivos que creemos

        while (1) { //Metemos en un bucle infinito, ya que cuando el padre salga, también saldrán los hijos

            if ((leidos = read(fd_hijo2[0], archivos, 100)) < 0) {  //Leemos los datos del padre
                perror("\nError leyendo del pipe en el hijo 2");
                exit(-1);
            } else if (leidos == 0) {   //Si encontramos EOF, salimos
                printf("\nEncontrado EOF, saliendo desde el hijo2...\n");
                exit(0);
            }

            if ((arch = open(archivos, O_RDWR | O_CREAT ,S_IRWXU)) < 0) {   //Abrimos el archivo, creandolo si no existe
                perror("\nError abriendo el archivo desde el hijo 2");
                exit(-1);
            }


            if (fchmod(arch, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0) {   //Le cambiamos los permisos
                perror("\nError cambiando los permisos del archivo desde el hijo 2");
                exit(-1);
            }

            write(STDOUT_FILENO, cambioCorrecto, strlen(cambioCorrecto));

            close(arch);    //Cerramos el archivo
        }

        close(fd_hijo2[0]); //Cerramos el cauce de lectura antes de salir
        exit(0);

    } else {    //Código del padre

        close(fd_hijo1[0]); //Cerramos el cauce de lectura del hijo 1 en el padre
        close(fd_hijo2[0]); //Cerramos el cauce de lectura del hijo 2 en el padre

        //Declaramos las variables que vamos a usar
        char lectura[100];
        char cadena_fin[] = "fin";
        int leidos;
        struct stat atributos;

        signal(SIGCHLD, pickZombies);   //Ignoramos las señales del hijo, así evitamos dejar procesos zombie

        while (strcmp(cadena_fin, lectura) != 0) {

            if ((leidos = read(STDIN_FILENO, lectura, 100)) < 0) {  //Leemos de la entrada estándar
                perror("\nError leyendo de la entrada estándar");
                exit(-1);
            } else if (leidos == 0) {   //Si leemos EOF salimos
                printf("\nLeido EOF de la entrada estándar, saliendo...\n");
                exit(0);
            }

            lectura[strlen(lectura) - 1] = '\0';   //Quitamos el salto de línea del final

            if (strcmp(cadena_fin, lectura) == 0) { //Comparamos con nuestra cadena que simboliza el fin de ejecución
                break;
            }


            int existe = 1;

            if (stat(lectura, &atributos) < 0) {    //Si no conseguimos obtener los datos, significa que no existe, entonces lo creamos
                write(fd_hijo2[1], lectura, strlen(lectura));   //Y lo mandamos al hijo 2
                write(STDOUT_FILENO, "\nEl archivo no existe, creandolo...\n", strlen("\nEl archivo no existe, creandolo...\n"));
                existe = 0;
            }

            if (atributos.st_ino%2 == 0 && existe == 1) {   //Si existe y tiene inodo par, lo mandamos al hijo 1
                write(fd_hijo1[1], lectura, strlen(lectura));
            } else if (existe == 1) {   //Si existe e inodo impar, al hijo 2
                write(fd_hijo2[1], lectura, strlen(lectura));
            }

            for (int i = 0; i < 100;  i++)
                lectura[i] = '\0';

        }



        close(fd_hijo1[1]); //Cerramos el cauce de escritura en el padre antes de salir
        close(fd_hijo2[1]); //Cerramos el cauce de escritura en el padre antes de salir
        exit(0);
    }

    
}