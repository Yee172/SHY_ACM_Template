#include <bits/stdc++.h>
using namespace std;

namespace partition
{
    const int MOD = 0x3b9aca07;

    namespace fast_mod_operation
    {
        inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
        inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    }
    using fast_mod_operation::__add__;
    using fast_mod_operation::__sub__;

    inline int pentagon_number(int n) { return 3 * n * n - n >> 1; }

    const int MAXN = 100050;
    int pentagon[MAXN];
    bool dp_add[MAXN];
    int partition_number[MAXN];

    inline void initialize()
    {
        pentagon[0] = 0;
        dp_add[0] = false;
        for (int i = 1, j = 1, k = 2; ; ++i, ++(++j), ++(++k))
        {
            pentagon[k] = (pentagon[j] = pentagon_number(i)) + i;
            dp_add[k] = dp_add[j] = i & 1;
            if (pentagon[k] > MAXN) break;
        }
        memset(partition_number, 0, sizeof partition_number);
        partition_number[0] = 1;
        for (int i = 1, j; i < MAXN; ++i)
            for (j = 1; pentagon[j] <= i; ++j)
                partition_number[i] = dp_add[j] ?
                                      __add__(partition_number[i], partition_number[i - pentagon[j]])
                                                :
                                      __sub__(partition_number[i], partition_number[i - pentagon[j]]);
    }
}
using partition::partition_number;
