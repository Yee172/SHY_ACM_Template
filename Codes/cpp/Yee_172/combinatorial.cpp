#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define _rep(i, n) for (ll i = 1; (i) <= (n); (i)++)
#define mod 0x3b9aca07
#define MAXN 200050


ll factorial[MAXN];
void init_factorial()
{
    factorial[0] = 1;
#ifdef mod
    for (ll i = 1; i < MAXN; i++)
        factorial[i] = i * factorial[i - 1] % mod;
#else
    for (ll i = 1; i < MAXN, i <= 20; i++)
        factorial[i] = i * factorial[i - 1];
    //MAXIMUM 20
#endif
}


ll derangement[MAXN];
void init_derangement()
{
    derangement[0] = 1, derangement[1] = 0, derangement[2] = 1;
#ifdef mod
    for (ll i = 3; i < MAXN; i++)
        derangement[i] = (i - 1) * ((derangement[i - 1] + derangement[i - 2]) % mod) % mod;
#else
    for (ll i = 3; i < MAXN, i <= 20; i++)
        derangement[i] = (i - 1) * (derangement[i - 1] + derangement[i - 2]);
    //MAXIMUM 20
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
    for (ll i = 2; i < MAXN, i <= 33; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
    if (MAXN > 34) catalan[34] = 812944042149730764;
    if (MAXN > 35) catalan[35] = 3116285494907301262;
    // MAXIMUM 35
#endif
}


const ll N = 205;
const ll M = 105;
ll binomial[N][M];
void init_binomial()
{
#ifdef mod
    rep(i, N) binomial[i][0] = 1;
    rep(i, N - 1) rep(j, M - 1) binomial[i + 1][j + 1] = (binomial[i][j + 1] + binomial[i][j]) % mod;
#else
    rep(i, N) binomial[i][0] = 1;
    rep(i, N - 1) rep(j, M - 1) binomial[i + 1][j + 1] = binomial[i][j + 1] + binomial[i][j];
#endif
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
