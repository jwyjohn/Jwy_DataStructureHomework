#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
struct node
{
    ll l, r;
    mutable ll v;
    node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
    bool operator<(const node &o) const { return l < o.l; }
};
set<node> tree;
auto split(ll pos)
{
    auto it = tree.lower_bound(node(pos, 0, 0));
    if (it != tree.end() && it->l == pos)
        return it;
    it--;
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(node(l, pos - 1, v));
    return tree.insert(node(pos, r, v)).first;
}
void assign(ll l, ll r, ll v)
{
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.insert(node(l, r, v));
}
ll qpow(ll a, ll n, ll p)
{
    ll ans = 1;
    a %= p;
    while (n)
    {
        if (n & 1)
            ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}
ll n, m, seed, vmax;
ll rnd()
{
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}
void add(ll l, ll r, ll v)
{
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}
ll kth(ll l, ll r, ll k)
{
    auto end = split(r + 1);
    vector<pair<ll, ll>> v;
    for (auto it = split(l); it != end; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
    {
        k -= v[i].second;
        if (k <= 0)
            return v[i].first;
    }
    return 0;
}
ll sum_of_pow(ll l, ll r, ll x, ll y)
{
    ll tot = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        tot = (tot + qpow(it->v, x, y) * (it->r - it->l + 1)) % y;
    return tot;
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        int r = read();
        tree.insert(node(i, i, r));
    }
    for (int i = 1; i <= m; ++i)
    {
        ll opr, l , r, x, y;
        opr = read(), l = read(), r = read(), x = read();
        switch (opr)
        {
        case 1:
            assign(l, r, x);
            break;
        case 2:
            printf("%lld\n", kth(l, r, 1));
            break;
        }
    }
    return 0;
}