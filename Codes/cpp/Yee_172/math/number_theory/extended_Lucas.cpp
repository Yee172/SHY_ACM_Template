#include <bits/stdc++.h>
using namespace std;

namespace extended_Lucas
{
    namespace euler_sieve
    {
        typedef int TYPE;
        const TYPE MAXN = 10050;
        TYPE prime[MAXN];
        int cnt = 0;
        bool vis[MAXN];
        void euler_sieve()
        {
            vis[0] = vis[1] = true;
            for (TYPE i = 2; i < MAXN; i++)
            {
                if (!vis[i]) prime[cnt++] = i;
                for (TYPE j = 0; j < cnt, i * prime[j] < MAXN; j++)
                {
                    vis[i * prime[j]] = true;
                    if (i % prime[j] == 0) break;
                }
            }
        }
    }
    using euler_sieve::prime;

    namespace Chinese_remainder_theorem
    {
        inline int __mul__(long long a, const int b, const int mod)
        {
            a *= b;
            a = a < 0 ? a - a / mod * mod + mod : a;
            return (int) (a < mod ? a : a - a / mod * mod);
        }

        void extended_gcd(int a, int b, int &d, int &x, int &y)
        {
            if (!b) { d = a; x = 1; y = 0; }
            else { extended_gcd(b, a % b, d, y, x); y -= x * (a / b); }
        }

        int CRT(const int n, const int a[], const int r[])
        {
            int m2, r2, i, d, x, y, c, t;
            int m1 = a[0];
            int r1 = r[0];
            bool no_solution = false;
            for (i = 1; i < n; ++i)
            {
                m2 = a[i];
                r2 = r[i];
                extended_gcd(m1, m2, d, x, y);
                c = r2 - r1;
                if (c % d)
                {
                    no_solution = true;
                    break;
                }
                t = m2 / d;
                x = __mul__(x, c / d, t);
                r1 += m1 * x;
                m1 = m1 / d * m2;
            }
            if (no_solution) return -1;
            if (n == 1 && r1 == 0) return m1;
            return r1;
        }
    }
    using Chinese_remainder_theorem::extended_gcd;
    using Chinese_remainder_theorem::CRT;

    inline int __mul__(long long a, const int b, const int mod) { a *= b; return (int) (a < mod ? a : a - a / mod * mod); }
    inline int __pow__(int a, long long b, const int mod) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a, mod)) if (b & 1) r = __mul__(r, a, mod); return r; }
    inline int __mod__(long long a, const int mod) { return (int) (a < mod ? a : a - a / mod * mod); }

    int fac[1000050];
    inline int factorial(long long n, const int p, const int pk)
    {
        int res = 1;
        fac[0] = 1;
        for (int i = 0, ui = pk / p; i < ui; ++i)
        {
            for (int j = i * p + 1, uj = i * p + p; j < uj; ++j) fac[j] = __mul__(fac[j - 1], j, pk);
            fac[i * p + p] = fac[i * p + p - 1];
        }
        while (n)
        {
            res = __mul__(res, __mul__(__pow__(fac[pk], n / pk, pk), fac[__mod__(n, pk)], pk), pk);
            n /= p;
        }
        return res;
    }

    inline int __inv__(const int a, const int mod)
    {
        int d, x, y;
        extended_gcd(a, mod, d, x, y);
        x = x < 0 ? x - x / mod * mod + mod : x;
        return x < mod ? x : x - x / mod * mod;
    }

    inline int binomial(long long n, long long k, const int p, const int pk)
    {
        if (n < k) return 0;
        if (n == k || k == 0) return 1;
        int exponential = 0;
        for (long long i = n; i; exponential += (i /= p));
        for (long long i = k; i; exponential -= (i /= p));
        for (long long i = n - k; i; exponential -= (i /= p));
        return __mul__(__mul__(__mul__(factorial(n, p, pk), __inv__(factorial(k, p, pk), pk), pk), __inv__(factorial(n - k, p, pk), pk), pk), __pow__(p, exponential, pk), pk);
    }

    int a[105], b[105];
    inline int extended_Lucas(const long long n, const long long k, const int mod)
    {
        int tmp = mod, cnt = 0, pk;
        for (int i = 0, p = prime[i], ui = (int) sqrt(tmp) + 3; p < ui; p = prime[++i]) if (tmp % p == 0)
            {
                for (pk = 1; tmp % p == 0; pk *= p, tmp /= p);
                a[cnt] = pk, b[cnt++] = binomial(n, k, p, pk);
            }
        if (tmp > 1) a[cnt] = tmp, b[cnt++] = binomial(n, k, tmp, tmp);
        return __mod__(CRT(cnt, a, b), mod);
    }
}
