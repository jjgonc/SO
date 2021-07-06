#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


//se tenho extremo de escrita mas nao tenho de leitura, entao esta bloqueado no open
//so quando tiver alguma coisa escrita é que o read vai ler. Caso contrario esta bloqueado até lá
//enquanto tiver um extremo de escrita agora, o read bolqueia


int main (int argc, char * argv[]) {
    int fd;
    int bytes_read = 0;
    char buffer[1024];

    fd = open("fifo", O_WRONLY);
    
    while (bytes_read = read(0, buffer, 1024) > 0) {   //ler do stdin para o buffer
        write(fd, buffer, bytes_read);       //escrever do buffer para o fifo (fd tem o seu descritor)
    }
    
    close(fd);
    return 0;
}