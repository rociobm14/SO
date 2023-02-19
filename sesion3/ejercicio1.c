//bibliotecas fork
#include <sys/types.h>
#include <unistd.h>

//bibliotecas de errores y demás
#include <stdio.h>
#include <errno.h>
#include <stdlib.h> //para exit_failur etc.

/*duda de los argumentos: siempre hay que poner las comprobaciones de argc = num arg
o tambien si es menor mayor != etc.
*/

//duda: es necesario comprobar el valor de pid para ver si no es válido?

//duda: tengo bien el pid del padre? o no haría falta poner getpid?

//duda: hay que poner return 0 o return exit_succes?
int main(int argc, char *argv[]){
    
    if (argc != 2){
        perror("\nErrror, se debe de introducir solo un numero a comprobar.");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();


    if(pid < 0){
        perror("\nError en el fork");
        exit(EXIT_FAILURE);
    }

    //si pid= 0 --> proceso hijo
    if (pid == 0){ //proceso hijo

        if(atoi(argv[1]) % 2 == 0)
            printf("Proceso hijo: El numero %d es par\n", atoi(argv[1]));
        
        else
            printf("\nProceso hijo: El numero %d es impar\n", atoi(argv[1]));
 
    }

    else if (pid){
        if(atoi(argv[1]) % 4 == 0)
            printf("\nProceso padre: El numero %d es divisible por 4\n", atoi(argv[1]));
        
        else
            printf("\nProceso padre: El numero %d no es divisible por 4\n", atoi(argv[1]));

    }

    return EXIT_SUCCESS;

}

