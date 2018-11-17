#include <bits/stdc++.h>
using namespace std;

namespace Linear_basis
{
    long long linear_basis[64];
    long long query_basis[64];

    inline void initialize() { memset(linear_basis, 0, sizeof linear_basis); }

    inline void insert(long long x)
    {
        if (!x) return;
        for (int i = 63 - __builtin_clzll(x); i >= 0; --i)
        {
            if (!(x >> i)) continue;
            if (!linear_basis[i])
            {
                linear_basis[i] = x;
                return;
            }
            x ^= linear_basis[i];
        }
    }

    inline long long query_maximum()
    {
        long long res = 0;
        for (int i = 63; i >= 0; --i)
            if ((res ^ linear_basis[i]) > res)
                res ^= linear_basis[i];
        return res;
    }

    inline long long query_minimum()
    {
        for (int i = 0; i < 64; ++i)
            if (linear_basis[i])
                return linear_basis[i];
    }

    inline void initialize_query_basis()
    {
        memset(query_basis, 0, sizeof query_basis);
        int cnt = 0;
        for (int i = 0; i < 64; ++i)
        {
            for (int j = i - 1; j >= 0; --j)
                if ((linear_basis[i] >> j) & 1)
                    linear_basis[i] ^= linear_basis[j];
            if (linear_basis[i]) query_basis[cnt++] = linear_basis[i];
        }
    }

    inline long long query(long long k)
    {
        long long res = 0;
        for (int i = 63 - __builtin_clzll(k); i >= 0; --i)
            if ((k >> i) & 1)
                res ^= query_basis[i];
        return res;
    }
}
