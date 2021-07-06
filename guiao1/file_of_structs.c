#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>




//fazer ./a.out ola  -> por exemplo, mas temos que lhe passar um ficheiro

int main (int argc, int argv []) {
    
    int fd = open (argv[1], O_CREAT | O_TRUNC | O_RDWR, O644);

    if (fd < 0) {
        perror ("open error: ");
        return 1;
    }
    
    struct test {
        int i;      //inteiro sao 4 bytes
        char n[10];
    };

    printf ("tamanho: %lu\n", sizeof(struct test));
    
    //create struct t1
    struct test t1;
    t1.i = 10;
    strcpy(t1.n, "zz");

    //create struct t2
    struct test t2;
    t2.i = 4;
    strcpy(t2.n, "pp");

    printf ("Tamanho t1: %lu\n", sizeof(t1));        //size of das variaveis (deve ser o mesmo tamanho que a struct)
    printf ("Tamanho t2: %lu\n", sizeof(t2));

    write (fd, &t1, sizeof(struct test));       //escrever para o descritor n bytes (nº de bytes que ocupa a struct) do valor apontado para a struct t1
    write (fd, &t2, sizeof(struct test));

/*
    usar um destes 2 lseek para posicionar no ponto que quisermos do ficheiro e ler a struct que quisermos (escolher um ou outro conforme queira)
*/  
    lseek (fd, 0, SEEK_SET);     //ir para o inicio do ficheiro (struct t1)
    //lseek (fd, -sizeof(struct test), SEEK_END);      //ir para t2 -> posiciona-se no final do ficheiro e andar para tras 16 bytes (4 do inteiro + 10 da string, que arredonda para 16 pq é o endereço mais prox)

    struct test res; //criar a struct res para colocar la a resposta
    int read_bytes = 0;
    read_bytes = read(fd, &res, sizeof(struct test));

    char output[100];
    sprintf(output, "%d\n", res.i);     //este sprintf vai guardar na variavel output o res.i
    write (1, res.n, strlen(output));
    write (1, "\n", 1);
    write (1, output, strlen(output));

    close(fd);

    return 0;
}