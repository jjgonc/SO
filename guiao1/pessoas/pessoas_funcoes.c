#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "pessoas.h"




int new_person (char* name, int age) {   //adiciona no final do ficheiro e assume que nao ha repetidos
    
    //criar a pessoa com o nome e idade pretendida
    Person p;
    strcpy(p.name, name);
    p.age = age;

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0644);       //modo de escrita (O_WRONLY), posicionar no fim do ficheiro (APPEND) e criar se nao existir o ficheiro (O_CREAT)
    //verificar se o ficheiro foi corretamente aberto
    if (fd < 0) {
        perror ("open error!");
        return -1;
    }

    int res = write (fd, &p, sizeof(struct Person));
    
    //verificar se foi corretamente escrito
    if (res < 0) {
        perror ("write error!");
        return -1;
    }

    //para o ex 7 (Faça com que a opção -i diga qual a posição no ficheiro do registo inserido...)
    int seek_res = lseek (fd, -sizeof(struct Person), SEEK_CUR);    //este seek vai retornar o offset em bytes. Nós sabemos que cada struct ocupa 16 bytes, logo se dividirmos por 16 o valor retornado pelo lseek, temos a posiçao dessa pessoa
    if (seek_res < 0) {
        perror ("lseek error!");
        return -1;
    }

    //tudo correu bem, entao fechamos o ficheiro e retornamos o
    close (fd);
    return seek_res/(sizeof(struct Person));
}    





int person_change_age (char* name, int age){    //mudar a idade da pessoa pelo seu nome
    int res;
    int pos;
    Person person;  //vamos ler para aqui cada uma das pessoas até encontrar a que pretendemos

    int fd = open (FILENAME, O_RDWR, 0600);
    if (fd<0) {
        perror ("open error!");
        return -1;
    }

    //implementar leitura de pessoa a pessoa para person
    while (read (fd, &person, sizeof(struct Person) ) > 0) {    //NOTA: read retorna o nº de bytes lidos. Neste caso estamos a ler uma struct de cada vez
        //apenas para efeitos de debug:
        printf("Person name is - %s - and this person's age is - %d.\n ", person.name, person.age);
        
        //agora, lemos o registo do ficheiro para a memoria, mudamos a idade (em memoria) e voltamos a escrever o registo com a nova idade no sitio certo do ficheiro 
        if (strcmp (person.name, name) == 0) {  //verificar se é a pessoa com o mesmo nome que procuramos
            person.age = age;

            pos = lseek(fd, -sizeof(struct Person), SEEK_CUR);
            if (pos < 1) {
                perror ("seek error!");
                close(fd);
                return -1;
            }

            //passar da memoria (onde alteramos a idade) para o disco (voltar a colocar no ficheiro)
            int write_res = write (fd, &person, sizeof(struct Person));
            if (write_res < 0) {
                perror ("write error!");
                return -1;
            }

            //apenas para efeito de debug:
            printf("Wrote person name - %s - with age - %d.\n", person.name, person.age);

            close(fd);
            return 1;   //se encontramos e alteramos a idade retorna 1, caso nao se encontre retorna 0
        }
    }

    close(fd);
    return 0; 
}    
    //NOTA: para devolver a posiçao do registo seria apenas dividir por sizeof(struct Person)






int person_change_age_v2 (long pos, int age){   //mudar a idade da pessoa pelo registo
    
    Person p;
    int fd = open (FILENAME, O_RDWR);
    if (fd < 0) {
        perror ("open error!");
        return -1;
    }

    //encontrar o registo correspondente à posiçao dada e posicionar lá
    int lseek_res = lseek (fd, pos*sizeof(struct Person), SEEK_SET);
    if (lseek_res < 0) {
        perror ("lseek error!");
        return -1;
    }

    //uma vez encontrado o registo onde queremos alterar, entao vamos trazer para a memoria e guardar numa variavel em memoria p ( para alterar a idade)
    int bytes_read = read(fd, &p, sizeof(struct Person));
    if (bytes_read < 0) {
        perror ("read error!");
        return -1;
    }

    printf ("Just read person - %s - with age - %d.\n", p.name, p.age);

    p.age = age;    //alterar a idade desse registo NA MEMORIA 


    //voltar a tras no ficheiro para me posicionar no inicio do sitio onde atualizei a idade
    lseek_res = lseek (fd, -sizeof(struct Person), SEEK_CUR);
    if (lseek_res < 0) {
        perror ("lseek error!");
        return -1;
    }

    //uma vez atualizado, vamos voltar a mandar para o disco este pedaço (os 16 bytes da struct) que atualizamos (para o ficheiro)
    int write_res = write (fd, &p, sizeof(struct Person));
    if (write_res < 0) {
        perror ("write error!");
        return -1;
    }

    printf ("Just wrote person - %s - with age - %d.\n ", p.name, p.age);

    close (fd);

    return 0;


}