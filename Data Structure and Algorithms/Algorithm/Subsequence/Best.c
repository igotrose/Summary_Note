#include<stdio.h>   

int MaxSubSequenceSum(const int A[], int N)
{
    int thissum = 0, maxsum = 0;
    for (int i = 0; i < N; i++)
    {
        thissum += A[i];
        if (thissum > maxsum)
        {
            maxsum = thissum;
        }
        else if (thissum < 0)
        {
            thissum = 0;
        }
    }
    return maxsum;
}

int main()
{
    int A[] = {4, -3, 5, -2, -1, 2, 6, -2};
    int N = sizeof(A) / sizeof(A[0]);
    int max = MaxSubSequenceSum(A, N);
    printf("%d ", max);
    return 0; 
}  