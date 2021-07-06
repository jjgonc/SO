#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main (int argc, char * argv[]) {
    int fifo_res;
    fifo_res = mkfifo ("fifo", 0666);
    printf ("FIFO created: %d\n", fifo_res);
    if (fifo_res != 0) {
        perror ("mkfifo error!");
        return -1;
    }
    return 0;
}