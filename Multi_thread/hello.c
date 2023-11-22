#include<stdio.h>
#include <pthread.h>
#include <string.h>

    char name[20]={0};
    unsigned int sum=0;
    pthread_mutex_t sumlock1;
    pthread_mutex_t sumlock2;
void *sum_cal1(void *arg)
{   
    pthread_mutex_lock(&sumlock1);
    printf("dalaychiakhoa1_thread1\n");
    pthread_mutex_lock(&sumlock2);
    printf("dalaychiakhoa2_thread1\n");
    for(int i=0;i<500000;i++)
    {
        sum+=i;
    }
    pthread_mutex_unlock(&sumlock1);
    printf("damolaychiakhoa1_thread1\n");
    pthread_mutex_unlock(&sumlock2);
    printf("damolaychiakhoa2_thread1\n");
    return NULL;
}
void *sum_cal2(void *arg)
{   pthread_mutex_lock(&sumlock2);
    printf("dalaychiakhoa2_thread2\n");

    pthread_mutex_lock(&sumlock1);
    printf("dalaychiakhoa1_thread2\n");
    for(int i=0;i<500000;i++)
    {
        sum+=i;
    }
    pthread_mutex_unlock(&sumlock2);
    printf("damolaychiakhoa2_thread2\n");
    pthread_mutex_unlock(&sumlock1);
    printf("damolaychiakhoa1_thread2\n");
    return NULL;
}
void *call_name(void *arg)
{
    memset(name,0,sizeof(name));
    printf("nhap ten:");
    fflush(stdin);
    scanf("%s",name);
        return NULL;
}
int main()
{
    pthread_t sum_thread2;
    pthread_t sum_thread1;
    pthread_t name_thread;
    

    pthread_mutex_init(&sumlock1,NULL);
    pthread_mutex_init(&sumlock2,NULL);

    pthread_create(&name_thread,NULL,call_name,NULL);
    pthread_create(&sum_thread1,NULL,sum_cal1,NULL);
    pthread_create(&sum_thread2,NULL,sum_cal2,NULL);

    pthread_cancel(sum_thread1);
    
    pthread_join(sum_thread1,NULL);
    printf("da dung thread1\n");

    pthread_join(sum_thread2,NULL);
    printf("da dung thread2\n");
    pthread_join(name_thread,NULL);

    pthread_mutex_destroy(&sumlock1);
    pthread_mutex_destroy(&sumlock2);
    
    printf("xin chao %s, tong la:%d\n",name,sum);
}