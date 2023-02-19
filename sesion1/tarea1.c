#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
//HE TENIDO QUE AÑADIR ESTO PARA QUE ME FUNCIONE EXIT
#include <stdlib.h>
//HE TENIDO QUE AÑADIR ESTO PARA QUE ME FUNCIONEN LAS FUNCIONES OPEN, WRITE, LSEEK, ETC
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[]){
    
    int fd;
    if ((fd = open("archivo", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0){
        printf("\nError %d en open", errno);
        printf("\nError en open");
        exit(-1);
    }

    if (write(fd, buf1, 10) != 10){
        perror("\nError en el primer write");
        exit(-1);
    }

    if (lseek(fd, 40, SEEK_SET) < 0){
        perror("\nError en lseek");
        exit(-1);
    }

    if (write(fd, buf2, 10) != 10){
        perror("\nError en segundo write");
        exit(-1);
    }

    close(fd);
    return 0;

}