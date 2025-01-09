#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct ListNode
{
    int element;
    struct ListNode* next;
}ListNode;

typedef struct HashTable 
{
    int tablesize;
    ListNode** arr;
}HashTable;

HashTable* InitializeHashTable(int tablesize)
{
    HashTable* H = (HashTable*)malloc(sizeof(HashTable));
    H->tablesize = tablesize;
    H->arr = (ListNode**)malloc(sizeof(ListNode*) * H->tablesize);
    for (int i = 0; i < H->tablesize; i++)
    {
        H->arr[i] = (ListNode*)malloc(sizeof(ListNode));
        H->arr[i]->next = NULL;
    }
    return H;
}

ListNode* Find(int key, HashTable* H)
{
    int index = Hash(H->tablesize, key);
    ListNode* L = H->arr[index];
    ListNode* P = L->next;
    while (P != NULL && P->element != key)
        P = P->next;
    return P;
}

void Insert(int key, HashTable* H)
{
    ListNode* POS = Find(key, H);
    if (POS == NULL)
    {
        int index = Hash(H->tablesize, key);
        ListNode* L =  H->arr[index];
        POS = (ListNode*)malloc(sizeof(ListNode));
        POS->next = L->next;
        POS->element = key;
        L->next = POS;
    }
}

int Delete(HashTable* H, int element)
{
    int index = Hash(H->tablesize, element);
    ListNode* L = H->arr[index];
    ListNode* p = Find(element, H);
    int val = 0;
    if (p)
    {
        ListNode* pre = L;
        while (pre->next != p)
            pre = pre->next;
        val = p->element;
        pre->next = p->next;
        if (L->next == p)
            H->arr[index] = pre;
        free(p);
        return val;
    }
    else
    {
        printf("the element you want to delete is not exist\n");
        return -1;
    }
}

int Hash(int tablesize, int key)
{
    return key % tablesize;
}

void ShowHashTable(HashTable* H)
{
    for (int i = 0; i < H->tablesize; i++)
    {
        printf(" %d - ", i);
        ListNode* current = H->arr[i]->next;
        while (current != NULL)
        {
            printf("%d -> ", current->element);
            current = current->next;
        }
        printf("NULL \n");
    }
}

int main()
{
    int tablesize = 10;
    HashTable* H = InitializeHashTable(tablesize);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int randnum = rand() % 100; 
        Insert(randnum, H);
    }
    ShowHashTable(H);    
    int val = Delete(H, 64);
    ShowHashTable(H);  
    return 0;
}