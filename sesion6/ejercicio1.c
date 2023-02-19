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
    
    int fd;

    //Redireccionamos la entrada o salida estándar dependiendo de si es < o >
    //entrada --> <
    //salida --> >

    //ENTRADA
    if(strcmp(argv[2], "<") == 0){
        fd = open(argv[3], O_RDONLY);
        close(STDIN_FILENO);

        if(fcntl(fd, F_DUPFD, STDIN_FILENO) == -1)
            perror("\nError en fcntl");
    }
    
    //SALIDA
    else if (strcmp(argv[2], ">") == 0){
        fd = open(argv[3], O_CREAT|O_WRONLY);    
        close(STDOUT_FILENO);
        
        if(fcntl(fd, F_DUPFD, STDOUT_FILENO) == -1)
            perror("\nError en fcntl");    
    }

    else{
        printf("\nEl segundo parametro debe ser uno de los anteriores");
    }

    //ejecuta la orden
    if (execlp(argv[1], "", NULL) < 0){
        perror("Error en excelp\n");
        exit(EXIT_FAILURE);
    }

    close(fd);
}