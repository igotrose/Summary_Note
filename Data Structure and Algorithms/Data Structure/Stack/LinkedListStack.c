#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct LinkedListStack
{
    int element;
    struct LinkedListStack* next;
}LLS;

LLS* CreateLLS()
{
    LLS* p = (LLS*)malloc(sizeof(LLS));
    p->next = NULL;
    return p;
}

void push(LLS* header, int element)
{
    assert(header);
    LLS* p = header;
    while (p->next != NULL) 
        p = p->next;
    LLS* tmp = (LLS*)malloc(sizeof(LLS));
    tmp->element = element;
    p->next = tmp;
    tmp->next = NULL;
}

int pop(LLS* header)
{
    assert(header);
    LLS* p = header->next;
    while (p->next != NULL) 
        p = p->next;
    LLS* pre = header;
    while (pre->next != p) 
        pre = pre->next;
    pre->next = p->next;
    int val = p->element;
    free(p);
    return val;
}

void ShowStack(LLS* header)
{
    assert(header);
    LLS* p = header->next;
    while (p != NULL) 
    {
        printf("%d ", p->element);
        p = p->next;
    }
}

int main()
{
    LLS* stack = CreateLLS();
    push(stack, 1);
    push(stack, 2);
    push(stack, 1);
    push(stack, 3);
    int val = pop(stack);
    printf("%d\n", val);
    ShowStack(stack);
    return 0;
}