/*
1º criar/abrir o ficheiro
2º ler e procurar
3º escrever

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "pessoas.h"

//este ficheiro é a main


//chmod +x pscript -> mudar as permissoes para executar
// ./pscript 10


//EX 8 : time ./pessoas -u Pessoa9 20

int main (int argc, char *argv[]) {

    char id[20] = "";   //as aspas so so para inicializar a string

    if (strcmp(argv[1], "-i") == 0) {   //neste caso pq vamos fazer: ./a.out -i ...., logo o argumennto de indice 1 é o -i
        //printf ("linha 28\n");
        int res = new_person (argv[2], atoi(argv[3]));
        //printf ("linha 31\n");
        snprintf(id, 20, "registo %d\n", res);
        int write_res = write(1,id, sizeof(id));
        if (write_res < 0) {
            perror ("error write!");
            return -1;
        }
    }

    if (strcmp(argv[1], "-u") == 0) {           //pesquisar pelo nome
        person_change_age(argv[2], atoi(argv[3]));
    }

    if (strcmp(argv[1], "-o") == 0) {       //pesquisar pelo registo (tempo de procura constante)
        person_change_age_v2(atoi(argv[2]), atoi (argv[3]));
    }

    return 0;
}