#include <bits/stdc++.h>
using namespace std;

namespace binary_indexed_tree_2D
{
    typedef int TYPE;
    unsigned n, m;
    vector<vector<TYPE> > bit;

    inline void initialize() { bit = vector<vector<TYPE> >(n + 1, vector<TYPE>(m + 1, 0)); }

    inline TYPE sum(const int x, const int y)
    {
        TYPE res = 0;
        for (int i = x; i; i -= i & -i) for (int j = y; j; j -= j & -j) res += bit[i][j];
        return res;
    }

    inline void add(const int x, const int y, const TYPE value)
    {
        for (int i = x; i <= n; i += i & -i) for (int j = y; j <= m; j += j & -j) bit[i][j] += value;
    }

    inline void range_add(const int x1, const int y1, const int x2, const int y2, const TYPE value)
    {
        add(x1, y1, value), add(x1, y2 + 1, -value), add(x2 + 1, y1, -value), add(x2 + 1, y2 + 1, value);
    }
}
