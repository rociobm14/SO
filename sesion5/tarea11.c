//tarea11.c
#include <stdio.h>
#include <signal.h>

//no entiendo muy bien como funciona, he buscado en internet que el numero de señal
//de SIGUSR1 es 16, pero hace lo mismo que si le paso 3 ,4 , 10 o cosas así.

int main(){

    sigset_t new_mask;
    
    /* inicializar la nueva mascara de señales */
    sigemptyset(&new_mask);
    
    sigaddset(&new_mask, SIGUSR1); //añadimos la máscara SIGUSR1.
    
    /*esperar a cualquier señal excepto SIGUSR1 */
    sigsuspend(&new_mask);
 }