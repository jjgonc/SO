#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> //include onde se encontra o WEXITSTATUS, WIFEXITED, etc...


int mysystem (char * command) {
    char *exec_args[20];
    int i=0;
    char *string;
    int exec_ret;
    int status;
    int wait_ret;
    int res;
    int pid;
    
    string = strtok (command, " ");

    //colocar todos os commandos num array

    while (string != NULL) {
        exec_args[i] = string;
        string = strtok (NULL, " "); //quando lhe passo o 1o argumento a NULL, ele mantem no ponto em que estava e procura o proximo espaço
        i++;
    }

    exec_args[i] = NULL;    // DUVIDA:: poderia ser o caracter \0 ?????

    //o filho criado faz um comando para que o programa nao termmine
    pid = fork();
    if (pid==0) {
        exec_ret = execvp (exec_args[0], exec_args);
        _exit(exec_ret);
    }

    else {
        if (pid != -1) {
            wait_ret = waitpid (pid, &status, 0);   //tbm funcionaria se fosse o wait normal

            if (WIFEXITED(status)) {    //verificar se terminou corretamente
                res = WEXITSTATUS(status);
            }
            else res = -1;
        }
        else res = -1;
    }
    return res;
}



int main () {
    char comando1 [] = "ls -l -a -h";
    char comando2 [] = "sleep 10";
    char comando3 [] = "ps";
    int ret;

    printf ("a executar mysystem para %s\n", comando1);
    ret = mysystem(comando1);
    printf ("ret returned %d\n", ret);

    printf ("a executar mysystem para %s \n", comando2);
    mysystem (comando2);

    printf ("a executar mysystem para %s \n", comando3);
    mysystem (comando3);

    return 0;
}