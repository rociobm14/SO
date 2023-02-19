#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    struct flock cerrojo;
    int fd;
    
    //el programa toma uno o varios pathname como argumento
    //cuando ya no queden, se saldrá del bucle, ya que argc va disminuyendo.
    while (--argc > 0){
        //abre el pathname, y se puede tanto leer como escribir en él.
        if ((fd = open(*++argv, O_RDWR)) == -1) {
            perror("open fallo"); 
            continue;
        }

        //DEFINIMOS LOS CAMPOS DEL CERROJO, este cerrojo es consultivo, 
        //se situa el cerrojo antes de realizar la operación E/S.
        cerrojo.l_type = F_WRLCK; //tipo de bloqueo --> cerrojo de escritura
        
        //estos son el rango de bytes que se quieren bloquear
        //En este caso se bloquea desde el inicio del archivo (SEEK_SET)
        //Hasta el final, porque se ha especificado 0 en l_start y l_len
        cerrojo.l_whence = SEEK_SET; //desde el inicio del archivo
        cerrojo.l_start = 0; //desde el inicio se bloquea hasta el finañ
        cerrojo.l_len = 0; //desde el inicio se bloquea hasta el final

        //Establece el cerrojo sobre el archivo fd con la orden F_SETLK
        /* intentamos un bloqueo de escritura del archivo completo */
        //Mientras de error, -1, vemos quien lo bloquea
        while (fcntl(fd, F_SETLK, &cerrojo) == -1){
            
            /*si el cerrojo falla, vemos quien lo bloquea*/
            //F_UNLCK elimina un cerrojo.
            //Comprobamos si el cerrojo falla, y con F_GETLK vemos quién lo bloquearía.
            //Si existe bloqueo, significa que el fcntl es != -1,entonces si existe
            //bloqueo y no se elimina el cerrojo, imprimimor la zona de bloqueo
            while(fcntl(fd, F_GETLK, &cerrojo) != -1 && cerrojo.l_type != F_UNLCK ){
                printf("%s bloqueado por %d desde %lld hasta %lld para %c", *argv, 
                cerrojo.l_pid, cerrojo.l_start, cerrojo.l_len, 
                cerrojo.l_type==F_WRLCK ? 'w':'r'); //exclusivo (w) o compartido(r)

                if (!cerrojo.l_len) break;
                cerrojo.l_start +=cerrojo.l_len;
                cerrojo.l_len=0;
            } /*mientras existan cerrojos de otros procesos*/
        
        } /*mientras el bloqueo no tenga exito */
        
        /* Ahora el bloqueo tiene exito y podemos procesar el archivo */
        printf ("procesando el archivo\n");
        /* Una vez finalizado el trabajo, desbloqueamos el archivo entero */
        cerrojo.l_type =F_UNLCK; //se elimina el cerrojo
        cerrojo.l_whence =SEEK_SET;
        cerrojo.l_start =0;
        cerrojo.l_len =0;
        
        //con F_SETLKW establece un cerrojo, y  si este no se puede obtener, bloquea
        //a fcntl hasta que se pueda obtener dicho cerrojo.
        if (fcntl(fd, F_SETLKW, &cerrojo) == -1) 
            perror("Desbloqueo");
    }
    return 0;
}