#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


//NOTA SOBRE wait() :: on success, returns the process ID of the terminated child; on error, -1 is returned.

int main () {
    int i;
    pid_t pid;
    int status;
    for (i=0; i<10;i++) {
        pid = fork();   //a partir da segunda iteraçao, o filho é que cria o seu proprio filho
        if (pid == 0) {
            printf ("[filho] My pid = %d | My father pid = %d\n", getpid(), getppid());
            //por nao ter aqui o exit, faz com que seja sempre o filho a criar novos filhos (enquanto isso o pai é o mesmo desde o inicio pq esta com o wait)
        }
        else {
            pid_t childpid = wait(&status);
            printf ("[pai] Son number %d with pid %d exited\n", WEXITSTATUS(status), childpid);
            _exit(i);
        }
    }
    //ao sair do ultimo filho a ser criado, vai desbloqueando os waits por ordem inversa à que os filhos foram criados
    _exit(10);   //aqui apenas executa o ultimo filho e vai executar antes dos exits do ciclo for que estao no else (como se  ve no resultado)

    return 0;
}

//FAQ:: o facto de os printfs darem do filho numero 10 ate ao 1 tem alguma logica por tras??
/*
RESPOSTA:: sim, porque como diz no enunciado, "uma descendência em profundidade de dez processos, ou seja, o
processo cria um filho, este filho cria outro, e assim por diante até ao décimo nı́vel de descendência.". Assim, o 
processo 1 depende do 2, o 2 depende do 3, e assim por diante. Logo, podemos concluir que temos que terminar o 10
para posteriormente terminar o 9 e sempre assim até ao 1, uma vez que o processo 9 é pai do 10.

*/