#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>

/*
A familia de funções exec substitui o programa (imagem
do processo) em execução num certo processo pelo
novo programa (nova imagem do processo) especificado
como argumento. Caso este exec estaja num filho, apenas
o que é do filho deixa de ser executado (tudo o que é do
pai continua igual).
*/




int main (int argc, char ** argv) {
    int ret;    //so vemos este int se o exec falhar, caso contrario o programa acaba
    char *exec_args[] = {"/bin/ls", "-l", NULL};
//NOTA:: Ao fazer o exec, tudo o que estiver para baixo dele NAO SERA EXECUTADO!
//podia fazer de varias maneiras diferentes, por ex:
    ret = execl ("/bin/ls", "/bin/ls", "-l", NULL);    //ultimo argumento é sempre null pq é para a funçao saber que ja nao ha mais nada
    ret = execlp ("ls", "ls", "-l", NULL);
    ret = execv ("/bin/ls", exec_args);
    ret = execvp ("ls", exec_args);
    printf ("Este printf não é suposto aparecer como output pq caso o exec dê certo, termina o programa...\n");
    printf ("Erro. ret retornou %d\n", ret);
    perror ("Reached return");
    return 0;
}


/*
execl ("/bin/ls", "/bin/ls", "-l", NULL);  

programa substitui o que esta em [0] pelo que esta em [1] e passou os argumento que esta em [2]
*/