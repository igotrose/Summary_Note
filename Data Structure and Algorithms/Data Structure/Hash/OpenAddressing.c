#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define EMPTY 0
#define OCCUPIED 1

typedef struct Element
{
    int element;
    int status;
}Element;

typedef struct HashTable
{
    int tablesize;
    Element* Arr;
}HashTable;

int Hash(int element, int tablesize)
{
    return element % tablesize;
}

HashTable* InitializeHashTable(int tablesize)
{
    HashTable* H = (HashTable*)malloc(sizeof(HashTable));
    H->tablesize = tablesize;
    H->Arr = (Element*)malloc(sizeof(Element) * H->tablesize);
    for (int i = 0; i < H->tablesize; i++)
    {
        H->Arr[i].status = EMPTY;
        H->Arr[i].element = -1;
    }
    return H;
}

//  Linear probing
// int Find(HashTable* H, int element)
// {
//     int index = Hash(element, H->tablesize);
//     Element L = H->Arr[index];
//     while (H->Arr[index].element != element && H->Arr[index].status != EMPTY)
//     {
//         index++;
//         if(index >= H->tablesize - 1)
//             index = 0;
//     }
//     return index;
// }

// Quadratic probing
// int Find(HashTable* H, int element)
// {
//     int index = Hash(element, H->tablesize);
//     int offset = 0;
//     while (H->Arr[index].element != element && H->Arr[index].status != EMPTY)
//     {
//         index += 2 * (++offset) - 1;
//         if (index >= H->tablesize)
//             index -= H->tablesize;
//     }
//     return index;
// }

// Double hashing
int Hash2(int element, int tablesize)
{
    return 5 + (element % (tablesize - 5));
}

int Find(HashTable* H, int element)
{
    int index = Hash(element, H->tablesize);
    int offset = Hash2(element, H->tablesize);
    while (H->Arr[index].status != EMPTY && H->Arr[index].element != element)
        index = (index + offset) % H->tablesize;
    return index;
}

void Insert(HashTable* H, int element)
{
    int index = Find(H, element);
    if (H->Arr[index].status == EMPTY)
    {
        H->Arr[index].element = element;
        H->Arr[index].status = OCCUPIED;
    }
}

int Delete(HashTable* H, int element)
{
    int index = Find(H, element);
    int val = H->Arr[index].element;
    H->Arr[index].element = -1;
    H->Arr[index].status = EMPTY;
    return val;
}

void ShowHashTable(HashTable* H)
{
    for (int i = 0; i < H->tablesize; i++)
    {
        printf(" %d --  ", i);
        printf("%d ", H->Arr[i].element);
        printf(" %d \n", H->Arr[i].status);
    }
}
  
int main()
{
    HashTable* H = InitializeHashTable(10);
    int insertnum = -1;
    // srand((unsigned)time(NULL));
    for (int i = 0; i < H->tablesize; i++)
    {
        insertnum = rand() % 100;
        Insert(H, insertnum);
    }
    ShowHashTable(H);
    return 0;
}