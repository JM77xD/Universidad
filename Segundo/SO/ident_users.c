#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main(void)
{
printf("Identificador de usuario: %d\n", getuid());
printf("Identificador de usuario efectivo: %d\n", geteuid());
printf("Identificador de grupo: %d\n", getgid());
printf("Identificador de grupo efectivo: %d\n", getegid());
printf("El PID del padre es: %d\n", getppid());
printf("Mi PID es: %d\n", getpid());
}