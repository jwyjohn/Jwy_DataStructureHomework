#define MAXN 10000003
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

int a[MAXN], p[MAXN], N, M;

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
    memset(p, 0, sizeof(p));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]);
    };
    p[1] = a[1];
    for (int i = 2; i <= N; i++)
    {
        p[i] = p[i - 1] + a[i];
    };
    int l, r;
    for (int j = 0; j < M; j++)
    {
        scanf("%d%d", &l, &r);
        printf("%lld\n", p[r] - p[l] + a[l]);
    };
    return 0;
};