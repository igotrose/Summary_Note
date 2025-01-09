#include<stdio.h>

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[right]);
    return i + 1;
    
}

void QuickSort(int arr[], int left, int right)
{
    if (left >= right)
        return;
    int pivot = Partition(arr, left, right);
    QuickSort(arr, left, pivot - 1);
    QuickSort(arr, pivot + 1, right);
}

int main()
{
    int arr[] = {3, 4, 5, 1, 2, 9, 8, 7, 6, 10};
    int sz = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr, 0, sz - 1);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}