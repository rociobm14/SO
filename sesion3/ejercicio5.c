#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> //para usar wait

int main(int argc, char *argv[]){
    int i, estado;
    pid_t hijos[5];

    //CREAMOS LOS HIJOS
    for (i = 0; i<5; i++){
        if ((hijos[i] = fork()) < 0){
            perror("Error en el fork\n");
            exit(EXIT_FAILURE);
        }

        if (hijos[i]== 0){
            printf("Soy el hijo con PID = %d\n", getpid());
            exit(EXIT_SUCCESS);
        }
    }

    //BUCLE PARA LOS IMPARES

    int hijos_restantes = 5;
    for (i = 0; i<5; i++){
        if(hijos[i] % 2 != 0 && waitpid(hijos[i], 0, 0)){
            printf("Acaba de finalizar mi hijo con PID = %d\n", hijos[i]);
            printf("Solo me quedan %d hijos vivos\n", hijos_restantes--);
        }
    }

    for (int j = 0; j<5; j++){
        if(hijos[j] % 2 == 0 && waitpid(hijos[j], 0, 0)){
            printf("Acaba de finalizar mi hijo con PID = %d\n", hijos[j]);
            printf("Solo me quedan %d hijos vivos\n", hijos_restantes--);
        }
    }
    return 0;
   
}