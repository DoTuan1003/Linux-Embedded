#include <stdio.h>
#include <string.h>

int sum(int i, int n)
{
    int sum = 0;

    for (i = 0; i < n; i++)
        sum = sum + i;

    sum--;

    return sum;
}

int main()
{
    int i = 0;
    int n = 100;
    FILE *fp = NULL;
    char data[128];
    int val = 0;

    fp = fopen("/home/tuan/work/baitap/remote_debug/data", "w");
    memset(data, 0, sizeof(data));
    val = sum(i, n);
    sprintf(data, "sum: %d\n", val);
    fwrite(data, strlen(data), 1, fp);
    fclose(fp);

    return 0;
}