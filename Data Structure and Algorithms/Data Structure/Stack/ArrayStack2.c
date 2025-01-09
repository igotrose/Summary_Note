#include <stdio.h>

#define Max 100

typedef struct
{
    int data[Max];
    int top;
}Stack;

void InitStack(Stack* stack)
{
    stack->top = -1;
}

int IsStackEmpty(Stack* stack)
{
    return (stack->top == -1);
}

void Push(Stack* stack, int element)
{
    if (stack->top == Max - 1) 
    {
        printf("FULL");
        return; 
    }
    stack->data[++stack->top] = element;
}

int Pop(Stack* stack)
{
    if (stack->top == -1)
    {
        printf("EMPTY");
        return -1;
    }
    return stack->data[stack->top--];
}

int main()
{
    Stack S;
    InitStack(&S);

    Push(&S, 1);
    Push(&S, 2);

    for (int i = 0; i <= S.top; i++) 
        printf("%d ", S.data[i]);
    printf("\n");
    printf("%d\n", Pop(&S));
    return 0;   
}
