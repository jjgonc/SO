#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


//wExit status -> se for zero encontrou, caso contrarioo nao encontrou
//Sig kill mata um processo -> usamos kill (pid_do_processo, SIGKILL)


/*
n forks 

quando encontrar, saimos do while de waits e mandamos um sigkill (kill (pid, SIGKILL))

nunca fazer kill (-1, SIGKILL) -> verificar sempre o 1º arg
*/


int main (int argc, char * argv[]) {
    //1º - caso o programa nao receba corretamente os argumentos, enviar um perror
    if (argc < 3) {
        perror ("Incorrect usage (./multigrep <word> <file1> <file2>...");
        return -1;
    }

    //number of files is equal to the total number of arguments minus the ./multigrep and the <word> to search for
    // argv = ['multigrep', 'palavra', 'file1', 'file2', NULL];
    // files = ['file1', 'file2', NULL];
    int nFiles = argc - 2;

    int exec_res;
    int status;
    int pids[nFiles];       //store de pid's to kill the processes later

    for (int i = 0; i<nFiles; i++) {
        int pid = fork();
        if (pid == 0) {
            //NOTE:: argv of index 2+i will give iº file of the command we passed
            printf("[SON #%d] grep with pid %d is searching for word %s in file %s \n", i, pid, argv[1], argv[2+i]);
            exec_res = execlp ("grep", "grep", argv[1], argv[2+i], NULL);

            if (exec_res < 0) {
                perror ("execlp of grep");
                _exit(EXIT_FAILURE);
            }
        }
        pids[i] = pid;
    }

    int found = 0;
    int pid;
    int pidFound; //pid of the process that found the word

    while (!found) {
        pid = wait(&status);        //wait returns the pid of the process that was waited for
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) < 255) {
                found = 1;
                pidFound = pid;
                printf ("grep with pid %d found the word\n", pid);
            }
            else {
                printf ("Word not found by pid = %d\n", pid);
            }
        }
        else {
            printf ("[ERROR] WIFEXITED == FALSE!!\n");
        }
    }


    if (!found) {
        printf ("Word is not in any of those files\n");
        return 1;
    }

    for (int i = 0; i<nFiles; i++) {
        printf ("Killing process with pid [%d]...\n", pids[i]);
        if (pidFound != pids[i] && pids[i] != -1) { //prevenir que o pids[i] seja -1 pq kill(-1, ....) tem consequencias GRAVES 
            kill(pids[i], SIGKILL);
        }
    }
    return 0;
}