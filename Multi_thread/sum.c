#include<stdio.h>
#include <pthread.h>
#include <string.h>

unsigned int sum=0;
pthread_mutex_t sumlock1;

void sum_increa()
{

    pthread_mutex_lock(&sumlock1);
    sum+=1;    
    pthread_mutex_unlock(&sumlock1);

}
unsigned int getsum()
{
    unsigned int local_sum=0;

    pthread_mutex_lock(&sumlock1);
    local_sum=sum;
    pthread_mutex_unlock(&sumlock1);
    return local_sum;
}