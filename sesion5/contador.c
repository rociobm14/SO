#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types // <sys/types.h>
#include <limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

static int count_signals[65];
static int signals[65];

static void handler(int sigNum){
    if (sigNum > 64 || sigNum < 0){
        printf("El programa no puede capturar la señal %d\n", sigNum);
        raise(SIGSTOP); //kill(getpid(), SIGSTOP)
    }

    if (signals[sigNum] == 0){//Si es 0, la señal se puede manejar.
        count_signals[sigNum]++;
        printf("La señal %d, se ha escrito %d veces.\n", sigNum, count_signals[sigNum]);
    }

    else{
        printf("La señal %d es una señal invalida\n", sigNum);
        raise(SIGSTOP); 
    }
}

int main(int argc, char *argv[]){
    
    struct sigaction sa;

    if (setvbuf(stdout, NULL, _IONBF, 0)){
        perror("\nError en setvbuf");
    }

    //Inicializo handler
    sa.sa_handler = handler;

    //Inicializamos señales vacías
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    //Establecemos los 64 manejadores
    for (int i=0; i<65; i++){
        if (sigaction(i, &sa, NULL) < 0){
            printf("No puedo manejar la señal %d\n", i);
            signals[i] = 1; //si se asigna 1 a esa señal, no se puede manejar.
        }
    }

    printf("Esperando el envío de señales...\n");
    while(1);
}