#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>




/*
pipes servem para enviar informaçao de uns para os outros, sinais servem para comunicar uns com os outros

so podemos ter um sinal de cada tipo de cada vez na fila de sinais -> se mandarmos muitos, os outros sao ignorados!!!!

*/



void signal_handler (int signum) {
    printf ("received %d\n", signum);
    sleep(10);
    printf("handled %d\n", signum);
}



int main () {
    printf ("pid: %d\n", getppid());
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    alarm(1);
    pause();
    printf("Continuing execution...\n");
    return 0;
}



/*
tempo = 0;
handler () {
tempo++;
}


while () {
    alarm(1);
    pause()     -> recebe o SIGALARM e desbloqueia (se nao tivesse o pause ficava infinitamente no alarm)...
}


*/