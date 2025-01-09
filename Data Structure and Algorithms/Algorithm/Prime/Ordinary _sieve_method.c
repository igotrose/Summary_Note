#include<stdio.h>
#include<math.h>
#include<time.h>
// 判断1~100的素数，打印输出素数和素数的个数

// 时间复杂O(n)
int Ordinary_sieve_method(int n)
{
    if (n == 2)
    {
        printf("%d\n", n);
        return 1;
    }
    int count = 0;
    for (int i = 2; i < n; i++)
    {
        int flag = 1;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }    
        }
        if (flag == 1)
        {
            count++;
            printf("%d\n", i);
        }
    }
    return count;
}
// 优化1 -- 时间复杂度O(n/2)
int Ordinary_sieve_method1(int n)
{
    if (n == 2)
    {
        printf("%d\n", n);
        return 1;
    }
    int count = 0;
    for (int i = 2; i < n; i++)
    {
        int flag = 1;
        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }    
        }
        if (flag == 1)
        {
            count++;
            printf("%d\n", i);
        }
    }
    return count;
}

// 优化2 -- 时间复杂度O(n/2)
int Ordinary_sieve_method2(int n)
{
    if (n == 2)
    {
        printf("%d\n", n);
        return 1;
    }
    int count = 0;
    if (n != 2 && n % 2 == 0)
    {
        printf("%d\n", 2);
        count++;
    }
    for (int i = 3; i < n; i+=2)
    {
        int flag = 1;
        for (int j = 3; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }    
        }
        if (flag == 1)
        {
            count++;
            printf("%d\n", i);
        }
    }
    return count;
}

// 优化3 -- 时间复杂度O(sqrt(n))
int Ordinary_sieve_method3(int n)
{
    if (n == 2)
    {
        printf("%d\n", n);
        return 1;
    }
    int count = 0;
    for (int i = 2; i < n; i++)
    {
        int flag = 1;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }    
        }
        if (flag == 1)
        {
            count++;
            printf("%d\n", i);
        }
    }
    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    clock_t start, end;
    start = clock();
    int count = Ordinary_sieve_method3(n);
    printf("%d\n", count);
    end = clock();
    double last_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("last time :%lf ms", last_time);
    return 0;
}