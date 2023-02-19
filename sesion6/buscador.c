#include<err.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    DIR *directorio;
    int octal;
    struct dirent * informacion;
    struct stat atributos;
    int espacio_ocupado = 0;

    if (argc != 2){
        perror("\nEl numero de argumentos no es valido, se esperaba un directorio");
        exit(EXIT_FAILURE);
    }

    //abro el directorio
    if (directorio = opendir(argv[1]) == -1){
        perror("no se pudo abrir el directorii");
        exit(EXIT_FAILURE);
    }

    //Introducir el numero de 3 digitos
    printf("Introduce un numero octal de 3 digitos");
    scanf("%d",  octal);

    while(octal != 0){
        //Recorremos el directorio y buscamos los archivos
        while(informacion == readdir(directorio) != 0){
            //para ver el estado de un archivo, usamos la variable stat y asi 
            //accedemos a sus atributos
            if(stat(informacion->d_name, &atributos) < 0){
                perror("\nNo se pudo acceder a los atributos del archivo");
                exit(EXIT_FAILURE);
            }

            //una vez he podido acceder. veo si los permisos coinciden
            //Si el archivo es regular y ademas coinciden en el permiso pasado
            if(S_ISREG(atributos.st_mode) && atributos.st_mode == octal){
                //calcula el espacio que ocupa ese archivo regular y lo va acumulando
                espacio_ocupado += atributos.st_size;
                //muestro por LA SALIDA DE ERROR el nombre del archivo, su inodo y el espacio
                write(STDERR_FILENO, informacion->d_name, sizeof(informacion->d_name));
                write(STDERR_FILENO, atributos.st_ino, sizeof(int));
                write(STDERR_FILENO, atributos.st_size, sizeof(int));
            }
        }

        //una vez recorrido el directorio, leemos un nuevo numero
        printf("Introduzca un numero octal de 3 digitos");
        scanf("%d", octal);

        if (octal == 0){
            printf("\nEl espacio total ocupado por las coincidencias anteriores es: ",
            espacio_ocupado);
        }
    }

    closedir(directorio);
    return(0);
}
