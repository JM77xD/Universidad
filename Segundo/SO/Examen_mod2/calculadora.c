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

    mkfifo("/tmp/fifo_entrada", S_IRUSR|S_IWUSR | S_IRGRP | S_IROTH);
    

    int fd_recibirDatos;

    if ((fd_recibirDatos = open("/tmp/fifo_entrada", O_RDONLY | O_TRUNC, S_IRUSR | S_IRGRP)) < 0) {
        perror ("\nError al abrir el fifo de entrada");
        exit(-1);
    }

    char datos[300];
    int leidos;

    while ((leidos = read(fd_recibirDatos, datos, 300)) != 0) {
        if (leidos < 0 ) {
            perror("\nError leyendo del fifo de entrada");
            exit(-1);
        }

        int pos_salto1 = 0, pos_salto2 = 0, pos_salto3 = 0, pos_salto4 = 0;

        for (int i = 0; i < leidos; i++) {
            if (datos[i] == '\n') {
                if (pos_salto1 == 0) {
                    pos_salto1 = i;
                } else if (pos_salto2 == 0) {
                    pos_salto2 = i;
                } else if(pos_salto3 == 0) {
                    pos_salto3;
                } else if (pos_salto4 == 0) {
                    pos_salto4 = i;
                }
            }
        }

        char pid_cliente[pos_salto1+1], operando1[pos_salto2-pos_salto1+1], operacion[pos_salto3-pos_salto2+1], operando2[pos_salto4-pos_salto3+1];

        for (int i = 0; i < pos_salto1; i++) {
            pid_cliente[i] = datos[i];
        }

        for (int i = pos_salto1+1; i < pos_salto2; i++) {
            operando1[i-pos_salto1-1] = datos[i];
        }

        for (int i = pos_salto2+1; i < pos_salto3; i++) {
            operacion[i-pos_salto2-1] = datos[i];
        }

        for (int i = pos_salto3+1; i < pos_salto4; i++) {
            operando2[i-pos_salto3-1] = datos[i];
        }

        long oper1, oper2;

        oper1 = atol(operando1);
        oper2 = atol(operando2);

        pid_cliente[pos_salto1] = '\0';
        operando1[pos_salto2-pos_salto1] = '\0';
        operacion[pos_salto3-pos_salto2] = '\0';
        operando2[pos_salto4-pos_salto3] = '\0';

        char fifo_vuelta[126];
        sprintf(fifo_vuelta, "/tmp/fifo_vuelta_%s", pid_cliente);

        int fvuelta;
        if ((fvuelta = open(fifo_vuelta, O_WRONLY, S_IWUSR)) < 0) {
            perror("\nError abriendo el fifo de vuelta del cliente");
            exit(0);
        }

        long resultado;

        if (strcmp("*", operacion) == 0) {
            resultado = oper1 * oper2;
        } else if (strcmp("+", operacion) == 0) {
            resultado = oper1 + oper2;
        } else {
            printf("\nOperación no reconocida\n");
        }

        char result[50];

        sprintf(result, "%ld", resultado);

        write(fvuelta, result, strlen(result));

        for (int i = 0; i < 300; i++)
            datos[i] = '\0';

        unlink(fifo_vuelta);
    }
}