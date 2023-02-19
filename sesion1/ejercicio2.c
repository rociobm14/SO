#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> //para strlen

//duda: si no paso argumentos no me coge la entrada estándar.
//duda 2: que es mejor poner, perror o printf
//basicamente lo entiendo regular

int main(int argc, char *argv[]){

    int filein = STDIN_FILENO;
    int fileout;
    int leer;
    int count = 80;
    char buff[80];
    char bloque[15];
    int num_bloque = 0;
   
    if (argc > 2){
        printf("Error: numero incorrecto de argumentos\n");
        exit(EXIT_FAILURE);
    }

    else if(argc==2){
        if ((filein = open(argv[1], O_RDONLY))< 0){
            printf("Error %d en open\n", errno);
            perror("Error en open\n");
            exit(EXIT_FAILURE);
        }
    }

    if ((fileout = open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
        printf("Error %d en open\n", errno);
        perror("Error en open\n");
        exit(EXIT_FAILURE);
    }

    while ((leer = read(filein, buff, count)) != 0){
        if (leer < 0){
            perror("\nError en el read");
            exit(EXIT_FAILURE);
        }
        
        num_bloque++;

        if (write(fileout, bloque, strlen(bloque)) != strlen(bloque)){
            perror("\nError en write1");
            exit(EXIT_FAILURE);
        }

        sprintf(bloque, "\nBloque %d\n", num_bloque);


        if (write(fileout, bloque, strlen(bloque)) != strlen(bloque)){
            perror("\nError en write2");
            exit(EXIT_FAILURE);
        }


        if (write(fileout, buff, leer) != leer){
            perror("\nError en write3");
             exit(EXIT_FAILURE);
        }

    }

    close(filein);
    close(fileout);
    return EXIT_SUCCESS;
}