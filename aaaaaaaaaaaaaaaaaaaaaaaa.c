/*
Integrantes de equipo:
-Alvarez Zamora Oscar Eduardo.
-Gallegos Ruiz Diana Abigail.
-Ramirez Hernandez Ana Daniela.
-Rojas Gomez Ian.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

#define MAXSIZEBUFFER 150

int id=0;
FILE *file; //Usaremos un file, ¿no?

void write(char *mensaje, char *nombreArchivo){
	kill(*pid del hermane*, SIGSTOP());
	file=fopen(nombreArchivo, 'w');
	if(file==NULL){
		printf("Hubo un error al abrir el archivo para escribir");
		exit(1);
	}else{
		fprintf(file, "%s", mensaje);
		fclose(file);
		kill(*pid del hermane*, SIGCONT());
		sleep(3); //idkboutthat
	}
}
void read(char *nombreArchivo){
	file=fopen(nombreArchivo, 'r');
	if(file==NULL){
		printf("Hubo un problema al abrir el archivo para leer");
		exit(1);
	}else{
		char string[MAXSIZEBUFFER];
		fscanf(file,"%s",string);
		printf("Mi hermanx dice: %s",string);
	}
}

int main(){
	file=NULL;
	pid_t  pid;
	int i=0;
	for(i;i<2;i++){
		if((pid=fork())==0){
			sleep(1);)
			break;
		}
	}
	id=i+1;
	while(1){
		write(*mensaje de teclado whynot*,file);
		read(file);
	}
	return 0;
}
