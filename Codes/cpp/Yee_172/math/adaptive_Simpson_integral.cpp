#include <bits/stdc++.h>
using namespace std;

namespace adaptive_Simpson_integral
{
    typedef double db;
    typedef pair<db, db> pdd;
    typedef pair<pdd, pdd> pdddd;
    const db eps = 1e-6;
    db (*f)(db);

    inline db simpson_formula(const db left, const db right)
    {
        db middle = (left + right) / 2.0;
        return (f(left) + 4.0 * f(middle) + f(right)) * (right - left) / 6.0;
    }

    inline db integral(const db left, const db right, db (*function)(double))
    {
        f = function;
        db res = 0, l, r, m, precision, S_total, S_left, S_right;
        queue<pdddd> q;
        q.push(make_pair(make_pair(left, right), make_pair(simpson_formula(left, right), eps)));
        while (!q.empty())
        {
            l = q.front().first.first;
            r = q.front().first.second;
            S_total = q.front().second.first;
            precision = q.front().second.second;
            q.pop();
            m = (l + r) / 2.0;
            S_left = simpson_formula(l, m);
            S_right = simpson_formula(m, r);
            if (fabs(S_left + S_right - S_total) <= 15.0 * precision)
                res += S_left + S_right + (S_left + S_right - S_total) / 15.0;
            else
            {
                q.push(make_pair(make_pair(l, m), make_pair(S_left, precision / 2.0)));
                q.push(make_pair(make_pair(m, r), make_pair(S_right, precision / 2.0)));
            }
        }
        return res;
    }
}
using adaptive_Simpson_integral::integral;

double a, b, c, d;
inline double f(double x) { return (c * x + d) / (a * x + b); }
