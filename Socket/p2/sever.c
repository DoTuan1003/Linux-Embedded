#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

void main ()
{
	int listenfd =-1;
	int connfd =-1;
	struct sockaddr_in server_addr;
	char send_buffer[1024];
	time_t ticks;
	
	memset(send_buffer,0,sizeof(send_buffer));
	memset(&server_addr,0,sizeof(server_addr));
	
	listenfd =socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("192.168.137.77");
	server_addr.sin_port =	htons(3000);
	
	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	listen(listenfd,10);
	
	while(1)
	{
	connfd= accept(listenfd,(struct sockaddr *)NULL, NULL);
	ticks =time(NULL);
	sprintf(send_buffer,"repply ok %s", ctime(&ticks));
	write(connfd,send_buffer,strlen(send_buffer));
	close(connfd);
	}
	close(listenfd);
}
