#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

//Esta bien?
int main(int argc, char *argv){
    
    int i;
    int nprocs = 20;
    pid_t childpid;

    for (i=1; i < nprocs; i++){
        if ((childpid = fork()) == -1){
            fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
            exit(-1);
        }

        if (!childpid){
            printf("PID hijo = %d - PID padre = %d \n", getpid(), getppid());
            break;

        }
    }

    exit(EXIT_SUCCESS);
}