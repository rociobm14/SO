#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    const int T = 4; 

    if (argc != T){
        printf("Error en el numero de parametros.");
        exit(EXIT_FAILURE);
    }

    //redireccionar a la salida
    int fd[2];
    pid_t PID;

    if (strcmp(argv[2], "|")){
        pipe(fd); //llamada al sistema para crear un cauce sin nombre

        //comprobamos PID
        if(PID = fork() < 0){
            perror("\nError en el fork");
        }

        if (PID == 0){ //proceso hijo (redirecciona salida), es escritor
            close(fd[0]); //cierra el descriptor de lectura, ya que va a escribir.
            close(STDOUT_FILENO);

            if(fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1){
                perror("\nFallo en el fcntl del hijo");
                exit(EXIT_FAILURE);
            }

            //ejecutamos la orden
            execlp(argv[1], argv[1], NULL);
        }

        else{ //proceso padre (redirecciona la entrada), es lector
            close(fd[1]); //cerramos descriptor de escritura, va a leer
            close(STDIN_FILENO);

            if(fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1){
                perror("\nError en fcntl del padre");
                exit(EXIT_FAILURE);
            }

            execlp(argv[3], argv[3], NULL);
        }
    }

    else{
        perror("El segundo parametro tiene que ser el indicado anteriormente\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}