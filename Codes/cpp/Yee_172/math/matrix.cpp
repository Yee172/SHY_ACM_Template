#include <bits/stdc++.h>
using namespace std;

namespace matrix
{
    const int MOD = 0x3b9aca07;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }

    typedef unsigned long long ull;
    template <typename T>
    class Matrix
    {
    public:
        ull n;
        bool cyclic = false;
        vector<vector<T> > a;
        Matrix() {}
        Matrix(ull n) : n(n) { init(); }
        vector<T> &operator [] (ull i) { return a[i]; }
        Matrix<T> operator * (Matrix &b) const
        {
            Matrix<T> res(n);
            if (cyclic)
            {
                res.cyclic = true;
                for (int k = 0; k < n; k++)
                    if (a[0][k])
                        for (int j = 0; j < n; j++)
                            if (b[k][j])
                                res[0][j] = __add__(res[0][j], __mul__(a[0][k], b[k][j]));
                for (int i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (int j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
                }
            }
            else
                for (int k = 0; k < n; k++)
                    for (int i = 0; i < n; i++)
                        if (a[i][k])
                            for (int j = 0; j < n; j++)
                                res[i][j] = __add__(res[i][j], __mul__(a[i][k], b[k][j]));
            return res;
        }

        Matrix<T> operator^(ull t) const
        {
            assert(n >= 0);
            Matrix<T> res(n);
            res.cyclic = cyclic;
            for (int i = 0; i < n; i++) res[i][i] = 1;
            Matrix<T> tmp = *this;
            for (; t; t >>= 1)
            {
                if (t & 1) res = res * tmp;
                tmp = tmp * tmp;
            }
            return res;
        }

        void print()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cout << a[i][j] << " \n"[j == n - 1];
        }

    private:
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;

namespace matrix
{
    typedef unsigned long long ull;
    template <typename T>
    class Matrix
    {
    public:
        ull n;
        bool cyclic = false;
        vector<vector<T> > a;
        Matrix() {}
        Matrix(ull n) : n(n) { init(); }
        vector<T> &operator [] (ull i) { return a[i]; }
        Matrix<T> operator * (Matrix &b) const
        {
            Matrix<T> res(n);
            if (cyclic)
            {
                res.cyclic = true;
                for (int k = 0; k < n; k++)
                    if (a[0][k])
                        for (int j = 0; j < n; j++)
                            if (b[k][j])
                                res[0][j] += a[0][k] * b[k][j];
                for (int i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (int j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
                }
            }
            else
                for (int k = 0; k < n; k++)
                    for (int i = 0; i < n; i++)
                        if (a[i][k])
                            for (int j = 0; j < n; j++)
                                res[i][j] += a[i][k] * b[k][j];
            return res;
        }

        Matrix<T> operator^(ull t) const
        {
            assert(n >= 0);
            Matrix<T> res(n);
            res.cyclic = cyclic;
            for (int i = 0; i < n; i++) res[i][i] = 1;
            Matrix<T> tmp = *this;
            for (; t; t >>= 1)
            {
                if (t & 1) res = res * tmp;
                tmp = tmp * tmp;
            }
            return res;
        }

        void print()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cout << a[i][j] << " \n"[j == n - 1];
        }

    private:
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;
