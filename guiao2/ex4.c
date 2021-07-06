#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


//criar 10 processos filhos que são executados em concorrencia
int main () {
    int i;
    int status;
    int pid;

    for (i=0; i<10; i++) {
        pid = fork();
        if (pid == 0) {
            printf("[filho] Filho numero %d cujo pid é %d e o pid do pai é %d \n", i+1, getpid(), getppid());
            _exit(i+1);
        }
    }

    for (i=0; i<10; i++) {  //aqui é so o pai que executa
        int childpid = wait(&status);
        printf("[pai] Sou o pai do filho %d, com o pid %d e o meu pid é %d\n", WEXITSTATUS(status), childpid, getpid());
    }

}

//neste caso, um pai tem varios filhos!

//unica garantia no resultado é que o filho nunca nasce antes de o pai acabar