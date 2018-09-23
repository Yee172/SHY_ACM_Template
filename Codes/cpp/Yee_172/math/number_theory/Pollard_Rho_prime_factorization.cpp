#include <bits/stdc++.h>
using namespace std;

namespace Pollard_Rho_prime_factorization
{
    namespace Miller_Rabin_primality_test
    {
        const int ITERATION_TIME = 20;

        inline long long __mod__(long long a, long long MOD) { return a < MOD ? a : a - a / MOD * MOD; }
        inline long long __add__(long long a, long long b, long long MOD) { a += b; return a < MOD ? a : a - MOD; }

        inline long long __mul__(long long a, long long b, long long mod)
        {
            a = a - a / mod * mod, b = b - b / mod * mod;
            return ((a * b - ((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
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
    using Miller_Rabin_primality_test::__mod__;
    using Miller_Rabin_primality_test::__add__;
    using Miller_Rabin_primality_test::__mul__;
    using Miller_Rabin_primality_test::is_prime;

    inline long long gcd(long long a, long long b)
    {
        if (!a) return b;
        if (!b) return a;
        int t = __builtin_ctzll(a | b);
        a >>= __builtin_ctzll(a);
        do
        {
            b >>= __builtin_ctzll(b);
            if (a > b) swap(a, b);
            b -= a;
        } while (b);
        return a << t;
    }

    inline void get_max(long long &a, long long &b) { a = a > b ? a : b; }

    const int M = (1 << 7) - 1;
    inline long long get_one_factor(long long n)
    {
        if (n & 1 ^ 1) return 2;
        if (n % 3 == 0) return 3;
        long long x = 0, y = x, t = 1, q = 1, c = __mod__(random(), n - 1) + 1;
        for (int k = 2; ; k <<= 1, y = x, q = 1)
        {
            for (int i = 1; i <= k; ++i)
            {
                x = __add__(__mul__(x, x, n), c, n);
                q = __mul__(q, x > y ? x - y : y - x, n);
                if (!(i & M))
                {
                    t = gcd(q, n);
                    if (t > 1) break;
                }
            }
            if (t > 1 || (t = gcd(q, n)) > 1) break;
        }
        return t;
    }

    long long maximum_prime_factor;
    inline void get_max_prime_factor_dfs(long long n)
    {
        if (n == 1 || n <= maximum_prime_factor) return;
        if (is_prime(n)) { get_max(maximum_prime_factor, n); return; }
        long long p = n;
        while (p == n) p = get_one_factor(n);
        while (n % p == 0) n /= p;
        get_max_prime_factor_dfs(p);
        get_max_prime_factor_dfs(n);
    }

    inline long long get_max_prime_factor(long long n)
    {
        srand((unsigned int)time(NULL));
        maximum_prime_factor = 0;
        get_max_prime_factor_dfs(n);
        return maximum_prime_factor;
    }
}
using Pollard_Rho_prime_factorization::get_one_factor;
using Pollard_Rho_prime_factorization::get_max_prime_factor;
