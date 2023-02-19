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

    DIR * directorio;
    int numero_hijos;

    if (argc < 2){
        perror("\nEl numero de argumentos es invalido");
        exit(EXIT_FAILURE);
    }

    numero_hijos = argv[2];
    pid_t hijos[numero_hijos]; //almacenaré aqui cada hijo creado para hacer los fork
    int numero_octales[numero_hijos]; //tendra el tamaño de el numero de hijos
    int indice = 3; //se empezará rellenando el array desde el 3 argumento 
    //relleno el array de octales
    
    //mientras el indice no sea igual al numero de argumentos
    while (indice <= argc){
        for(int i=0; i<numero_hijos; i++){
            numero_octales[i] = atoi(argv[indice]);
            indice++;
        }
    }

    //Una vez relleno, abro el directorio, para que pueda ser ejecutado por los hijos
    if(directorio = opendir(argv[1]) == -1){
        perror("\nNo se pudo abrir el directorio");
        exit(EXIT_FAILURE);
    }

    //Creo los hijos con fork
    for (int i=0; i<hijos; i++){
        if(hijos[i] = fork() < 0){
            perror("\nError en el fork");
            exit(EXIT_FAILURE);
        }
    }

    //creo el cauce sin nombre
    int fd[2];
    pipe(fd);

    //Creo otro cauce para enviar al padre los subtotales
    int fd2[2];
    pipe(fd2);

    pid_t padre = getppid();

    if(padre != 0){ //estoy en el proceso padre
        close(fd[0]); //cierro el modo lectura ya que el padre enviará cosas a los hijos
        //escribo los octales en el cauce
        for (int i=0; i<numero_hijos; i++){
            write(fd[1], numero_octales[i], sizeof(int));
        }

        //cuando ha terminado de enviarlos, imprimirá tantos valores de 0 como hijos creados
        //y así indica que ha terminado
        for(int i=0; i<numero_hijos; i++){
            printf("0\n");
        }
    }

    int octal; //los hijos van leyendo los octales enviados por el padre

    //voy recorriendo los hijos
    int j=0;
    int tam = numero_hijos;
    int buffer[tam];
    for (int i=0; i<numero_hijos; i++){
        if(hijos[i] = getpid() == 0){//estamos dentro del hijo i
            //ejecuto programa buscador con dir
            if( (execl(directorio, "./buscador", NULL) < 0)) {
                perror("\nError en el execl");
                exit(-1);
            }
            close(fd[1]); //cierro el modo escritura, ya que los hijos leeran los octales
            octal = read(fd[0], numero_octales[j], sizeof(int));
            j++;
            
            //Calculo los subtotales y los voy guardando en un buffer
            int subtotales = i++;
            buffer[i] = subtotales;

            //voy enviando los subtotales
            for (int i=0; i<buffer; i++){
                close(fd2[0]); //cierro la lectura, los hijos envian los subtotales
                write(fd[1], buffer[i], sizeof(int));
            }
        }
    }

    //Cuando los hijos terminan, el padre imprime el subtotal
    int subtotales = 0;
    if (padre != 0){
        close(fd2[1]); //cierro escritura, va a leer
        for (int i=0; i<tam; i++){
            subtotales += read(fd2[0], buffer[i], sizeof(int));
        }

        printf("\nEl total de subtotales es: %d", subtotales);
    }

    return (0);

}