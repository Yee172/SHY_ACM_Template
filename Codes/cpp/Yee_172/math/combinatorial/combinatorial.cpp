#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define _rep(i, n) for (ll i = 1; (i) <= (n); (i)++)
#define MOD 0x3b9aca07
#define MAXN 200050
#define TYPE ll


ll factorial[MAXN];
void init_factorial()
{
    factorial[0] = 1;
#ifdef MOD
    for (ll i = 1; i < MAXN; i++)
        factorial[i] = i * factorial[i - 1] % MOD;
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
    {
#ifdef MOD
        factorial[i] = (TYPE) i * factorial[i - 1] % MOD;
#else
        factorial[i] = (TYPE) i * factorial[i - 1];
#endif
    }
}


#ifdef MOD
ll mod_inverse[MAXN];
ll factorial_inverse[MAXN];
void init_factorial_inverse()
{
    mod_inverse[0] = 0, factorial_inverse[0] = mod_inverse[1] = 1;
    for (ll i = 2; i < MAXN; i++)
        mod_inverse[i] = (MOD - MOD / i) * mod_inverse[MOD % i] % MOD;
    for (ll i = 1; i < MAXN; i++)
        factorial_inverse[i] = factorial_inverse[i - 1] * mod_inverse[i] % MOD;
}
#endif


ll derangement[MAXN];
void init_derangement()
{
    derangement[1] = 0, derangement[0] = derangement[2] = 1;
#ifdef MOD
    for (ll i = 3; i < MAXN; i++)
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) % MOD * (i - 1) % MOD;
#else
    for (ll i = 3; i < MAXN && i <= 20; i++)
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) * (i - 1);
    //MAXIMUM 20 for long long
#endif
}


TYPE derangement[MAXN];
void init_derangement()
{
    derangement[1] = 0, derangement[0] = derangement[2] = 1;
    for (ll i = 3; i < MAXN; i++)
    {
#ifdef MOD
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) % MOD * ((TYPE) (i - 1)) % MOD;
#else
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) * ((TYPE) (i - 1));
#endif
    }
}


ll catalan[MAXN];
#ifdef MOD
ll mod_inverse[MAXN];
#endif
void init_catalan()
{
    catalan[1] = 1;
#ifdef MOD
    mod_inverse[0] = 0, mod_inverse[1] = 1;
    for (ll i = 2; i < MAXN; i++)
        mod_inverse[i] = (MOD - MOD / i) * mod_inverse[MOD % i] % MOD;
    for (ll i = 2; i < MAXN; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) % MOD * mod_inverse[i + 1] % MOD;
#else
    for (ll i = 2; i < MAXN && i <= 33; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
    if (MAXN > 34) catalan[34] = 812944042149730764;
    if (MAXN > 35) catalan[35] = 3116285494907301262;
    // MAXIMUM 35 for long long
#endif
}


TYPE catalan[MAXN];
void init_catalan()
{
    catalan[1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
#ifdef MOD
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1) % MOD;
#else
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
#endif
    }
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
#ifdef MOD
            catalan[i][j] = (catalan[i - 1][j] + catalan[i][j - 1]) % MOD;
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
#ifdef MOD
            binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % MOD;
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
#ifdef MOD
            stirling_first[i][j] = ((i - 1) * stirling_first[i - 1][j] % MOD + stirling_first[i - 1][j - 1]) % MOD;
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
#ifdef MOD
            stirling_second[i][j] = (j * stirling_second[i - 1][j] % MOD + stirling_second[i - 1][j - 1]) % MOD;
#else
            stirling_second[i][j] = j * stirling_second[i - 1][j] + stirling_second[i - 1][j - 1];
#endif
        }
        stirling_second[i][i] = (TYPE) 1;
    }
}


// stiring numbers of the second kind
ll powmod(ll a,ll b) {ll r = 1; a %= MOD; for(; b; b >>= 1) {if (b & 1) r = r * a % MOD; a = a * a % MOD;} return r;}
ll modinv[MAXN];
ll fa_inv[MAXN];
ll f[] = {1, -1};

ll init_stirling()
{
    modinv[0] = 0, modinv[1] = 1;
    for (ll i = 2; i < MAXN; i++) modinv[i] = (MOD - MOD / i) * modinv[MOD % i] % MOD;
    fa_inv[0] = 1;
    for (ll i = 1; i < MAXN; i++) fa_inv[i] = fa_inv[i - 1] * modinv[i] % MOD;
}

ll stirling(ll n, ll m)
{
    ll r = 0;
    if (n >= m)
        for (ll i = 0; i < m + 1; i++)
            r = (r + f[i & 1] * fa_inv[m - i] * fa_inv[i] % MOD * powmod(m - i, n)) % MOD;
    return r;
}


// bell triangle
vector<TYPE> bell[MAXN]; // bell(i) = bell[i][i]
void init_bell()
{
    for (ll i = 0; i < MAXN; i++)
        bell[i] = vector<TYPE>((unsigned) i + 1, 0);
    bell[1][1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        bell[i][1] = bell[i - 1][i - 1];
        for (ll j = 2; j <= i; j++)
        {
#ifdef MOD
            bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % MOD;
#else
            bell[i][j] = bell[i][j - 1] + bell[i - 1][j - 1];
#endif
        }
    }
}


TYPE bell[MAXN];
TYPE temp[MAXN];
void init_bell()
{
    bell[0] = bell[1] = temp[0] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        temp[i - 1] = bell[i - 1];
        for (ll j = i - 2; j >= 0; j--)
        {
#ifdef MOD
            temp[j] = (temp[j] + temp[j + 1]) % MOD;
#else
            temp[j] = temp[j] + temp[j + 1];
#endif
        }
        bell[i] = temp[0];
    }
}
