#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readln.h"

#define MAX_BUF 1024
#define MAX_READ_BUFFER 2048

char read_buffer[MAX_READ_BUFFER];
int read_buffer_pos = 0;
int read_buffer_end = 0;


int readc (int fd, char *c) {
    if(read_buffer_pos == read_buffer_end){
		read_buffer_end = read(fd, read_buffer, MAX_READ_BUFFER);
		switch(read_buffer_end){        //read_buffer_end guarda o nº de bytes lidos / 0 se o ficherio terminar / -1 se ocorrer erros
			case -1:
				perror("read");
				return -1;
			case 0:
				return 0;
				break;
			default:
				read_buffer_pos = 0;
		}
	}
    *c = read_buffer[read_buffer_pos++];

    return 1;
}



ssize_t readln(int fd, char *line, size_t size) {       //line é um buffer
    int res = 0;
    int i = 0;

    while (i<size && (res = readc (fd, &line[i]) > 0)) { //ate o readc dize que ja nao ha mais nada para ler ou excedermos o tamanho max
        i++;
        if (((char*) line) [i-1] == '\n') {
            return i;   //se encontrar um \n dá imediatamente return do nº de bytes lidos
        }
    }
    return i;
}





int main (int argc, char * argv[]) {
    int out = STDOUT_FILENO;                            //DUVIDA:  para que serve isto????
    int line_counter = 0;
    char* buffer = (char *) malloc(MAX_BUF * sizeof(char));
    int bytes_read = 0;
    int newline = 1;

    while ( (bytes_read = readln (0, buffer, MAX_BUF)) > 0) {
        char line_number[10] = "";   //inicializar a string
        //esta funçao vai passar a frente linhas vazias (enters) por causa da condiçao do while
        if (newline && buffer[0] != '\n') {
            snprintf (line_number, 10, "%d:", line_counter);        //DUVIDA:   porque o 10???
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
