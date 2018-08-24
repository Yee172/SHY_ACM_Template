#include <bits/stdc++.h>
using namespace std;

namespace mobius_mu_sieve
{
    typedef long long TYPE;
    const TYPE MAXN = 1000050;
    vector<TYPE> prime;
    bool vis[MAXN];
    int mu[MAXN];
    void mobius_mu_sieve()
    {
        mu[0] = 0, mu[1] = 1;
        for (TYPE i = 2; i < MAXN; i++)
        {
            if (!vis[i]) prime.push_back(i), mu[i] = -1;
            for (TYPE j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
            {
                vis[i * prime[j]] = true;
                if (i % prime[j]) mu[i * prime[j]] = -mu[i];
                else
                {
                    mu[i * prime[j]] = 0;
                    break;
                }
            }
        }
    }
}
