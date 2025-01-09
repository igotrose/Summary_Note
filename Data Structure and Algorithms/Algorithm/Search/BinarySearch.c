#include<stdio.h>

int BinarySearch(const int arr[], int goal, int len)
{
    int left = 0, right = len - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < goal)
        {
            left = mid + 1;
        }
        else if (arr[mid] > goal)
        {
            right = mid - 1;
        }
        else 
        {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sz = sizeof(arr) / sizeof(arr[0]);
    int ret = BinarySearch(arr, 6, sz);
    printf("%d", ret);
    return 0;
}