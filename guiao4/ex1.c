#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

    /*
0 é para o std intput
1 é para o std output 
2 para o std error
    */

//DUVIDA: O QUE TEMOS QUE ESCREVER NO ERROS.TXT ????

/*
1º Fazer open do ficheiro que queremos e guardar o file descriptor
2º Redirecionar (fazer dup2) o std input, std output e std error para onde queremos (estes descritores de ficheiro)
3º Fazer close dos descritores de ficheiro
4º Ler o que esta no ficheiro e escrever onde queremos (escrevemos no numero associado onde queremos, pq em vez de escrever lá, vai escrever onde foi redirecionado)
*/

int main (int argc, char * argv[]) {
    int res;
    char buffer;
    char line[100];
    int i=0;


    int ifd = open ("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2 (ifd, 0);
    res = dup2 (ofd, 1);
    res = dup2 (efd, 2);

    close (ifd);
    close (ofd);
    close (efd);

    int read_res;

    while ((read_res = read(0, &buffer, 1)) != 0) { //ler caracter a caracter (so para demostrar)
        line[i] = buffer;
        i++;

        if (buffer == '\n') {
            write(1, line, i);      //i indica o nº de bytes que a linha tem
            write (2, line, i);     //ao escrever no 2, vai para o erros.txt pq foi redirecionado

            printf ("after write line || i = %d\n", i);

            fflush (stdout);    //flush != close ----> tudo o que tiver em buffer neste momento escreve para ficheiro (descarrega o que está em buffer)

            //setbuf (stdout, NULL);    //faz o mesmo que o fflush mas teria que por na linha antes de fazer os open's

            i=0;
        }
    }
    return 0;
}