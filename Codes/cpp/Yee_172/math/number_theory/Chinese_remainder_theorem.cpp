#include <bits/stdc++.h>
using namespace std;

namespace Chinese_remainder_theorem
{
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
            x = ((long long) c / d * x % t + t) % t;
            r1 += m1 * x;
            m1 = m1 / d * m2;
        }
        if (no_solution) return -1;
        if (n == 1 && r1 == 0) return m1;
        return r1;
    }
}
using Chinese_remainder_theorem::CRT;

namespace Chinese_remainder_theorem
{
    inline long long __mul__(long long a, long long b, long long mod)
    {
        a = a - a / mod * mod, b = b - b / mod * mod;
        return ((a * b - ((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
    }

    void extended_gcd(long long a, long long b, long long &d, long long &x, long long &y)
    {
        if (!b) { d = a; x = 1; y = 0; }
        else { extended_gcd(b, a % b, d, y, x); y -= x * (a / b); }
    }

    long long CRT(const int n, const long long a[], const long long r[])
    {
        long long m2, r2, d, x, y, c, t;
        long long m1 = a[0];
        long long r1 = r[0];
        bool no_solution = false;
        for (int i = 1; i < n; ++i)
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
            x = __mul__(c / d, x % t, t);
            r1 += m1 * x;
            m1 = m1 / d * m2;
        }
        if (no_solution) return -1;
        if (n == 1 && r1 == 0) return m1;
        return r1;
    }
}
using Chinese_remainder_theorem::CRT;
