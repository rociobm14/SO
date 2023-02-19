#include <stdio.h>
#include <signal.h>

int main(){

    sigset_t new_mask;
    
    /* inicializar la nueva mascara de señales */
    sigemptyset(&new_mask);
    
    sigdelset(&new_mask, SIGUSR1); // quitamos la máscara que queremmos
    
    //El proceso esperará mientras se manden otras señales que no sean SIGUSR1.
    sigsuspend(&new_mask);
 }