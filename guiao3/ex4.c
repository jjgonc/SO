#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//nao esta a funcionar....

int main (int argc, char* argv[]) {
    int exec_ret;
    //char* exec_args = {"./a.out", "ola", "mundo", NULL};
    exec_ret = execv("ex3", argv);  //o primeiro argumento é o nome do executavel do exercicio 3 (pq fiz gcc ex3.c -o ex3), se nao tivesse feito passava a.out!!!
    perror ("exec!");

    return exec_ret;
}