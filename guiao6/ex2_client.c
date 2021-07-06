#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

 int main (int argc, char * argv[]) {
     if (argc > 1) {
         int fd = open("fifo", O_WRONLY);
        //if (write(fd, argv[1], strlen(argv[1])) == -1) {
            //perror ("write error");
        //}
        write(fd, argv[1], strlen(argv[1]));
        close(fd);
     }
     else {
         printf ("Formato errado. -> ./client hello world\n");
     }
     return 0;
 } 


 /*
gcc ex2_client -o client
./client ola


open bloqueia quando nao ha nenhum extremo de leitura aberto

read devolve zero se nao houver nenhum processo com o extremo de escrita aberto. Caso contrario, mantem-se bloqueado
o servidor bloqueia se abrir o extremo de escrita e nao tiver nenhum de leitura aberto
open de leitura boqueia até ter extremo de escrita aberto e vice-versa.
 */