#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


/* 
> gcc ex1.c 

> ./a.out

Process ID -> 5256
Parent Process ID -> 3381

> ps

  PID TTY          TIME CMD
 3381 pts/0    00:00:00 bash
 5258 pts/0    00:00:00 ps

*/

int main (int argc, char* argv[]) {
    int pid = getpid();
    int ppid = getppid();
    printf ("Process ID -> %d\n", pid);
    printf ("Parent Process ID -> %d\n", ppid);
    return 0;
}