#define READ


#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int readlnC(int fd, char *c);
ssize_t readln(int fd, char *line, size_t size);
