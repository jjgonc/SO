#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h> //include onde se encontra o WEXITSTATUS, WIFEXITED, etc...


int main (int argc, char *argv[]) {
    int status;
    int wait_ret, exec_ret;
    char *exec_args[] = {"/bin/ls", "-l", NULL};

    int pid = fork();
    if (pid == 0) {
        exec_ret = execv ("/bin/ls", exec_args);

        printf ("If this printf returns, there's an error in exec and it returned %d\n", exec_ret);

        _exit(exec_ret);
    }
    else {
        wait_ret = wait(&status);

        printf ("I'm the father and my pid is %d\n", getpid());
        if (WIFEXITED(status)) {
            printf ("[pai] Son returned %d\n", WEXITSTATUS(status));
        }
        else {
            printf("WEXITSTATUS returned false (son didn't end)!\n");
        }
    }
    return 0;
}
