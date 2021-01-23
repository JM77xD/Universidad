#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char *argv[]) {

    char buf[100] ;
    int fd;
    int output = open("salida.txt", O_CREAT | O_WRONLY, S_IRUSR|S_IWUSR);

    if (argc > 2) {
        perror("\nError en el numero de argumentos\n");
        exit(-1);
    }

    if (argc == 1) {
        fd = STDIN_FILENO;
        write(fd, "\nAdoptando stdin como entrada\n<Ctrl+D> para finalizar\n", strlen("\nAdoptando stdin como entrada\n<Ctrl+D> para finalizar\n"));
    } else if ((fd = open(argv[argc-1], O_RDONLY)) < 0) {
        printf("\nError %d en la apertura del archivo", errno );
        perror("\nError en el open");
        exit(-1);
    }  

    int contador = 1;
    char a_escribir[80];
    int leidos;

    while ((leidos = read(fd, a_escribir, 80)) != 0) {
        
        sprintf(buf, "\nLectura del bloque %d:\n", contador); //Covertir el int en un char con sprintf @see stdio.h
        write(output, buf, strlen(buf));
        write(output, a_escribir, leidos);
        contador = contador + 1;
    }

    close(output);
    close(fd);


    return 0;
}