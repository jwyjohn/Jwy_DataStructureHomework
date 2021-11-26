#define MAXN 10000003
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

int a[MAXN], N, M;

int tree[MAXN];

inline int lowbit(int x) { return x & (-x); }

inline void update(int i, int x)
{
    for (int pos = i; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
};
inline int query(int n)
{
    int ans = 0;
    for (int pos = n; pos; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
};
inline int sum(int a, int b)
{
    return query(b) - query(a - 1);
};

int main()
{
    memset(a, 0, sizeof(a));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]);
    };
    for (int i = 1; i <= N; i++)
    {
        update(i, a[i]);
    };
    int l, r;
    for (int j = 0; j < M; j++)
    {
        scanf("%d%d", &l, &r);
        printf("%lld\n", sum(l, r));
    };
    return 0;
};