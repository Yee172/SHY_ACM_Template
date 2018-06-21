#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define _rep(i, n) for (ll i = 1; (i) <= (n); (i)++)
#define mod 0x3b9aca07
#define MAXN 200050
#define TYPE ll


ll factorial[MAXN];
void init_factorial()
{
    factorial[0] = 1;
#ifdef mod
    for (ll i = 1; i < MAXN; i++)
        factorial[i] = i * factorial[i - 1] % mod;
#else
    for (ll i = 1; i < MAXN && i <= 20; i++)
        factorial[i] = i * factorial[i - 1];
    //MAXIMUM 20 for long long
#endif
}


TYPE factorial[MAXN];
void init_factorial()
{
    factorial[0] = (TYPE) 1;
    for (ll i = 1; i < MAXN; i++)
        factorial[i] = (TYPE) i * factorial[i - 1];
}


ll derangement[MAXN];
void init_derangement()
{
    derangement[0] = 1, derangement[1] = 0, derangement[2] = 1;
#ifdef mod
    for (ll i = 3; i < MAXN; i++)
        derangement[i] = (i - 1) * ((derangement[i - 1] + derangement[i - 2]) % mod) % mod;
#else
    for (ll i = 3; i < MAXN && i <= 20; i++)
        derangement[i] = (i - 1) * (derangement[i - 1] + derangement[i - 2]);
    //MAXIMUM 20 for long long
#endif
}


ll catalan[MAXN];
#ifdef mod
ll mod_inverse[MAXN];
ll factorial_inverse[MAXN];
#endif
void init_catalan()
{
    catalan[1] = 1;
#ifdef mod
    mod_inverse[0] = 0, mod_inverse[1] = 1;
    for (ll i = 2; i < MAXN; i++)
        mod_inverse[i] = (mod - mod / i) * mod_inverse[mod % i] % mod;
    factorial_inverse[0] = 1;
    for (ll i = 1; i < MAXN; i++)
        factorial_inverse[i] = factorial_inverse[i - 1] * mod_inverse[i] % mod;
    for (ll i = 2; i < MAXN; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) % mod * factorial_inverse[i + 1] % mod;
#else
    for (ll i = 2; i < MAXN && i <= 33; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
    if (MAXN > 34) catalan[34] = 812944042149730764;
    if (MAXN > 35) catalan[35] = 3116285494907301262;
    // MAXIMUM 35 for long long
#endif
}


vector<TYPE> catalan[MAXN]; // catalan[in_stack][out_stack]
void init_catalan()
{
    for (ll i = 0; i < MAXN; i++)
        catalan[i] = vector<TYPE>((unsigned) i + 1, 1);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef mod
            catalan[i][j] = (catalan[i - 1][j] + catalan[i][j - 1]) % mod;
#else
            catalan[i][j] = catalan[i - 1][j] + catalan[i][j - 1];
#endif
        }
        catalan[i][i] = catalan[i][i - 1];
    }
}


vector<TYPE> binomial[MAXN];
void init_binomial()
{
    for (ll i = 0; i < MAXN; i++)
        binomial[i] = vector<TYPE>((unsigned) i + 1, 1);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef mod
            binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % mod;
#else
            binomial[i][j] = binomial[i - 1][j] + binomial[i - 1][j - 1];
#endif
        }
    }
}


vector<TYPE> stirling_first[MAXN];
void init_stirling_first()
{
    for (ll i = 0; i < MAXN; i++)
        stirling_first[i] = vector<TYPE>((unsigned) i + 1, 0);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef mod
            stirling_first[i][j] = ((i - 1) * stirling_first[i - 1][j] % mod + stirling_first[i - 1][j - 1]) % mod;
#else
            stirling_first[i][j] = (i - 1) * stirling_first[i - 1][j] + stirling_first[i - 1][j - 1];
#endif
        }
        stirling_first[i][i] = (TYPE) 1;
    }
}


vector<TYPE> stirling_second[MAXN];
void init_stirling_second()
{
    for (ll i = 0; i < MAXN; i++)
        stirling_second[i] = vector<TYPE>((unsigned) i + 1, 0);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef mod
            stirling_second[i][j] = (j * stirling_second[i - 1][j] % mod + stirling_second[i - 1][j - 1]) % mod;
#else
            stirling_first[i][j] = j * stirling_first[i - 1][j] + stirling_first[i - 1][j - 1];
#endif
        }
        stirling_second[i][i] = (TYPE) 1;
    }
}


// stiring numbers of the second kind
ll powmod(ll a,ll b) {ll r = 1; a %= mod; for(; b; b >>= 1) {if (b & 1) r = r * a % mod; a = a * a % mod;} return r;}
ll modinv[MAXN];
ll fa_inv[MAXN];
ll f[] = {1, -1};

ll init_stirling()
{
    modinv[0] = 0, modinv[1] = 1;
    for (ll i = 2; i < MAXN; i++) modinv[i] = (mod - mod / i) * modinv[mod % i] % mod;
    fa_inv[0] = 1;
    for (ll i = 1; i < MAXN; i++) fa_inv[i] = fa_inv[i - 1] * modinv[i] % mod;
}

ll stirling(ll n, ll m)
{
    ll r = 0;
    if (n >= m)
        for (ll i = 0; i < m + 1; i++)
            r = (r + f[i & 1] * fa_inv[m - i] * fa_inv[i] % mod * powmod(m - i, n)) % mod;
    return r;
}
