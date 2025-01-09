# 子序列问题
记录一些学习中遇到子序列相关问题  
## 最大子序列和
**现有一序列，需要求出最大的子序列和**   
***穷举法：*** 将所有结果一一列举，并得到最后的答案    

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
*时间复杂度：*$O(N^2)$   
***分治法：*** 将问题划分为若干个子问题，并将若干个子问题的解合并，得到一个完整的解   

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
*时间复杂度：* $O(NlogN)$  
***最优解：*** 

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
*时间复杂度：* $O(N)$  