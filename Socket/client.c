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
	int sockfd =-1;
	struct sockaddr_in server_addr;
	char *recv_buffer=NULL;
	time_t ticks;
	int size=0;
	FILE *fp=NULL;
	int write;
	int count=0;
	char temp[10];
	int size1=0;
	

	memset(&server_addr,0,sizeof(server_addr));
	memset(temp,0,10);
	
	sockfd =socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port =	htons(9023);
//	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	while(!count)
	{
	if(connect(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr)) ==0)
	{
		if ((read(sockfd,temp,sizeof(temp)-1))<=0)
		{
			printf("no recive data1\n");
			close(sockfd);
			return;
		}
		else
		{
		size1=atoi(temp);
		recv_buffer=(char *)malloc(size1);
		if (!recv_buffer) 
		{
            printf("out of memory\n");
			close(sockfd);
            return;
        }
		memset(recv_buffer,0,size1);
		size=read(sockfd,recv_buffer,size1);
		if(size<=0)
		{
			printf("no recive data\n");
			close(sockfd);
			return;
		}
		fp = fopen("/home/tuan/work/bt_socket/test_recive", "w");
		if(fp != NULL)
		{
			write=fwrite(recv_buffer,size,1,fp);
			if(write<=0)
			{
				printf("write erro\n");
				fclose(fp);
				close(sockfd);
				return;
			}
			free(recv_buffer);
			fclose(fp);
			close(sockfd);
			count=1;
			return;
		}
		}
	}
	}
	
}
