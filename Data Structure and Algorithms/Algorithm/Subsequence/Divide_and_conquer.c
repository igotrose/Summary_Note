#include<stdio.h>

int MaxSubSum(const int A[], int left, int right)
{
    int mid = (left + right) / 2;
    if (left == right)
    {
        if (A[left] > 0)
            return A[left];
        else
            return 0;
            
    }
    int MaxLeftSum = MaxSubSum(A, left, mid);
    int MaxRightSum = MaxSubSum(A, mid + 1, right);
    int MaxLeftBorderSum = 0, LeftBorderSum = 0;
    for (int i = mid; i >= left; i--)
    {
        LeftBorderSum += A[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    int MaxRightBorderSum = 0, RightBorderSum = 0;
    for (int i = mid + 1; i <= right; i++)
    {
        RightBorderSum += A[i];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int Max3(int MaxLeftSum, int MaxRightSum, int MaxBorderSum)
{
    int max;
    max = MaxLeftSum > MaxRightSum ? MaxLeftSum : MaxRightSum;
    max = max > MaxBorderSum ? max : MaxBorderSum;
    return max;
}

int MaxSubsequenceSum(const int A[], int N)
{
    return MaxSubSum(A, 0, N - 1);
}

int main()
{
    int A[] = {4, -3, 5, -2, -1, 2, 6, -2};
    int N = sizeof(A) / sizeof(A[0]);
    int max = MaxSubsequenceSum(A, N);
    printf("%d ", max);
    return 0; 
}  