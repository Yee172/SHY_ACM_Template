#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 100500

void extend_gcd(ll a, ll b, ll &d, ll &x, ll &y)
{
    if (!b) {d = a; x = 1; y = 0;}
    else {extend_gcd(b, a % b, d, y, x); y -= x * (a / b);}
}

ll chinese_remainder(ll n, const ll a[], const ll r[])
{
    ll m2, r2, i, d, x, y, c, t;
    ll m1 = a[0];
    ll r1 = r[0];
    ll flag = 0;
    for (i = 1; i < n; i++)
    {
        m2 = a[i];
        r2 = r[i];
        extend_gcd(m1, m2, d, x, y);
        //d=extend_gcd(m1,m2);x*m1+y*m2=d;
        c = r2 - r1;
        if (c % d)//对于方程m1*x+m2*y=c，如果c不是d的倍数就无整数解
        {
            flag = 1;
            break;
        }
        t = m2 / d;
        //对于方程m1x+m2y=c=r2-r1,若(x0,y0)是一组整数解,那么(x0+k*m2/d,y0-k*m1/d)也是一组整数解(k为任意整数)
        //其中x0=x*c/d,y0=x*c/d;
        x = (c / d * x % t + t) % t;
        //保证x0是正数，因为x+k*t是解，(x%t+t)%t也必定是正数解(必定存在某个k使得(x%t+t)%t=x+k*t)
        r1 = m1 * x + r1;
        //新求的r1就是前i组的解，Mi=m1*x+M(i-1)=r2-m2*y(m1为前i个m的最小公倍数);对m2取余时，余数为r2；
        //对以前的m取余时，Mi%m=m1*x%m+M(i-1)%m=M(i-1)%m=r
        m1 = m1 * m2 / d;
    }
    if (flag) return -1;
    if (n == 1 && r1 == 0) return m1;
    //结果不能为0
    return r1;
}

ll a[MAXN];
ll r[MAXN];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("../in.txt", "r", stdin);
#endif
    ll k;
    scanf("%lld", &k);
    for (ll i = 0; i < k; i++)
        scanf("%lld%lld", a + i, r + i);
    printf("%lld\n",  chinese_remainder(k, a, r));
    return 0;
}
