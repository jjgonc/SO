#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char * argv) {
    int read_bytes;
    char buf[1024];
    int log = open ("log.txt", O_CREAT | O_RDONLY, 0644);
    int fifo_res = mkfifo ("fifo", 0666);
    if (fifo_res != 0) {
        perror ("mkfifo");
        return -1;
    }

    int fifo_fd = open ("fifo", O_RDONLY);
    if (fifo_fd < 0) {
        perror ("open error");
        return -1;
    }

    while ((read_bytes = read (fifo_fd, buf, 1024)) > 0) {
        write(log, buf, read_bytes);
        write(log, "\n", 1);
    }
    close(fifo_fd);

    close(log);
    unlink("fifo");
}


/*
gcc ex2_server.c -o server
./server
*/