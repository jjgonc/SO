#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

//criar 10 processos filhos que sao executados sequencialmente
int main () {
    int i;
    int status;
    int pid, childpid;
    for (i=0; i<10; i++) {
        pid = fork();
        if (pid == 0) {
            printf("[filho] O meu pid é: %d | Pid do meu pai: %d\n", getpid(), getppid());
            _exit(i+1);
        }
        else {
            childpid = wait(&status); //pid de cada filho
            printf ("Son with pid %d is the son number %d\n", childpid, WEXITSTATUS(status));
        }
    }
}

/*
NOTA:: Podia ter sido usado 
        if (WIFEXITED (status) == 1) {
            printf ("Son with pid %d is the son number %d\n", childpid, WEXITSTATUS(status));
        }
        else {
            printf ("erro\n");
        }
        ....
        que, se o filho retornou então WIFEXITED retorna true!!!
*/