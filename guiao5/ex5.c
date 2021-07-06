#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


//0 é o de leitura e o 1 é o de escrita
// N comandos -> N-1 forks
//tem que ser sempre o pai a criar os pipes para que se possa escrever para la
//mandar para o extremo de escrita para ser lido no extremo de leitura

int main () {
    char * comandos[4] = {"grep -v ^# /etc/passwd ", "cut -f7 -d: ", "uniq ", "wc -l"};
    int numComandos = 4;    //logo Npipes = N-1 = 3!!!
    int p[3][2];    //array de pipes
    
    int pid;
    int status[numComandos];
    int i;

    //O melhor é evitar escrever os pipes todos de uma vez para nao ter que fechar tudo junto. Começamos pelo primeiro pipe
    if (pipe(p[0]) == -1) {
        perror("pipe 0 error");
        return -1;
    }

    int pid0 = fork();   //fazer o fork para o pipe 0
    if (pid0 == 0) { //para o filho
        close(p[0][0]); //fechar o descritor de leitura pq nao vamos precisar (nao temos nada para ler neste momento)
        dup2(p[0][1], 1);   //vamos mudar o stdin para o descritor de escrita para meter la o resultado do grep
        close(p[0][1]);
        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);    //neste comando, o que era suposto ter sido escrito para o terminal (stdin), foi escrito para o descritor de escrita por causa do dup2
        _exit(1);
    }
    close(p[0][1]); //nao precisamos do descritor de escrita do pai




    if (pipe(p[1]) == -1) {
        perror("pipe 1 error");
        return -1;
    }

    int pid1 = fork();    
    if (pid1 == 0) {
        close(p[1][0]); //nao precisamos do descritor de leitura deste pipe
        
        dup2(p[0][0], 0);   //input passa a ser o descritor de escrita do pipe 0, para trabalharmos com esse input  ----> DUVIDA:: pq estou a passar o de leitura do pipe anterior????
        close(p[0][0]); //como ja redirecionamos, já podemos fechar
        dup2(p[1][1], 1);
        close(p[1][1]);
        execlp("cut", "cut", "-f7", "-d:", NULL);
        _exit(1);
    }
    close(p[0][0]); //so tinha sido fechado no filho
    close(p[1][1]);



    if (pipe(p[2]) == -1) {
        perror("pipe 2 error");
        return -1;
    }

    int pid2 = fork();
    if (pid2 == 0) {
        close(p[2][0]);

        dup2(p[1][0], 0);
        close(p[1][0]);
        dup2(p[2][1], 1);
        close(p[2][1]);
        execlp ("uniq", "uniq", NULL);
        _exit(1);
    }
    close(p[1][0]);
    close(p[2][1]); //nao precisamos do descritor de escrita do pai



    int pid3 = fork();
    if (pid3 == 0) {
        dup2(p[2][0], 0);
        close(p[2][0]);
        //ja nao vamos fazer o dup do STDIN (1), como nos de cima, pq vamos querer escrever mesmo no stdin 
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }
    close(p[2][0]);
    close(p[2][1]); //---> duvida: tinhamos que fechar este???? Acho que é indiferente (not sure)


    wait(NULL);
    wait(NULL);
    wait(NULL);
    
    return 0;
}