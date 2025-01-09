#include<stdio.h>
#include<string.h>
#include<time.h>

const int MAXNUM = 100000;

int Eratosthene_sieve_method(int* access, int* prime)
{
    int prime_index = 0;
    for (int i = 2; i <= MAXNUM; i++)
    {
        if (access[i] == 0)
            prime[prime_index++] = i;
        for (int j = 2; i * j < MAXNUM; j++)
            access[i*j] = 1;       
    }
    return prime_index;
}

void print(int* prime, int prime_index)
{
    for ( int i = 0; i < prime_index - 1; i++)
    {
        printf("%5d ", prime[i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("\n");
}

int main()
{
    int access[MAXNUM];
    int prime[MAXNUM];
    memset(access, 0, sizeof(access));   
    int count = Eratosthene_sieve_method(access, prime);
    print(prime, count);
    printf("%d\n", count);
    return 0;
} 