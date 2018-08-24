#include <bits/stdc++.h>
using namespace std;

namespace FWT
{
    const int MOD = 0x3b9aca07;
    const int inv2 = MOD + 1 >> 1;

    inline void FWT_OR(int * x, int len, int mode=1)
    {
        for (int step = 1; step < len; step <<= 1)
            for (int d = step << 1, i = 0; i < len; i += d)
                for (int j = i; j < i + step; ++j)
                {
                    int a = x[j], b = x[j + step];
                    if (mode == -1) x[j + step] = (b - a + MOD) % MOD;
                    else x[j + step] = (a + b) % MOD;
                }
    }

    inline void FWT_AND(int * x, int len, int mode=1)
    {
        for (int step = 1; step < len; step <<= 1)
            for (int d = step << 1, i = 0; i < len; i += d)
                for (int j = i; j < i + step; ++j)
                {
                    int a = x[j], b = x[j + step];
                    if (mode == -1) x[j] = (a - b + MOD) % MOD;
                    else x[j] = (a + b) % MOD;
                }
    }

    inline void FWT_XOR(int * x, int len, int mode=1)
    {
        for (int step = 1; step < len; step <<= 1)
            for (int d = step << 1, i = 0; i < len; i += d)
                for (int j = i; j < i + step; ++j)
                {
                    int a = x[j], b = x[j + step];
                    x[j] = (a + b) % MOD;
                    x[j + step] = (a - b + MOD) % MOD;
                    if (mode == -1)
                    {
                        x[j] = (int)(1ll * x[j] * inv2 % MOD);
                        x[j + step] = (int)(1ll * x[j + step] * inv2 % MOD);
                    }
                }
    }
}
using FWT::FWT_OR;
using FWT::FWT_AND;
using FWT::FWT_XOR;
