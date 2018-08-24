#include <bits/stdc++.h>
using namespace std;

namespace generate_factors
{
    typedef long long TYPE;
    map<TYPE, int> generate_factors(TYPE n)
    {
        map<TYPE, int> factors;
        TYPE f = 2;
        while (f * f <= n)
        {
            while (n % f == 0)
            {
                factors[f]++;
                n /= f;
            }
            f++;
        }
        if (n > 1) factors[n]++;
        return factors;
    }
}

namespace generate_factors
{
    namespace euler_sieve
    {
        typedef long long TYPE;
        const TYPE MAXN = 1000050;
        vector<TYPE> prime;
        bool vis[MAXN];
        void euler_sieve()
        {
            vis[0] = vis[1] = true;
            for (TYPE i = 2; i < MAXN; i++)
            {
                if (!vis[i]) prime.push_back(i);
                for (TYPE j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
                {
                    vis[i * prime[j]] = 1;
                    if (i % prime[j] == 0) break;
                }
            }
        }
    }
    using namespace euler_sieve;

    map<TYPE, int> generate_factors(TYPE n)
    {
        map<TYPE, int> factors;
        for (auto f : prime)
        {
            if (f * f > n) break;
            while (n % f == 0)
            {
                factors[f]++;
                n /= f;
            }
        }
        if (n > 1) factors[n]++;
        return factors;
    }
}

