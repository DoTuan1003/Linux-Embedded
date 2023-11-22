#include <stdio.h>
    
int main (){

while(1)
{
    static int count = 0;
    if (count % 2 == 0)
        printf("count:%d\n",count);
    else
        printf("count:%d\n",count);
    if(count>5){
        count=0;
    }
    count++;
}
}