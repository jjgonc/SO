#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]) {
    int res;
    int i=0;
    char buffer;
    char line [1024];
    int status;

    int ifd = open ("/etc/passwd", O_RDONLY);
    int ofd = open ("saida.txt", O_TRUNC | O_CREAT | O_WRONLY, 0666);
    int efd = open ("erros.txt", O_TRUNC | O_CREAT | O_WRONLY, 0666);

    //criar as copias dos descritores de ficheiros
    res = dup2 (ifd, 0);
    res = dup2 (ofd, 1);
    res = dup2 (efd, 2);

    close (ifd);
    close (ofd);
    close (efd);    

    int pid = fork();

    if (pid == 0) {
        printf("Sou o filho %d \n", getpid());
        int read_res;

        while (read_res = read (0, &buffer, 1) != 0) {
            line[i] = buffer;
            i++;

            if (buffer == '\n') {   //quado chegar ao \n, significa que acabou a linha, entao escrevemos essa linha
                write (1, line, i); //o descritor 1 (seria do stdoutput) está agora associado ao file saida.txt
                write (2, line, i); //o descritor 2 (seria do stderror) está agora associado ao file erros.txt

                printf ("after writting line");
                i=0;
            }
        }

        _exit(0);
    }

    else {
        printf ("Sou o pai %d \n", getpid());
        wait(&status);

        if (WIFEXITED(status)) {
            printf ("O filho retornou %d\n", WEXITSTATUS(status));
        }
        else {
            printf ("O filho nao terminou (occoreu um erro)\n");
        }
    }
    return 0;
}

