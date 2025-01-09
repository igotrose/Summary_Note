#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef struct DoubleLinkedList
{
    int element;
    struct DoubleLinkedList* previous;
    struct DoubleLinkedList* next;
}DLL;

DLL* CreateHeader()
{
    DLL* p = (DLL*)malloc(sizeof(DLL));
    p->next = NULL;
    p->previous = NULL;
    return p;
}

void InsertFront(DLL* header, int element)
{
    assert(header);
    DLL* tmp = (DLL*)malloc(sizeof(DLL));
    assert(tmp);
    tmp->element = element;
    tmp->previous = header;
    tmp->next = header->next;
    header->next = tmp;
}

void InsertTail(DLL* header, int element)
{
    assert(header);
    DLL* tmp = (DLL*)malloc(sizeof(DLL));
    assert(tmp);
    tmp->element = element;
    tmp->next = NULL;
    DLL* p = header;
    while (p->next)
    {
        p = p->next;
    }
    tmp->previous = p;
    p->next = tmp;
}

void InsertOrder(DLL* header, int element)
{
    assert(header);
    DLL* tmp = (DLL*)malloc(sizeof(DLL));
    assert(tmp);
    tmp->element = element;
    DLL* p = header->next;
    if (p == NULL || p->element >= element)
    {    
        tmp->next = header->next;   
        header->next = tmp;
        tmp->previous = header;
    }
    else
    {
        while ((p->next != NULL) && p->element < element)
        {
            p = p->next;
        }
        tmp->next = p->next;
        tmp->previous = p;
        p->next = tmp;
    }
}

void Delete(DLL* header, int element)
{
    assert(header);
    DLL* p = header->next;
    while (p != NULL && p->element != element)
    {
        p = p->next;
    }
    p->previous->next = p->next;
    p->next->previous = p->previous;
    free(p);
}

void PrintList(DLL* header)
{
    assert(header);
    DLL* p = header->next;
    printf("Double linked list: ");
    while (p != NULL)
    {
        printf("%d ", p->element);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    DLL* H1 = CreateHeader();
    InsertFront(H1, 10);
    InsertFront(H1, 9);
    InsertOrder(H1, 12);
    InsertOrder(H1, 12);
    PrintList(H1);

    Delete(H1, 12);
    PrintList(H1);
    return 0;
}
