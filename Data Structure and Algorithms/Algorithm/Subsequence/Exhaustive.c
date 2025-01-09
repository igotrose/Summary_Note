#include<stdio.h>

int MaxSubsequenceSum(int A[], int N)
{
    int maxsum = 0;
    for (int i = 0; i < N; i++)
    {
        int thissum = 0;
        for (int j = i; j < N; j++)
        {
            thissum += A[j];
            if (maxsum < thissum)
            {
                maxsum = thissum;
            }
        }
    }
    return maxsum;
}

int main()
{
    int A[] = {-2, 11, -4, 13, -5, -2};
    int N = sizeof(A) / sizeof(A[0]);
    int max = MaxSubsequenceSum(A, N);
    printf("max = %d\n", max);
    return 0;
}