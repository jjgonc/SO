
#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>





int mysystem (char * command) {
    char *exec_args[20];
    int i=0;
    char *string;
    int exec_ret;
    int status;
    int wait_ret;
    int res;
    int pid;
    
    string = strtok (command, " "); //guardar a primeira palavra do command em string

    //colocar todos os commandos num array
    while (string != NULL) {
        exec_args[i] = string;
        string = strtok (NULL, " "); //quando lhe passo o 1o argumento a NULL, ele mantem no ponto em que estava e procura o proximo espaço
        i++;
    }

    exec_args[i] = NULL;    // acho que tambem poderia ser o caratec \0

    //o filho criado faz o comando para que o programa nao termmine
    pid = fork();
    if (pid==0) {
        exec_ret = execvp (exec_args[0], exec_args);    //explicar este execvp
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





int main (int argc, char * argv[]) {
    int res = 0;
    int commandIndex = 1;
    int command[1024];

    int ifd, ofd;

    bzero(command, 1024);
    /*
    The  bzero()  function  erases  the  data  in the n bytes of the memory
       starting at the location pointed to by s, by writing zeroes (bytes con‐
       taining '\0') to that area.
    */

    if (strcmp (argv[commandIndex], "-i") == 0) {       //input stuff
    ifd = open (argv[commandIndex+1], O_RDONLY);
    res = dup2(ifd,0);
    close (ifd);
    commandIndex += 2;
    }

    if (strcmp(argv[commandIndex], "-o") == 0) {    //output stuff
        ofd = open (argv[commandIndex+1], O_CREAT, O_TRUNC, O_WRONLY, 0666);
        res = dup2 (ofd, 1);
        close (ofd);
        commandIndex += 2;
    }

    while (commandIndex < argc) {       //storing the arguments in an array
        strcat(command, argv[commandIndex]);
        strcat (command, " ");
        commandIndex++;
    }

    mysystem(command);                  //executing the arguments

    return 0;
}
