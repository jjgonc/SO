#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//ctrl + D para acabar de ler!!!

int pai2filho () {
    char ** line;
    char buffer[10];
    int p[2];
    int status;
    int bytes;
    int pid;

    bzero(buffer, 10);

    if (pipe(p) == -1) {
        perror ("pipe error!");
        return -1;
    }
    
    
    switch (pid = fork()) {
    case -1:
        perror ("fork error");
        return -1;
    
    case 0:
        close (p[1]);
        dup2 (p[0], 0);
        close(p[0]);    //depois de ir buscar o stdin, ja nao preciso do p[0]
        printf ("[FILHO] Now stdin is redirected to p[0]\n");     
        execlp ("wc", "/bin/wc", NULL);
        _exit(0);



    default:
        close (p[0]);
        printf("Escreva:\n");
        while ((bytes = read(0, buffer, 10)) > 0) {  //readln(0, buffer, max_line_size)>0
            write (p[1], buffer, bytes);
            buffer[bytes] = '\0';   //para terminar a string
        }
        close(p[1]);
        wait(&status);
        printf ("[PAI] Wrote to pipe\n");
    }
}

int main () {
    pai2filho();

    return 0;
}