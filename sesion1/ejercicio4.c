
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

 //duda de si lo he implementado bien y de si siempre las macros deben llamarse S_noseque
#define S_ISREG2(st_mode) ((st_mode & S_IFMT )== S_IFREG)

int main(int argc, char *argv[] ){

    struct stat atributos;
    char tipoArchivo[30];

    if(argc < 2){
        printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
        exit(-1);
    }

    if(lstat(argv[1],&atributos) < 0){
        printf("\nError al intentar acceder a los atributos de %s",argv[1]);
        perror("\nError en lstat");
    }
        

    printf("%s: ", argv[1]);

    if(S_ISREG2(atributos.st_mode))
        strcpy(tipoArchivo, "Regular");

    printf("%s\n",tipoArchivo);


    return 0;
}