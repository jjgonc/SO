#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h> //include onde se encontra o WEXITSTATUS, WIFEXITED, etc...

//EX: >./a.out ps ls ps

//fazer um padrao de forks concorrente para executar os comandos concorrentemente
//ao fazer concorr, correm toddos ao mesmo tempo e o output pode ser variavel

int main (int argc, char * argv[]) {
    int i;
    int pid;
    int exec_ret;
    for (i=1; i<argc; i++) { //i começa a 1 pq o argv[0] é o ./a.out
        pid = fork();
        if (pid == 0) {
            printf ("I'm the child with pid %d and i'm executing command %s\n", getpid(), argv[i]);
            exec_ret = execlp(argv[i], argv[i], NULL);
            perror("reached return");
            _exit(exec_ret);
        }
    }

    int status;
    for (i=1; i<argc; i++) {
        wait(&status);
        printf ("Waiting for children...\n");
        if (WIFEXITED (status)) {
            printf ("o programa retornou com %d\n", WEXITSTATUS(status));
        }
    }
    printf("All the children has been executed\n");
    
    return 0;
}