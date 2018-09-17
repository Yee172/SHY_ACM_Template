#include <bits/stdc++.h>
using namespace std;

namespace baby_step_giant_step
{
    inline int __mul__(long long a, const int b, const int mod)
    {
        a *= b;
        return (int) (a < mod ? a : a - a / mod * mod);
    }

    inline int __pow__(int a, long long b, const int mod)
    {
        int r = 1;
        for (; b; b >>= 1, a = __mul__(a, a, mod)) if (b & 1) r = __mul__(r, a, mod);
        return r;
    }

    inline int __mod__(const long long a, const int mod) { return (int) (a < mod ? a : a - a / mod * mod); }

    void extend_gcd(int a, int b, int &d, int &x, int &y)
    {
        if (!b) { d = a; x = 1; y = 0; }
        else { extend_gcd(b, a % b, d, y, x); y -= x * (a / b); }
    }

    inline int find_inverse(const int a, const int b, const int mod)
    {
        int x, y, r, d;
        extend_gcd(a, mod, d, x, y);
        r = (int) ((ll) x * b % mod);
        // a * x + mod * y = 1
        // a * r % mod = b
        return r < 0 ? r + mod : r;
    }

    int BSGS(int A, int B, int C) // A^x = B (mod C)
    {
        int buf = __mod__(1, C), D = buf, K, d = 0, tmp, M;
        // small steps
        for (int i = 0; i <= 100; buf = __mul__(buf, A, C), ++i)
            if (buf == B) return i;
        while ((tmp = __gcd(A, C)) ^ 1)
        {
            if (B % __gcd(A, C)) return -1;
            ++d;
            C /= tmp;
            B /= tmp;
            D = __mod__((ll) D * A / tmp, C);
        }
        unordered_map<int, int> H;
        M = (int) ceil(sqrt(C));
        buf = __mod__(1, C);
        for (int i = 0; i <= M; buf = __mul__(buf, A, C), ++i)
            if (H.find(buf) == H.end()) H[buf] = i;
        K = __pow__(A, M, C);
        for (int i = 0; i <= M; D = __mul__(D, K, C), ++i)
        {
            tmp = find_inverse(D, B, C);
            if (tmp >= 0 && H.find(tmp) != H.end()) return i * M + H[tmp] + d;
        }
        return -1;
    }
}
using baby_step_giant_step::BSGS;
