#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/*

MANEIRA MAIS FACIL DE FAZER:

int main () {
    int p[2];
    int status;

    if (pipe(p) == -1) {
        perror ("pipe error");
        return -1;
    }

    int pid;

    switch (pid = fork())
    {
    case -1:
        perror("fork error");
        return -1;
    
    //filho
    case 0:
        close (p[1]);
        dup2 (p[0], 0);
        close(p[0]);
        execlp ("wc", "wc", "-l", NULL);
        _exit(0);

    //pai
    default:
        close (p[0]);   //fechar pipe de leitura
        dup2 (p[1], 1);     //ligar stdout do primeiro comando ao extremo de escrita
        close(p[1]);
        execlp ("ls", "ls", "/etc", NULL);
    }

    return 0;
}



//ou em vez do switch:

    pid = fork();

    if (pid == 0) {
        close(p[0]);
        dup2 (p[1], 1);
        close(p[1]);
        execlp ("ls", "ls", "/etc", NULL);
        _exit(0);
    }

    else {
        close(p[1]);
        dup2 (p[0], 0);
        close (p[0]);
        execlp ("wc", "wc", "-l", NULL);
        _exit(0);
    }

*/


//MANEIRA MAIS DIFICIL, POREM MAIS CORRETA (PORQUE??)
//2 processos - 1 pipe
//2 forks - 1 por cada caso

int main () {
    int status;
    int p[2];
    if (pipe(p) == -1) {
        perror("pipe error");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror ("fork error");
        return -1;


    case 0:
        close(p[0]);
        dup2 (p[1], 1); //o output do ls vai para o pipe de escrita
        close(p[1]);
        execlp ("ls", "ls", "/etc", NULL);
        _exit(1);   //caso tenha corrido mal o exit fecha logo o processo e os descritores


    default:
        //fork para o wc
        close(p[1]);
            int pid;
            pid = fork();           //fazer isto para o exec nao terminar o programa (assim so termina o filho)
            if (pid == 0) {
                dup2(p[0], 0);
                close(p[0]);
                execlp ("wc", "wc", "-l", NULL);
                _exit(-1);
            }
            else {
                close(p[0]); //o p[1] foi fechado na linha 102
                //antes dos wait's porque caso contrario causa deadlock nos filhos que estariam à espera que todos os descritores estivessem fechados
                wait(NULL);
                wait(NULL);
            }
            //break;
    }
    return 0;
}