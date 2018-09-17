#include <bits/stdc++.h>
using namespace std;

namespace Lucas
{
    int MOD = 0x2717;
    const int MAXN = 100005;
    int factorial[MAXN];
    int mod_inverse[MAXN];
    int factorial_inverse[MAXN];

    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __mod__(const long long a) { return (int) (a < MOD ? a : a - a / MOD * MOD); }

    inline void initialize()
    {
        mod_inverse[0] = 0, factorial[0] = factorial_inverse[0] = mod_inverse[1] = 1;
        for (int i = 1; i < MOD; ++i)
            factorial[i] = __mul__(factorial[i - 1], i);
        for (ll i = 2; i < MOD; i++)
            mod_inverse[i] = __mul__((MOD - MOD / i), mod_inverse[MOD % i]);
        for (ll i = 1; i < MOD; i++)
            factorial_inverse[i] = __mul__(factorial_inverse[i - 1], mod_inverse[i]);
    }

    inline int binomial(int n, int k)
    { return n < k ? 0 : __mul__(factorial[n], __mul__(factorial_inverse[n - k], factorial_inverse[k])); }

    inline int Lucas(long long n, long long k)
    {
        if (n < k) return 0;
        int res = 1;
        while (n && k && res) { res = __mul__(res, binomial(__mod__(n), __mod__(k))); n /= MOD; k /= MOD; }
        return res;
    }
}
