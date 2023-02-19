#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

//No se como se haria, background --> lo ejecuta el hijo.
int main(void){

    const int TAM = 256;
    char *argv[TAM];
    int plano; //para saber si es foreground o background.
    char *entrada;
    char **argv;

    printf("\n ESCRIBIR EXIT PARA FINALIZAR LA SESION\n");

    while(1){
        printf("shell >");
        gets(entrada);
        if(strcmp(entrada, "EXIT") == 0){ //si se escribe EXIT, se finaliza todo.
            printf("Fin de la sesion\n");
            exit(0);
        }

        int plano = 0;
        while
    }

}