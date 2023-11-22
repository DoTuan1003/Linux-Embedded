#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
void main()
{
	int shm_fd;
	const char* message= "\nhello\n";
	void *ptr;
	
	shm_fd=shm_open("hello", O_CREAT | O_RDWR  ,0666);
	ftruncate(shm_fd,4096);
	
	ptr=mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	strcpy(ptr,message);
	return;
	
}
