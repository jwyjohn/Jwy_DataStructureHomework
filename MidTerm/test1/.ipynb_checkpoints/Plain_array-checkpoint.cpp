#define MAXN 1000003
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

int a[MAXN], N, M;

long long sum(int l, int r)
{
    long long sum = 0;
    for (int i = l; i <= r; i++)
        sum += a[i];
    return sum;
};

int main()
{
    memset(a, 0, sizeof(a));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]);
    };
    int l, r;
    for (int j = 0; j < M; j++)
    {
        scanf("%d%d", &l, &r);
        printf("%lld\n", sum(l, r));
    };
    return 0;
};