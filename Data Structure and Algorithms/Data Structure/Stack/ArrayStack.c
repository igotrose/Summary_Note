#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ArrayStack
{
    int* arr;
    int length, capacity;    
}AS;

AS CreateAS(AS as)
{
    as.capacity = 10;
    as.arr = (int*)malloc(sizeof(int) * as.capacity);
    as.length = 0;
    return as;
}

void push(AS* as, int element)
{
    assert(as);
    as->arr[as->length++] = element;
}

int pop(AS* as)
{
    assert(as);
    if(as->length == 0)
    {
        printf("empty");
        return -1;
    }
    return as->arr[--as->length];
}

void ShowStark(AS as)
{
    for (int i = 0; i < as.length; i++) 
        printf("%d ", as.arr[i]);
    printf("\n");
}

int main()
{
    AS as = CreateAS(as);
    push(&as, 4);
    push(&as, 4);
    push(&as, 4);

    int val = pop(&as);
    printf("%d\n", val);
    ShowStark(as);
    printf("%d %d", as.capacity, as.length);
    return 0;
}