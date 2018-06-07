#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 110;
const ll mod = 0x3b9aca07;
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)

struct Matrix
{
    bool cyclic = false;
    ll n;
    ll a[N][N];
    Matrix() {}
    Matrix(ll n) : n(n)
    {
        init();
    }
    void init()
    {
        rep(i, n) rep(j, n) a[i][j] = 0;
    }
    ll *operator[](ll i)
    {
        return a[i];
    }
    Matrix operator*(Matrix &b) const
    {
        Matrix res(n);
        if (cyclic)
        {
            res.cyclic = true;
            rep(k, n) if (a[0][k]) rep(j, n) if (b[k][j]) res[0][j] += a[0][k] * b[k][j] % mod, res[0][j] %= mod;
            rep(i, n - 1)
            {
                res[i + 1][0] = res[i][n - 1];
                rep(j, n - 1) res[i + 1][j + 1] = res[i][j];
            }
        }
        else rep(i, n) rep(j, n) rep(k, n) res[i][j] += a[i][k] * b[k][j] % mod, res[i][j] %= mod;
        return res;
    }
    Matrix operator^(ll t) const
    {
        Matrix res(n);
        res.cyclic = cyclic;
        rep(i, n) res[i][i] = 1;
        Matrix tmp = *this;
        while (t)
        {
            if (t & 1)
                res = res * tmp;
            t >>= 1;
            tmp = tmp * tmp;
        }
        return res;
    }
    void print()
    {
        rep(i, n) rep(j, n) printf("%lld%c", a[i][j], j == n - 1 ? '\n' : ' ');
    }
};
