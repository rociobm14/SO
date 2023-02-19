#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[]){

    DIR *directorio;
    struct dirent *entrada;
    struct stat atributos;
    int permisosNuevos, permisosAntiguos;
    char pathname[257]; //256 era muy pequeño para sprintf debido a que también contiene el
                        //carácter nulo /0

    directorio = opendir(argv[1]); //abrimos el directorio y lo guardamos en el puntero.

    //strol convierte el número en un long int de forma octal, que es lo que 
    //necesitamos nosotros para dar permisos, pues están de esa forma.
    permisosNuevos = strtol(argv[2], NULL, 8);

    //Lee donde está el puntero directorio, adelanta una posicion y lo devuelve 
    //a la estructura dirent (entrada).
    while ((entrada == readdir(directorio)) != 0){
        
        //guarda en pathname el nombre del archivo
        sprintf(pathname, "%s/%s", argv[1], entrada->d_name); 

        //lstat examina el archivo al que apunta pathname, y llena el buffer atributos.
        lstat(pathname, &atributos);

        //con el stat atributos accede a los permisos del archivo y se queda solo
        //con los de la derecha de &.
        permisosAntiguos = atributos.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

        //Con strcmp se comprueba si el nombre del directorio es . o .. y ya
        //en función de eso le damos los nuevos permisos.
        //Lo que hace strcmp es comprobar 2 strings, en este caso compara el nombre del
        //archivo correspondiente con los string . y ..
        if ((strcmp(entrada->d_name, ".") && strcmp(entrada->d_name, "..")) != 0){
            //Si el archivo al que apunta pathname se le puede cambiar su modo con los
            //nuevos permisos, será correcto e imprimirá los permisos antiguos y nuevos
            if (chmod(pathname, permisosNuevos) == 0)
                printf("%s: %o %o\n", entrada->d_name, permisosAntiguos, permisosNuevos);
            
            //Si no se le puede cambiar su modo, tan solo imprimirá el error y los antiguos.
            else
                printf("%s: %o %o\n", entrada->d_name, errno, permisosAntiguos);

        } 

    }
    //cerramos el directorio que hemos pasado como argumento.
    closedir(directorio);
}