#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main (int argc, char * argv) {
    int fifo_fd;
    int read_bytes = 0;
    char buffer[1024];
    
    fifo_fd = open("fifo", O_RDONLY);
    
    while ((read_bytes = read(fifo_fd, buffer, 1024)) > 0){
        write(1, buffer, read_bytes);
    }
    
    close (fifo_fd);
    unlink("fifo");
    return 0;
}