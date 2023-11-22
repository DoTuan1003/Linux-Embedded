#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
void main()
{
        int shm_fd;
		char read_buffer[1024];
        void *ptr=NULL;

        shm_fd=shm_open("hello", O_RDONLY,0666);

        ptr=mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
		
        printf("%s",(char*) ptr);
		
		shm_unlink("hello");
        return;

}
