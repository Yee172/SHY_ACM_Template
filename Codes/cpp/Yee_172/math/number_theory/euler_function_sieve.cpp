#include <bits/stdc++.h>
using namespace std;

namespace euler_function_sieve
{
    typedef long long TYPE;
    const TYPE MAXN = 1000050;
    vector<TYPE> prime;
    bool vis[MAXN];
    TYPE phi[MAXN];
    void euler_function_sieve()
    {
        phi[0] = 0, phi[1] = 1;
        for (TYPE i = 2; i < MAXN; i++)
        {
            if (!vis[i]) prime.push_back(i), phi[i] = i - 1;
            for (TYPE j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
            {
                vis[i * prime[j]] = true;
                if (i % prime[j] == 0)
                {
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }
                else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
