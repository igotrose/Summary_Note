#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Heap
{
    int Capacity;
    int Size;
    int* Arr;
}Heap;

Heap* Initialize(int MaxCapacity)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->Arr = (int*)malloc(sizeof(int));
    heap->Capacity = MaxCapacity;
    heap->Size = 0;
    heap->Arr[0] = -1;
    return heap;
}

void Insert(Heap* H, int element)
{
    int i = 0;
    for (i = ++H->Size; H->Arr[i >> 1] > element; i >>= 1)
    {
        H->Arr[i] = H->Arr[i >> 1];
    }
    H->Arr[i] = element;    
}

int DeleteMin(Heap* H)
{
    int i, child;
    int min = H->Arr[1], last = H->Arr[H->Size--];
    for ( i = 1; i * 2 <= H->Size; i = child)
    {
        child = i * 2;
        if (child != H->Size && H->Arr[child + 1] < H->Arr[child])
            child++;
        if (last > H->Arr[child])
            H->Arr[i] = H->Arr[child];
        else
            break;
    }
    H->Arr[child] = last;
    return min;
}

int main()
{
    srand((unsigned)time(NULL));
    Heap* H = Initialize(15);
    for (int i = 0; i < 10; i++)
        Insert(H, rand() / 1000);
    for (int i = 1; i < H->Size; i++)
        printf("%d ", H->Arr[i]);
    printf("\n%d\n", DeleteMin(H));
    for (int i = 1; i < H->Size; i++)
        printf("%d ", H->Arr[i]);
    return 0;
}