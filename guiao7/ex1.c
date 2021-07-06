#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

int ctrl_c_counter = 0;
int seconds = 0;

void ctrl_c_handler (int signum) {
    printf ("\nReceived[%d] : passaram-se %d segundos\n", signum, seconds);
    ctrl_c_counter++;
}

void ctrl_backslash_handler (int signum) {
    printf ("\nReceived[%d] : carregou %d vezes CTRL+C\n", signum, ctrl_c_counter);
    exit(0);
}

void sigalarm_handler (int signum) {
    seconds++;
    alarm(1);
}




int main (int argc, char * argv[]) {
    printf ("Program started...\n", seconds);

    //registar handlers de sinais
    if (signal (SIGINT, ctrl_c_handler) == SIG_ERR) {
        perror ("SIGINT error");
    }

    if (signal (SIGQUIT, ctrl_backslash_handler) == SIG_ERR) {
        perror ("SIGQUIT error");
    }

    if (signal (SIGALRM, sigalarm_handler) == SIG_ERR) {
        perror ("SIGALRM error");
    }

// o SIGALRM mata o processo por default, mas posso mudar para contar segundos

    // problema que surgia se o alarm estivesse dentro do while: o ctr+c out ctr+\ quebram o pause, o que quebra o alarme pois é reiniciado
    alarm(1);
    while (1) {
        //alarm(1);         //nao funcionava corretamente se fizesse mais que 1 ctrl+c por segundo
        pause();        //so avança quando receber um sinal (neste caso, daqui a 1 seg recebe o alarm do handler do sigalarm)
        //se nao tivesse feito o pause ficava sempre no alarm
    }
    //crtl+c quebra o pause e volta ao alarm
}