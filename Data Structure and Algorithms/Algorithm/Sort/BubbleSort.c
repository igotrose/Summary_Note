#include<stdio.h>

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int arr[], int sz)
{
    for (int i = 0; i < sz - 1; i++)
    {
        for (int j = 0; j < sz - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                Swap(&arr[j], &arr[j+1]);
        }
    }
}

void BubbleSortWithFlag(int arr[], int sz)
{
    for (int i = 0; i < sz - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < sz - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j+1]);
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
}

int main()
{
    int arr[] = {3, 4, 5, 1, 2, 9, 8, 7, 6, 10};
    int sz = sizeof(arr)/sizeof(arr[0]);
    // BubbleSort(arr, sz);
    BubbleSortWithFlag(arr, sz);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}