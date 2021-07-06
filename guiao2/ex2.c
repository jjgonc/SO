#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>



int main (int argc, char* argv[]) {
    int pid = fork();
    if (pid == 0) {
        printf ("[son] My pid is %d and my father's pid is %d\n", getpid(), getppid());
    }
    else {
        printf ("[father] My pid is %d, my son's pid is %d and my father's pid is %d\n", getpid(), pid, getppid());
    }
    return 0;
}