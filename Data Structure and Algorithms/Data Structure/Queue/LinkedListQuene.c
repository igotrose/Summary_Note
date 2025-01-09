#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct LinkedListQuene
{
    int element;
    struct LinkedListQuene* next;
}LLQ;

LLQ* CreateLLQ()
{
    LLQ* header = (LLQ*)malloc(sizeof(LLQ));
    header->next = NULL;
    return header;
}

void push(LLQ* quene, int element)
{
    assert(quene);
    LLQ* p = quene;
    while (p->next != NULL) 
        p = p->next;
    LLQ* tmp = (LLQ*)malloc(sizeof(LLQ));
    tmp->element = element;
    tmp->next = NULL;
    p->next = tmp;
}

int pop(LLQ* quene)
{
    assert(quene);
    LLQ* first = quene->next;
    int val = first->element;
    quene->next = first->next;
    free(first);
    return val;
}

void ShowLLQ(LLQ* quene)
{
    assert(quene);
    LLQ* p = quene->next;
    while (p != NULL) 
    {
        printf("%d " , p->element);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    LLQ* quene = CreateLLQ();
    push(quene, 3);
    push(quene, 4);
    push(quene, 4);

    pop(quene);
    pop(quene);
    
    ShowLLQ(quene);
    return 0;
}