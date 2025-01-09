#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayQuene
{
    int* arr;
    int length;
    int capacity;
}AQ;

AQ CreateAQ(AQ aq)
{
    aq.capacity = 10;
    aq.length = 0;
    aq.arr = (int*)malloc(sizeof(int) * aq.capacity);
    return aq;
}

void Enquene(AQ* aq, int element)
{
    assert(aq);
    aq->arr[aq->length++] = element;
}

int Dequene(AQ* aq)
{
    assert(aq);
    int val = aq->arr[0];
    for (int i = 0; i < aq->length; i++)
        aq->arr[i] = aq->arr[i + 1];
    aq->length--;
    return val;
}

void ShowAQ(AQ* aq)
{
    for (int i = 0; i < aq->length; i++) 
        printf("%d ", aq->arr[i]);
    printf("\n");
}

int main()
{
    AQ aq = CreateAQ(aq);
    Enquene(&aq, 3);
    Enquene(&aq, 5);
    Enquene(&aq, 4);
    printf("%d\n", Dequene(&aq));
    ShowAQ(&aq);
    return 0;
}