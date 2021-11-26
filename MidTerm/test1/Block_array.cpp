#include<bits/stdc++.h>
using namespace std;

const int N=10000003;
long long n,m,a[N],l[N],r[N],p[N],tag[N],sum[N];
void B()
{
    int k=sqrt(n),t=n/k;if(n%k!=0)t++;
    for(int i=1;i<=t;i++)l[i]=(i-1)*k+1,r[i]=i*k;
    r[t]=n;
    for(int i=1;i<=n;i++)p[i]=(i-1)/k+1;
    for(int i=1;i<=n;i++) sum[p[i]]+=a[i];
}
void U(long long L,long long R,long long d)
{
    long long x=p[L],y=p[R];
    if(x==y)
    {
        for(int i=L;i<=R;i++)a[i]+=d;
        sum[x]+=d*(R-L+1);
    }
    else
    {
        for(int i=x+1;i<y;i++)tag[i]+=d;
        for(int i=L;i<=r[x];i++)a[i]+=d;
        sum[x]+=d*(r[x]-L+1);
        for(int i=l[y];i<=R;i++)a[i]+=d;
        sum[y]+=d*(R-l[y]+1);
    }
}
long long Q(long long L,long long R)
{
    long long x=p[L],y=p[R],s=0;
    if(x==y)
    {
        for(int i=L;i<=R;i++)s+=a[i];
        s+=tag[x]*(R-L+1);
    }
    else
    {
        for(int i=x+1;i<y;i++)s+=sum[i]+tag[i]*(r[i]-l[i]+1);
        for(int i=L;i<=r[x];i++)s+=a[i];
        s+=tag[x]*(r[x]-L+1);
        for(int i=l[y];i<=R;i++)s+=a[i];
        s+=tag[y]*(R-l[y]+1);
    }
    return s;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);;
    B();
    for(int i=1;i<=m;i++)
    {
        long long q,l,r,d;
        // cin>>q>>l>>r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n",Q(l,r));
        // if(q==1){cin>>d;U(l,r,d);}
        // else cout<<Q(l,r)<<endl;
    }
    return 0;
}