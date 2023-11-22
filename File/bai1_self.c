#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main (int ac ,char* argv[])
{
char *buffer;
printf("agrc0la: %s \n", argv[0]);
printf("aac: %d \n", ac);
int fd;
buffer=(char *) malloc(100);
if( (fd= open(argv[1] , O_RDONLY)) )
{
    lseek(fd, atoi(argv[2]), atoi(argv[3]) );
    while(read(fd,buffer,100) != 0)
        puts(buffer);
}
free(buffer);
close(fd);
return 0;
}