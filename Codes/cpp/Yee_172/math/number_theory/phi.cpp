#include <bits/stdc++.h>
using namespace std;

namespace phi
{
    typedef long long TYPE;
    TYPE phi(TYPE x)
    {
        TYPE res = x;
        for (TYPE i = 2; i * i <= x; i++)
        {
            if (x % i == 0){
                res = res / i * (i - 1);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) res = res / x * (x - 1);
        return res;
    }
}
