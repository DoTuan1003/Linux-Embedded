#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main ()
{
	int listenfd =-1;
	int connfd =-1;
	struct sockaddr_in server_addr;
	time_t ticks;
	FILE *fp = NULL;
	char *send_buffer = NULL;
	int size = 0;
    int read = 0;
	int count=0;
	char temp[10];
	int stt=0;

	

	memset(&server_addr,0,sizeof(server_addr));
	memset(temp,0,10);

	
	listenfd =socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port =	htons(9023);
	
	bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	listen(listenfd,10);
	
	while(!stt)
	{
	connfd= accept(listenfd,(struct sockaddr *)NULL, NULL);
    fp = fopen("/home/tuan/work/bt_socket/text", "r");
	if(fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		size=ftell(fp);
		printf("size:%d\n",size);
		if(size<=0)
		{
			printf("file no data\n");
			fclose(fp);
			close(connfd);
			return;
		}
		if(count==0)
		{
		sprintf(temp, "%d", size);
		write(connfd,temp,4);
		count=1;
		}
		send_buffer=(char *)malloc(size);
        if (!send_buffer) 
		{
            printf("out of memory\n");
            fclose(fp);
            close(connfd);
            return;
        }
		memset(send_buffer,0,size);
		fseek(fp,0,SEEK_SET);
		read= fread(send_buffer,size,1,fp);
		if(read>0)
		{
			if((write(connfd,send_buffer,size))==-1)
			{
				printf("write erro\n");
			}
			else
				printf("write sucess\n");
		}
		free(send_buffer);
		fclose(fp);	
		close(connfd);
		close(listenfd);
		stt=1;
		}
		
	}
}