#include <bits/stdc++.h>
using namespace std;

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
