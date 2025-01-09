#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct SingleLinkedList 
{
    struct SingleLinkedList* next;
    int element;
}SLL;

SLL* CreatHeader()
{
    SLL* p = malloc(sizeof(SLL));
    assert(p);
    p->next = NULL;
    return p;
}

void JudgeIsEmpty(SLL* header)
{
    assert(header);
    if (header->next == NULL)
    {
        printf("this is an empty single linked list\n");
    }
    else
    {
        printf("this isn't an empty single linked list\n");
    }
}

void InsertFront(SLL* header, int x)
{
    assert(header);
    SLL* tmp = (SLL*)malloc(sizeof(SLL));
    assert(tmp);
    tmp->element = x;
    tmp->next = header->next;
    header->next = tmp;
}

void InsertTail(SLL* header, int x)
{
    assert(header);
    SLL* p = header;
    SLL* tmp = (SLL*)malloc(sizeof(SLL));
    assert(tmp);
    tmp->element = x;
    tmp->next = NULL;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = tmp;
}

void InsertOrder(SLL* header, int x)
{
    assert(header);
    SLL* tmp = (SLL*)malloc(sizeof(SLL));
    assert(tmp);
    tmp->element = x;
    SLL* p = header->next;
    if (p == NULL || p->element >= x)
    {
        tmp->next = p;
        header->next = tmp;
    }
    else
    {
        while ((p->next != NULL) && (p->next->element) < x)
        {
            p = p->next;
        }
        tmp->next = p->next;
        p->next = tmp;
    }
}

SLL* Find(SLL* header, int x)
{
    assert(header);
    SLL* p = header->next;
    while (p != NULL && p->element != x)
    {
        p = p->next;
    }
    return p;
}

int FindNodeth(SLL* header, int x)
{
    assert(header);
    int count = 1;
    SLL* p = header->next;
    while (p != NULL && p->element != x)
    {
        count++;
        p = p->next;
    }
    if (p == NULL)
    {
        count = -1;
    }
    return count;
}

void Delete(SLL* header, int x)
{
    assert(header);
    SLL* p = Find(header, x);
    SLL* pre = header;
    while (pre->next != p)
    {
        pre = pre->next;
    }
    if (p != NULL)
    {
        pre->next = p->next;
        free(p);
    }
    else
    {
        printf("the element you want to delete is not exist!\n");
    }
}

void Modify(SLL* header, int x, int y)
{
    assert(header);
    SLL* p = header->next;
    while(p != NULL)
    {
        if (p->element == x)
        {
            p->element = y;
            break;
        }
        else
        {
            p = p->next;
        }
    }
}

SLL* Merge_SLL(SLL* header1, SLL* header2)
{
    assert(header1 && header2);
    SLL* H3 = (SLL*)malloc(sizeof(SLL));
    SLL* p1 = header1->next;
    SLL* p2 = header2->next;
    SLL* p3 = H3;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->element < p2->element)
        {
            p3->next = p1;
            p1 = p1->next;
        }
        else
        {
            p3->next = p2;
            p2 = p2->next;
        }
        p3 = p3->next;
    }
    p3->next = (p1 == NULL ? p2 : p1);
    return H3;
}

void PrintList(SLL* header)
{
    assert(header);
    SLL* p = header->next;
    printf("Single linked list: ");
    while (p != NULL)
    {
        printf("%d ", p->element);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    // 有序插入
    SLL* L = CreatHeader();
    InsertOrder(L, 10);
    InsertOrder(L, 20);
    InsertOrder(L, 5);
    InsertOrder(L, 15);
    InsertOrder(L, 30);
    InsertOrder(L, 40);
    PrintList(L);
    return 0;
}