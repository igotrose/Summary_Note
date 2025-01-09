#include<stdio.h>

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SelectionSort(int arr[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        int minindex = i;
        for (int j = i + 1; j < sz; j++)
        {
            if (arr[j] < arr[minindex])
                minindex = j;
        }
        Swap(&arr[i], &arr[minindex]);
    }
}

int main()
{
    int arr[] = {3, 4, 5, 1, 2, 9, 8, 7, 6, 10};
    int sz = sizeof(arr)/sizeof(arr[0]);
    SelectionSort(arr, sz);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}