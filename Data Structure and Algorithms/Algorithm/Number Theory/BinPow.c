// 快速幂

#include <stdio.h>

long long BinPow(long long x, long long y)
{
    if (y == 0)                         // 递归退出条件
        return 1;
    long long ans = BinPow(x, y / 2);   // 递归调用
    if (y % 2)
        return ans * ans * x;           // 说明他的指数是奇数
    else
        return ans * ans;
}

int main()
{
    printf("%lld\n", BinPow(12, 12));
    return 0;
}