#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 1000050


vector<ll> prime;
bool vis[MAXN];
void euler_sieve()
{
    for (ll i = 2; i < MAXN; i++)
    {
        if (!vis[i]) prime.push_back(i);
        for (ll j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}


vector<ll> prime;
bool vis[MAXN];
ll phi[MAXN];
void euler_function_sieve()
{
    phi[1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        if (!vis[i]) prime.push_back(i), phi[i] = i - 1;
        for (ll j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}


vector<ll> prime;
bool vis[MAXN];
ll mu[MAXN];
void mobius_mu_sieve()
{
    mu[1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        if (!vis[i]) prime.push_back(i), mu[i] = -1;
        for (ll j = 0; j < prime.size(), i * prime[j] < MAXN; j++)
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


int is_prime(ll n)
{
    if (n == 2 || n == 3) return 1;
    ll remain = n % 6;
    if (remain != 1 && remain != 5) return 0;
    ll i = 5;
    while (i * i <= n)
    {
        if (!min(n % i, n % (i + 2))) return 0;
        i += 6;
    }
    return 1;
}


map<ll, ll> generate_factors(ll n)
{
    map<ll, ll> factors;
    ll f = 2;
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
