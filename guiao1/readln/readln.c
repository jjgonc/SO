#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

//readln lê ate encontrar um \n -> char *line
//ou o numero de bytes maximo ser escrito -> size_t size




/*
HOW TO USE:
gcc readln.c
./a.out

write on terminal and it will write on terminal the same string
*/

int readc (int fd, char *c) {
    //implementaçao char a char (byte a byte pq 1char == 1byte)
    return read (fd, c, 1);     //este 1 quer dizer o nº de bytes que le de cada vez -> neste caso 1 byte de cada vez
}


ssize_t readln(int fd, char *buf, size_t size) {       //line é um buffer
    int res = 0;
    int i = 0;

    while (i<size && (res = readc (fd, &buf[i]) > 0)) { //ate o readc dizer que ja nao ha mais nada para ler ou ate excedermos o tamanho max
        i++;
        if (((char*) buf) [i-1] == '\n') {
            return i;   //se encontrar um \n dá imediatamente return do nº de bytes lidos
        }
    }
    return i;
}




int main (int argc, char * argv[]) {
    int out = STDOUT_FILENO;                            //DUVIDA:  para que serve isto????   R.: Guardar o file descriptor do standard output (é o mesmo que 1) que é escrever no terminal
    int line_counter = 0;
    char* buffer = (char *) malloc(MAX_BUFFER * sizeof(char));
    int bytes_read = 0;
    int newline = 1;

    while ( (bytes_read = readln (0, buffer, MAX_BUFFER)) > 0) {
        char line_number[10] = "";   //inicializar a string
        //esta funçao vai passar a frente linhas vazias (enters) por causa da condiçao do while
        if (newline && buffer[0] != '\n') {
            snprintf (line_number, 10, "%d:", line_counter);        //10 é o tamanho alocado apra o line number-> se tiver mais de 10 digitos trunca o ficheiro
            write(out, line_number, sizeof (line_number));
            line_counter++;
        }
        write (out, buffer, bytes_read);

        //buffer was not big enough to hold the whole line, continue reading the line
        if (buffer[bytes_read -1] != '\n') {
            newline = 0;
        }
        else {
            newline = 1;
        }
    }
    return 0;
}