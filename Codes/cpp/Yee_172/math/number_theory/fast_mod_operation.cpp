#include <bits/stdc++.h>
using namespace std;

namespace fast_mod_operation
{
    const int MOD = 0x3b9aca07;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) if (b & 1) r = __mul__(r, a); return r; }
    inline int __mod__(const long long a, const int b) { return (int) (a < b ? a : a - a / b * b); }
    inline int __mod__(const int a) { return a < MOD ? (a < 0 ? a - a / MOD * MOD + MOD : a) : a - a / MOD * MOD; }
}
using fast_mod_operation::__add__;
using fast_mod_operation::__sub__;
using fast_mod_operation::__mul__;
using fast_mod_operation::__pow__;
using fast_mod_operation::__mod__;

namespace fast_mod_operation
{
    const int MOD = 0x3b9aca07;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) if (b & 1) r = __mul__(r, a); return r; }
    inline int __mod__(const long long a, const int b) { return (int) (a < b ? a : a - a / b * b); }
    inline int __mod__(const int a) { return a < MOD ? (a < 0 ? a + MOD : a) : a - a / MOD * MOD; }
}
using fast_mod_operation::__add__;
using fast_mod_operation::__sub__;
using fast_mod_operation::__mul__;
using fast_mod_operation::__pow__;
using fast_mod_operation::__mod__;

namespace fast_mod_operation
{
    const int MOD = 0x3b9aca07;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) if (b & 1) r = __mul__(r, a); return r; }
    inline int __mod__(const long long a, const int b) { return (int) (a < b ? a : a - a / b * b); }
    inline int __mod__(const int a) { return a < MOD ? a : a - a / MOD * MOD; }
}
using fast_mod_operation::__add__;
using fast_mod_operation::__sub__;
using fast_mod_operation::__mul__;
using fast_mod_operation::__pow__;
using fast_mod_operation::__mod__;

inline long long __mul__(long long a, long long b, long long mod)
{
    a = a - a / mod * mod, b = b - b / mod * mod;
    return ((a * b - ((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}

inline long long __mul__(long long a, long long b, long long mod)
{
    a = a - a / mod * mod, b = b - b / mod * mod;
    return ((long long)((long double)a * b - (long double)((long long)((long double)a / mod * b + 1e-3) * mod)) + mod) % mod;
}

inline int __mul__(long long a, const int b, const int mod)
{
    a = a < mod ? a : a - a / mod * mod;
    a = a < 0 ? a - a / mod * mod + mod : a;
    a *= b;
    a = a < 0 ? a - a / mod * mod + mod : a;
    return (int) (a < mod ? a : a - a / mod * mod);
}

inline int mul(int a, int b, int mod)
{
#if !defined(_WIN32) || defined(_WIN64)
    return (int) ((long long) a * b % mod);
#endif
    unsigned long long x = (long long) a * b;
    unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
    asm
    (
        "divl %4; \n\t"
        : "=a" (d), "=d" (m)
        : "d" (xh), "a" (xl), "r" (mod)
    );
    return m;
}
