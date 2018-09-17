#include <bits/stdc++.h>
using namespace std;

namespace sqrt_k
{
    inline ll _pow(ll a, ll b)
    {
        ll res = 1;
        for (; b; b >>= 1)
        {
            if (b & 1)
            {
                if (a > ((1e18 + 1e5) / res)) return -1;
                res *= a;
            }
            if (b > 1 && a > (1ll << 31)) return -1;
            a *= a;
        }
        return res;
    }

    ll sqrt_k(ll n, ll k)
    {
        ll res = static_cast<ll>(pow(n, 1. / k));
        for (ll i = _pow(res + 1, k); i <= n && i != -1; res++, i = _pow(res + 1, k));
        for (ll i = _pow(res, k); i > n || i == -1; res--, i = _pow(res, k));
        return res;
    }
}
