#include<stdio.h>

void ShellSort(int arr[], int sz)
{
    int j;
    // gap —— 控制增量
    for (int gap = sz >> 1; gap > 0; gap >>= 1)
    {
        for (int i = gap; i < sz; i += gap)
        {
            int temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

int main()
{
    int arr[] = {3, 4, 5, 1, 2, 9, 8, 7, 6, 10};
    int sz = sizeof(arr)/sizeof(arr[0]);
    ShellSort(arr, sz);
    for (int i = 0; i < sz; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}