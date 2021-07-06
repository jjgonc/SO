#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char * argv[]) {
    int i=0;
    int bytes_written;
    for (i=0; i < argc; i++) {
        bytes_written = write (1, argv[i], strlen(argv[i]));
        if (bytes_written < 1) {
            perror ("write error!");
        }
        //write (1, " ", 1);       para aparecer tudo na mesma linha
        write (1, "\n", 1); //devia na mesma igualar a uma var e ver se escreveu bytess e se correu tudo bem, mas como é so um \n nao ha problema
    }
    return 0;
}