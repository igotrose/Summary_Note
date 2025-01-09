#include<stdio.h>

void InsertionSort(int arr[], int sz)
{
    for (int i = 1; i < sz; i++)
    {
        int base = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > base)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = base;
    }
}

int main()
{
    int arr[] = {3, 4, 1, 6, 7, 5, 2, 9, 8};
    int sz = sizeof(arr)/sizeof(arr[0]);
    InsertionSort(arr, sz);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}