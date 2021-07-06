#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/*
mesmo que fazer:
wc < /etc/passwd > saida.txt 2> erros.txt

wc fica a espera ate receber EOF (ctrl+D)

"<" vai aplicar o wc ao /etc/passwd -> direcionar o stdin para passwd
">" escrever no saida.txt   -> em vez de imprimir no ecra, vai imprimir no saida.txt
"2>" redirecionar tudo o que ofr escrito no stderror no ficheiro erros.txt

*/

int main (int argc, char * argv[]) {
    int res=0;

    int ifd = open ("/etc/passwd", O_RDONLY);
    int ofd = open ("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open ("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2 (ifd, 0);
    res = dup2 (ofd, 1);
    res = dup2 (efd, 2);

    close(ifd);
    close(ofd);
    close(efd);
// O resultado do wc (que seria disposto no terminal) vai ser escrito no saida.txt, porque o que era para ser escrito no terminal (stdout) foi redirecionado para o saida.txt
    res = execlp ("wc", "wc", NULL);    //duvida: COMO SABEMOS QUE O wc VAI SER APLICADO AO /etc/passwd ?????? É por o etc/passwd ser o stdin ?

    return 0;
}