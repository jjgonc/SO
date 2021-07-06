#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> // chamadas ao sistema: definiçoes e declaraçoes essenciais
#include <fcntl.h>  //O_RDONLY, O_WRONLY, O_CREAT, O_*


#define MAX_BUFF 1024   //tamanho em BYTES que definimos para o buffer. Quanto mais pequeno for o buffer, mais chamadas ao read e write vai fazer, logo demora mais


int main (int argc, char * argv[]) {
    void * buffer = malloc(MAX_BUFF);
    int fd_origem, fd_destino;

    if ((fd_origem = open(argv[1], O_RDONLY)) == -1) {         //quando devolve -1 quer dizer que deu erro
        perror ("open");
        return -1;
    }

    if ((fd_destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640)) == -1) {       //quando devolve -1 é pq deu erro
        perror ("open");
        return -2;
    }

    int bytes_read;
    printf ("antes do ciclo %d\n", fd_origem);
    while ((bytes_read = read (fd_origem, buffer, MAX_BUFF)) > 0) {     //ver o nº maximo de bytes que cabe no buffer
        write (fd_destino, buffer, bytes_read);
    }

    close (fd_origem);
    close (fd_destino);

    return 0;

}

//fazer no terminal: time ./mycp source dest (é preciso ter o ficheiros)


//deixei nesta pasta o ficheiro teste_mycp, entao para testar é só fazer:

// > ./a.out mycp_teste novoficheiro 

//e ee vai copiar o ficheiro para um novo chamado novoficheiro (que foi o segundo nome que lhe passei)