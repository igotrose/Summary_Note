#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct FlexibleArray
{
    int length;
    int data[];
}FA;

FA* CreateFA(int length)
{
    FA* fa = (FA*)malloc(sizeof(FA) + length * sizeof(int));
    assert(fa);
    fa->length = length;
    return fa;
}

int main()
{
    FA* fa = CreateFA(10);
    for (int i = 0; i < 10; i++)
    {
        fa->data[i] = i*10;
        printf("%d ", fa->data[i]);
    }
    printf("\n");
    free(fa);
    return 0;
}