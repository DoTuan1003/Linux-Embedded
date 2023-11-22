#include<stdio.h>
#include <pthread.h>
#include <string.h>
#include "sum.h"

void *sum_cal1(void *arg)
{   
    for(int i=0;i<500000;i++)
    {
        sum_increa();
    }
    return NULL;
}
void *sum_cal2(void *arg)
{   
    for(int i=0;i<500000;i++)
    {
        sum_increa();
    }

    return NULL;
}

int main()
{
    pthread_t sum_thread2;
    pthread_t sum_thread1;


    pthread_create(&sum_thread1,NULL,sum_cal1,NULL);
    pthread_create(&sum_thread2,NULL,sum_cal2,NULL);

    
    pthread_join(sum_thread1,NULL);
    pthread_join(sum_thread2,NULL);

    
    printf("xin chao , tong la:%d\n",getsum());
}