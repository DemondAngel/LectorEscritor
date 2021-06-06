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
#define MAXSIZEPIDBUFFER 10

int id=0, pidS = 0;
int fd[2], fd2[2];
FILE *file; //Usaremos un file, �no?
char * pidc[2], *pidc2;

void escribeTuberia(char * buffer, int * tuberia){
    close(tuberia[0]);//Cerramos el lado de lectura del pipe
    write(tuberia[1], buffer, strlen(buffer));
    close(tuberia[1]);
}

char * leeTuberia(int * tuberia){
    char * buffer = (char * ) calloc(MAXSIZEPIDBUFFER, sizeof(char));
    close(tuberia[1]);

    read(tuberia[0], buffer, MAXSIZEPIDBUFFER);

    close(tuberia[0]);

	return buffer;
}

void writeMessage(char *mensaje, char *nombreArchivo){
	
	file=fopen(nombreArchivo, "w");
	if(file==NULL){
		printf("Hubo un error al abrir el archivo para escribir");
		exit(1);
	}else{
		fprintf(file, "%s", mensaje);
		fclose(file);
		kill(pidS, SIGCONT);
		printf("\nDebio revivir al proceso %i\n", pidS);
		kill(pidS, SIGUSR1);
		sleep(3); //idkboutthat
	}
}
void readMessage(char *nombreArchivo){
	file=fopen(nombreArchivo, "r");
	if(file==NULL){
		printf("Hubo un problema al abrir el archivo para leer");
		exit(1);
	}else{
		char string[MAXSIZEBUFFER];
		fscanf(file,"%s",string);
		printf("Mi hermanx dice: %s",string);
		fclose(file);
	}

}

void handle_sigusr1(){
	readMessage("comunicacion.txt");
}

int main(){
	pid_t pid[2];
	int i=0;
	pipe(fd);
	pipe(fd2);

	for(i;i<2;i++){

		pid[i]=fork();
		if(pid[i] == 0){
			sleep(1);
			struct sigaction sa = { 0 };
			sa.sa_flags = SA_RESTART;
			sa.sa_handler = &handle_sigusr1;

			sigaction (SIGUSR1, &sa, NULL);
			
			if(i == 0)
				pidc2 = leeTuberia(fd);
			else
				pidc2 = leeTuberia(fd2);
				
			pidS = atoi(pidc2);
			id=i+1;
			break;
		}
		else if(pid[i] == -1){
			printf("\nHa ocurrido un error mientras se creaba el Hijo\n");
		}
		pidc[i] = calloc(10, sizeof(char));
		sprintf(pidc[i], "%i", pid[i]);
	}

	if(id == 0){
		escribeTuberia(pidc[0], fd2);
		escribeTuberia(pidc[1], fd);
	}
	else{
		while(1){
			printf("\nPrint este es el proceso %i este es el proceso hermano %i id asignado de forma local %i\n", getpid(),pidS, id);
			fflush(stdin);
			char mensaje[MAXSIZEBUFFER];
			
			kill(pidS, SIGSTOP);

			printf("\nPor favor escriba un mensaje para el proceso %i\n", pidS);

			scanf("%s", mensaje);

			writeMessage(mensaje,"comunicacion.txt");
		}
	}

	wait(&pid[0]);
	wait(&pid[1]);

	return 0;
}
