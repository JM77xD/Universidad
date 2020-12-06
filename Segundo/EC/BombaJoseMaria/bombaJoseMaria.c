// gcc -Og bombaJoseMaria.c -o bombaJoseMaria -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 8

char password[]="AverSiAdivina\n";	// contraseña
int  passcode  = 1314;			// pin

void boom(void){		//Imprime la explosión
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){		//imprime bomba desactivada
	printf(	"\n"
		"---------------------------------------------------------------------\n"
		"------- bomba desactivada -------\n"
		"---------------------------------------------------------------------\n"
		"\n");
	exit(0);
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);	//Tomamos el tiempo

	do	printf("\nIntroduce la contraseña, tienes 7 segundos.\nContraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );	//Obtenemos un array de char desde stdin
	
	if    (	strncmp(pw,password,sizeof(password)) )	//Comparamos las claves
	    boom();

	gettimeofday(&tv2,NULL);	//Tomamos el tiempo

	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )	//Si tarda más de TLIM (7s), explota
	    boom();

	do  {	printf("\nIntroduce el pin, tienes 7 segundos.\nPIN: ");	//Leemos el pin
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;
		} while ( n!=1 );

	if ( pc != passcode ) //Si no coinciden, explota
	    boom();

	gettimeofday(&tv1,NULL);

	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )	//Si hemos tardado más de lo permitido, explota
	    boom();

	defused();	//Se desactiva la bomba
}