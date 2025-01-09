#include "stdio.h"

int main(void)
{
    union Test
    {
        unsigned int n;
        char arr[4];
    };

    union Test num;
    num.n = 0x12345678;
    for (int i = 0; i < 4; i++)
        printf("&arr[%d] = %p, arr[%d] = %#x\n", i, &num.arr[i], i, num.arr[i]);
    
    return 0;
}