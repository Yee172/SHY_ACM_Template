#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 0x3b9aca07
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)

template <typename T>
class Matrix
{
public:
    ll n;
    bool cyclic = false;
    vector<vector<T> > a;
    Matrix(ll n) : n(n)
    {
        init();
    }
    vector<T> &operator[](ll i)
    {
        return a[i];
    }

    Matrix<T> operator*(Matrix &b) const
    {
        Matrix<T> res(n);
        if (cyclic)
        {
            res.cyclic = true;
            rep(k, n) if (a[0][k]) rep(j, n) if (b[k][j])
                        {
#ifdef mod
                            res[0][j] += a[0][k] * b[k][j] % mod, res[0][j] %= mod;
#else
                            res[0][j] += a[0][k] * b[k][j];
#endif
                        }
            rep(i, n - 1)
            {
                res[i + 1][0] = res[i][n - 1];
                rep(j, n - 1) res[i + 1][j + 1] = res[i][j];
            }
        }
        else rep(i, n) rep(j, n) rep(k, n)
                    {
#ifdef mod
                        res[i][j] += a[i][k] * b[k][j] % mod, res[i][j] %= mod;
#else
                        res[i][j] += a[i][k] * b[k][j];
#endif
                    }
        return res;
    }

    Matrix<T> operator^(ll t) const
    {
        Matrix<T> res(n);
        res.cyclic = cyclic;
        rep(i, n) res[i][i] = 1;
        Matrix<T> tmp = *this;
        while (t)
        {
            if (t & 1) res = res * tmp;
            t >>= 1;
            tmp = tmp * tmp;
        }
        return res;
    };

    void print()
    {
        rep(i, n) rep(j, n) cout << a[i][j] << j == n - 1 ? '\n' : ' ';
    };

private:
    void init()
    {
        a = vector<vector<T> >((unsigned long long) n, vector<T>((unsigned long long) n, 0));
        rep(i, n) rep(j, n) a[i][j] = 0;
    };
};
