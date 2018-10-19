#include <bits/stdc++.h>
using namespace std;

namespace KMP
{
    const int MAXN = 1000050;
    const int MAXM = 10050;
    char a[MAXN];
    int len_a;
    char b[MAXM];
    int len_b;
    int _next[MAXM];

    inline void get_next()
    {
        _next[0] = 0;
        for (int q = 1, k = 0; q < len_b; ++q)
        {
            while (k > 0 && b[q] != b[k]) k = _next[k - 1];
            if (b[q] == b[k]) ++k;
            _next[q] = k;
        }
    }

    inline int kmp() // return index starts from 0, -1 means none
    {
        for (int i = 0, k = 0; i < len_a; ++i)
        {
            while (k > 0 && b[k] != a[i]) k = _next[k - 1];
            if (b[k] == a[i]) ++k;
            if (k == len_b) return i - len_b + 1;
        }
        return -1;
    }
}
