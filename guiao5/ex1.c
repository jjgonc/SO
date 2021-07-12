#include  <stdio.h>
#include  <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



/*
se o pai esta a enviar coisa para o filho nao precisamos do de escrita no filho, nem do de leitura no pai

neste caso so ha uma ordem de execuçao (so pode aparecer os printfs de uma maneira) pq o pai tem que escrever no pipe e so dps o filho é que vai ler

neste caso, se o wait estivesse antes do codigo do pai, ocorreria uma deadlock pq o pai esta a espera do filho e o filho tem que esperar pelo pai

*/



int pai2filho () {
    int p[2];
    char line[] = "linha1"; //neste caso so vai receber uma linha
    char buffer[20];
    int res;
    int status;

    if (pipe(p) == -1) {        //em caso de erro, retorna -1
        perror ("pipe error");
        return -1;
    }

    switch (fork()) {

        case -1:
            perror ("fork error");
            return -1;

        case 0:
            //filho
            //fechar descritor de escrita no filho pq so precisamos do de leitura
            close(p[1]);
            //aqui o res é importante para saber quanto lemos realmente
            res = read (p[0], &buffer, sizeof(buffer));     //lê o que está no p[0] para o buffer
            printf ("[FILHO]: read %s from pipe res: %d bytes\n", buffer, res);    //res == 6 pq linha1 tem 6bytes
            close (p[0]);
            _exit(0);

        default:        //default assumne quaisquer outros valores pq o pai fica com o pid do filho
            //pai
            //fechar descritor de leitura no pai
            close(p[0]);
            //sleep(5); //para mostrar que o filho nao anda sem o pai
            write (p[1], &line, strlen(line));      //lê o que está em line para o p[1]
            printf ("[PAI]: wrote line to pipe \n");
            close (p[1]);

            wait(&status); //wait NAO PODIA estar no inicio deste segmento (logo abaixo do default) de codigo!!!! Se nao dava deadlock
    }

    return 0;
}

/*
array line tem a string linha1.
primeiro entra o pai e lê o que está em line para o pipe 1
o filho recebe isso no pipe 0 e lê para o buffer
*/

int main (int argc, char * argv[]) {
    pai2filho();

    return 0;
}
