#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct DynamicArray
{
    int* da;
    int length;
    int capacity;
}DA;

DA CreateDA(DA arr)
{
    arr.capacity = 5;
    arr.length = 0;
    arr.da = (int*)malloc(sizeof(int) * arr.capacity);
    return arr;
}

DA InitDA(DA arr, int* tmp, int sz)
{
    if(sz + arr.length >= arr.capacity)
    {    
        arr.capacity *= 2;
        arr.da = (int*)realloc(arr.da, sizeof(int) * arr.capacity);
    }
    arr.length = sz;
    memcpy(arr.da, tmp, sizeof(int) * sz);
    return arr;
}

void PrintDA(DA arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.da[i]);
    printf("\n");
}

void InsertTailDA(DA* arr, int num)
{
    assert(arr);
    if (arr->length >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->da = (int*)realloc(arr->da, sizeof(int)* arr->capacity);
    }
    arr->da[arr->length++] = num;
}

void InsertFrontDA(DA* arr, int num)
{
    assert(arr);
    if (arr->length >= arr->capacity)
        arr->da = (int*)realloc(arr->da, sizeof(int)* (arr->capacity *= 2));;
    for (int i = arr->length; i > 0; i--)
        arr->da[i] = arr->da[i - 1];
    arr->da[0] = num;
    arr->length++;
}

void InsertCenterDA(DA* arr, int index, int num)
{
    assert(arr);
    if (arr->length >= arr->capacity) 
    {
        arr->capacity *= 2;
        arr->da = (int*)realloc(arr->da, sizeof(int) * arr->capacity);
    }
    for (int i = arr->length; i > index; i--) 
        arr->da[i] = arr->da[i - 1];
    arr->length++;
    arr->da[index] = num;
}

void DeleteFrontDA(DA* arr)
{
    assert(arr);
    for (int i = 0; i < arr->length; i++) 
        arr->da[i] = arr->da[i + 1];
    arr->length -= 1;
}

void DeleteTailDA(DA* arr)
{
    assert(arr);
    arr->length -= 1;
}

void DeleteCenterDA(DA* arr, int num)
{
    assert(arr);
    for (int i = 0; i < arr->length; i++) 
    {
        if (arr->da[i] == num) 
        {
            for (int j = i; j < arr->length; j++) 
                arr->da[j] = arr->da[j + 1];
            arr->length -= 1;            
        }
    }
}

int compare(const void* arg1, const void* arg2)
{
    return strcmp((char*) arg1, (char*)arg2);
}

void SortDA(DA* arr)
{
    qsort(arr->da, arr->length, sizeof(int), compare);
}


int main()
{
    DA arr = CreateDA(arr);
    int tmp[] = {1, 2, 3};
    int sz = sizeof(tmp) / 4;
    arr = InitDA(arr, tmp, sz);
    InsertTailDA(&arr, 5);
    InsertFrontDA(&arr, 0);
    InsertCenterDA(&arr, 3, 9);
    DeleteFrontDA(&arr);
    DeleteTailDA(&arr);
    DeleteCenterDA(&arr, 3);
    SortDA(&arr);
    PrintDA(arr);
    printf("%d %d", arr.capacity, arr.length);
    return 0;
}