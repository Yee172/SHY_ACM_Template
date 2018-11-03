#include <bits/stdc++.h>
using namespace std;

namespace Gaussian_elimination
{
    const double eps = 1e-8;
    vector<vector<double> > a;
    int n = 0;
    int augment_dimension = 1;

    inline void initialize() { a.assign((unsigned long)n, vector<double>(n + augment_dimension, 0)); }

    inline int sign(const double x) { return x < -eps ? -1 : x > eps; }

    bool Gaussian_elimination()
    {
        assert(n > 0);
        int r;
        double f;
        for (int i = 0; i < n; ++i)
        {
            r = i;
            for (int j = i + 1; j < n; ++j) if (sign(fabs(a[j][i]) - fabs(a[r][i])) == 1) r = j;
            if (sign(a[r][i]) == 0) return false;
            if (r != i) for (int j = 0; j < n + augment_dimension; ++j) swap(a[r][j], a[i][j]);
            for (int k = i + 1; k < n; ++k)
            {
                f = a[k][i] / a[i][i];
                for (int j = i; j < n + augment_dimension; ++j) a[k][j] -= f * a[i][j];
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
                for (int k = n; k < n + augment_dimension; ++k)
                    a[i][k] -= a[j][k] * a[i][j];
            for (int k = n; k < n + augment_dimension; ++k)
                a[i][k] /= a[i][i];
        }
        return true;
    }
}

namespace Gaussian_elimination
{
    const int MOD = 0x3b9aca07;

    inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) { if (b & 1) r = __mul__(r, a); } return r; }

    vector<vector<int> > a;
    vector<int> diagonal;
    int n = 0;
    int augment_dimension = 1;

    inline void initialize()
    {
        a.assign((unsigned long)n, vector<int>(n + augment_dimension, 0));
        diagonal.assign((unsigned long)n, 0);
    }

    bool Gaussian_elimination()
    {
        assert(n > 0);
        int r;
        int f;
        for (int i = 0; i < n; ++i)
        {
            r = i;
            for (int j = i + 1; j < n; ++j) if (a[j][i] > a[r][i]) r = j;
            if (a[r][i] == 0) return false;
            if (r != i) for (int j = 0; j < n + augment_dimension; ++j) swap(a[r][j], a[i][j]);
            diagonal[i] = __pow__(a[i][i], MOD - 2);
            for (int k = i + 1; k < n; ++k)
            {
                f = __mul__(a[k][i], diagonal[i]);
                for (int j = i; j < n + augment_dimension; ++j) a[k][j] = __sub__(a[k][j], __mul__(f, a[i][j]));
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
                for (int k = n; k < n + augment_dimension; ++k)
                    a[i][k] = __sub__(a[i][k], __mul__(a[j][k], a[i][j]));
            for (int k = n; k < n + augment_dimension; ++k)
                a[i][k] = __mul__(a[i][k], diagonal[i]);
        }
        return true;
    }
}
