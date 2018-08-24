#include <bits/stdc++.h>
using namespace std;

namespace Miller_Rabin_primality_test
{
    const int ITERATION_TIME = 20;

    inline long long __mod__(long long a, long long MOD) { return a < MOD ? a : a - a / MOD * MOD; }
    inline long long __add__(long long a, long long b, long long MOD) { a += b; return a < MOD ? a : a - MOD; }

    inline long long __mul__(long long a, long long b, long long MOD)
    {
        long long res = 0;
        while (b)
        {
            if (b & 1) res = __add__(res, a, MOD);
            a = __mod__(a << 1, MOD);
            b >>= 1;
        }
        return res;
    }

    inline long long __pow__(long long a, long long b, long long MOD)
    { long long r = 1; for (; b; b >>= 1, a = __mul__(a, a, MOD)) if (b & 1) r = __mul__(r, a, MOD); return r; }

    inline bool test(long long n, long long a, long long d, int p)
    {
        if (n == 2) return true;
        if (n == a) return true;
        if (n & 1 ^ 1) return false;
        a = __mod__(a, n);
        long long t = __pow__(a, d, n);
        bool flag;
        for (int i = 0; i < p; ++i)
        {
            flag = false;
            if (t != 1 && t != n - 1) flag = true;
            t = __mul__(t, t, n);
            if (t == 1 && flag) return false;
        }
        return t == 1;
    }

    inline bool is_prime(long long n)
    {
        if (n < 2) return false;
        srand((unsigned int)time(NULL));
        long long d = n - 1;
        int p = 0;
        while (d & 1 ^ 1) d >>= 1, ++p;
        for (int i = 0; i < ITERATION_TIME; ++i)
            if (!test(n, random() % (n - 1) + 1, d, p))
                return false;
        return true;
    }
}
using Miller_Rabin_primality_test::is_prime;
