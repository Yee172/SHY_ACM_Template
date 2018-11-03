#include <bits/stdc++.h>
using namespace std;

namespace NTT
{
    int MOD = 0x3be00001;
    const int g = 3;

    namespace fast_mod_operation
    {
        inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
        inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
        inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
        inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) { if (b & 1) r = __mul__(r, a); } return r; }
    }
    using fast_mod_operation::__add__;
    using fast_mod_operation::__sub__;
    using fast_mod_operation::__mul__;
    using fast_mod_operation::__pow__;

    inline int get_bit(int x) { for (; x != (x & -x); x += x & -x); return x; }
    inline int reverse(int x, int r) { int res = 0; for (int i = 0; i < r; ++i) if (x & (1 << i)) res += 1 << (r - i - 1); return res; }

    void ntt(int * A, int n, int mode=1)
    {
        int r = 0, cnt = 0, t = n;
        for (; t > 1; ++cnt, t >>= 1);
        for (; ; ++r) if ((1 << r) == n) break;
        for (int i = 0; i < n; ++i)
        {
            int tmp = reverse(i, r);
            if (i < tmp) swap(A[i], A[tmp]);
        }
        for (int s = 1; s <= r; ++s)
        {
            int m = 1 << s;
            int p = m >> 1;
            int wn = __pow__(g, (MOD - 1) / m);
            for (int k = 0; k < n; k += m)
            {
                int w = 1;
                for (int j = 0; j < p; ++j)
                {
                    int x = A[k + j], y = __mul__(w, A[k + j + p]);
                    A[k + j] = __add__(x, y);
                    A[k + j + p] = __sub__(x, y);
                    w = __mul__(w, wn);
                }
            }
        }
        if (mode == -1)
        {
            int inv = __pow__(1 << cnt, MOD - 2);
            for (int i = 1; i < n / 2; ++i) swap(A[i], A[n - i]);
            for (int i = 0; i < n; ++i) A[i] = __mul__(A[i], inv);
        }
    }

    void __mul__(int * A, int A_n, int * B, int B_n, int * C)
    {
        int bit = get_bit(A_n + B_n + 1);
        memset(A + A_n + 1, 0, sizeof(int) * (bit - A_n - 1));
        memset(B + B_n + 1, 0, sizeof(int) * (bit - B_n - 1));
        ntt(A, bit), ntt(B, bit);
        for (int i = 0; i < bit; ++i) C[i] = __mul__(A[i], B[i]);
        ntt(C, bit, -1);
    }
}
using NTT::get_bit;
