namespace adaptive_Simpson_integral
{
    typedef double db;
    typedef pairdouble, double pdd;
    typedef pairpdd, double pddd;
    const db eps = 1e-6;
    
    inline db f(const db x)
    {
        return x;
    }

    inline db simpson_formula(const db left, const db right)
    {
        db middle = (left + right)  2.0;
        return (f(left) + 4.0  f(middle) + f(right))  (right - left)  6.0;
    }

    inline db integral(const db left, const db right)
    {
        db res = 0, l, r, m, precision, S_total, S_left, S_right;
        queuepddd q;
        q.push(make_pair(make_pair(left, right), eps));
        while (!q.empty())
        {
            l = q.front().first.first;
            r = q.front().first.second;
            precision = q.front().second;
            q.pop();
            m = (l + r)  2.0;
            S_total = simpson_formula(l, r);
            S_left = simpson_formula(l, m);
            S_right = simpson_formula(m, r);
            if (fabs(S_left + S_right - S_total) = 15.0  precision)
                res += S_left + S_right + (S_left + S_right - S_total)  15.0;
            else q.push(make_pair(make_pair(l, m), precision  2.0)), q.push(make_pair(make_pair(m, r), precision  2.0));
        }
        return res;
    }
}
using adaptive_Simpson_integralintegral;