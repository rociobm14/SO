//EJEMPLO DE CREACIÓN DE UNA PROYECCIÓN//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

//definimos constante de mmap
const int MMAPSIZE=1024;

int main(){

    int fd, num;
    char ch='\0';
    char *memoria;
    
    //abrimos el archivo tal que se pueda leer y escribir, y con O_EXCL onliga a que
    //el archivo se cree 
    fd = open("Archivo", O_RDWR|O_CREAT|O_EXCL, S_IRWXU);
    
    //Si es -1 (error), significa que el archivo ya existe
    if (fd == -1) {
        perror("El archivo existe");
        exit(1);
    }
    
    //Va escribiendo en fd, de 1 en 1 el char \0, null,  con el número de bytes a
    // escribir sizeof(char), y así 1024 veces. Si la escritura da -1, significa que hay un
    //error en la escritura y por tanto no se puede escribir.
    for (int i=0; i < MMAPSIZE; i++){
        num = write(fd, &ch, sizeof(char));
        if (num!=1) 
            printf("Error escritura\n");
    }
    
    //Creamos la proyección con mmap, una vez tenemos fd relleno.
    //address = 0, dirección de inicio (es lo que se pone normalmente)
    //size: el de MMAPSIZE,
    //FLAGS: los datos se pueden leer y escribir y además se complementa con que
    //las modificaciones serán compartidas
    //fd: el descriptor de archivo que se proyectará
    //offset: es el desplazamiento desde el cuál se proyecta, en este caso es 0
    memoria = (char *)mmap(0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    
    //si la memoria falla, no se podrá realizar la proyección
    if (memoria == MAP_FAILED) {
        perror("Fallo la proyeccion");
        exit(2);
    }
    
    close(fd); /* no es necesario el descriptor*/
    
    strcpy(memoria, "Hola Mundo\n"); /* copia la cadena en la proyección */
    
    exit(0);
}