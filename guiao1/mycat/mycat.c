#include <unistd.h> // chamadas ao sistema: definiçoes e declaraçoes essenciais
#include <fcntl.h>  //O_RDONLY, O_WRONLY, O_CREAT, O_*


#define MAX_BUFFER 1024


/*
HOW TO USE:

gcc mycat.c
./a.out

write on terminal and after you hit enter it will post the same string you wrote

*/


int main (int argc, char * argv[]) {
    char buffer[MAX_BUFFER];
    int bytes_read;
    
    while ((bytes_read = read (0, buffer, MAX_BUFFER)) > 0) {   // 0 == stdin
        write (1, buffer, bytes_read);                          // 1 == stdout
    }

    return 0;
}

//read acaba com o \n (ao fazer enter) para dar o write
//se exceder a capacidade do buffer, so escreve os que conseguiu armazenar no buffer