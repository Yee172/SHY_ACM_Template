#include <bits/stdc++.h>
using namespace std;

namespace is_prime
{
    typedef long long TYPE;
    bool is_prime(TYPE n)
    {
        if (n == 2 || n == 3) return true;
        TYPE remain = n % 6;
        if (remain != 1 && remain != 5) return false;
        for (TYPE i = 5; i * i <= n; i += 6)
            if (!min(n % i, n % (i + 2))) return false;
        return true;
    }
}
