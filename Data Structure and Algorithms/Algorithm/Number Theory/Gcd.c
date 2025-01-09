// 欧几里得算法又名辗转相除法
// 求最大公约数和最小公倍数

#include<stdio.h>

unsigned int Gcd(unsigned int M, unsigned int N)
{
    unsigned int Rem;
    while (N > 0)
    {
        Rem = M % N;
        M = N;
        N = Rem;
    }
    return M;
}

long long gcd(long long m, long long n)
{
    return !n ? m : gcd(n, m % n);
}

long long Lcm(long long m, long long n)
{
    return m / gcd(m, n) * n;
}

int main()
{
    int num = Gcd(50, 15);
    printf("%d\n", num);

    printf("%lld\n", gcd(10, 14));
    printf("%lld\n", Lcm(10, 14));

    return 0;
}