#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int pai2filho () {
    int p[2];
    char * lines[] = {"linha1\n", "linha2\n", "linha3\n", "linha4\n", "linha5\n"};
    char buf;
    int num_lines = 5;
    int status;

    if (pipe(p) == -1) {
        perror ("pipe error");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror ("fork error");
        return -1;
    
    case 0:
        //filho
        //fechar descritor de escrita no filho
        close (p[1]);
        while (read(p[0], &buf, 1) > 0) {       //deveria ter usado o readline
            printf ("[FILHO]: read %c from pipe\n", buf);
        }
        printf ("[FILHO]: out of while\n");
        close (p[0]);
        _exit(0);


    default:
        //pai
        //fechar descritor de leitura no pai
        close (p[0]);
        for (int i = 0; i < num_lines; i++) {
            write (p[1], lines[i], strlen(lines[i]));
            printf ("[PAI]: WROTE %s to pipe\n", lines[i]);
            //sleep(5);
        }
        //fechar extremo de escrita do pai -> leva à situação de EOF e termina o programa
        close(p[1]);
        wait(&status);
        printf ("[PAI] Out of for\n");

    }
    return 0;
}


/*
1º o pai escreve as 5 linhas de line para o pipe de escrita
2º o filho lê as 5 linhas no pipe de leitura para buf
*/
int main () {
    pai2filho();

    return 0;
}