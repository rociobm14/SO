#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> //para usar wait

int main(int argc, char *argv[]){
    //Es necesario declarar el i aquí en vez de en el for siempre?
    int i, estado;
    pid_t hijo;

    //CREAMOS LOS HIJOS
    for (i = 0; i<5; i++){
        if ((hijo = fork()) < 0){
            perror("Error en el fork\n");
            exit(EXIT_FAILURE);
        }

        if (hijo == 0){
            printf("Soy el hijo con PID = %d\n", getpid());
            exit(EXIT_SUCCESS);
        }
    }

    //ESPERAMOS A QUE ACABEN LOS HIJOS
    for (int i=4; i>=0; i--){
        hijo = wait(&estado);
        printf("Acaba de finalizar mi hijo con PID = %d\n", hijo);
        printf("Solo me quedan %d hijos vivos\n", i);
    }

    return 0;
   
}