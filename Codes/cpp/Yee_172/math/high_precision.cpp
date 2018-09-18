#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace high_precision
{
    const int INITIAL_SIZE = 500;       // sizeof(BigInteger) = sizeof(int) * (UNITIAL_SIZE + 1)
    const int UNIT_LENGTH = 4;          // Maximum length of BigInteger = INITIAL_SIZE * UNIT_LENGTH
    const int UNIT_SIZE = 10000;        // 10 ** UNIT_LENGTH
    const int UNIT_MAX = UNIT_SIZE - 1;

    class BigInteger
    {
    public:
        int a[INITIAL_SIZE];
        int length;

        BigInteger() : a() { length = 0; memset(a, 0, sizeof(a)); }
        explicit BigInteger(long long);
        explicit BigInteger(int);
        explicit BigInteger(const char *);
        BigInteger(const BigInteger &T) : a(), length(T.length) { memcpy(a, T.a, sizeof a); }

        BigInteger &operator =  (const BigInteger &T) { length = T.length; memcpy(a, T.a, sizeof a); return *this; };
        BigInteger  operator +  (const BigInteger &) const;
        BigInteger  operator += (const BigInteger &T) { return *this = *this + T; }
        BigInteger  operator -  (const BigInteger &) const;
        BigInteger  operator -= (const BigInteger &T) { return *this = *this - T; }
        BigInteger  operator *  (const BigInteger &) const;
        BigInteger  operator *= (const BigInteger &T) { return *this = *this * T; }
        BigInteger  operator /  (const long long &) const;
        BigInteger  operator /= (const long long &b) { return *this = *this / b; }
        long long   operator %  (const long long &) const;
        BigInteger  operator ^  (const long long &) const;
        BigInteger  operator ^= (const long long &b) { return *this = *this ^ b; }
        bool        operator >  (const BigInteger &T) const;
        bool        operator >  (const long long &b) const { return *this > BigInteger(b); };
        bool        operator <  (const BigInteger &T) const;
        bool        operator <  (const long long &b) const { return *this < BigInteger(b); };
        bool        operator == (const BigInteger &T) const;
        bool        operator == (const long long &b) const { return *this == BigInteger(b); };

        void print(bool stdio=true);
    };

    BigInteger::BigInteger(const long long b) : a()
    {
        long long c, d = b;
        length = 0;
        memset(a, 0, sizeof a);
        while (d > UNIT_MAX)
        {
            c = d - d / UNIT_SIZE * UNIT_SIZE;
            d = d / UNIT_SIZE;
            a[length++] = (int) c;
        }
        a[length++] = (int) d;
    }

    BigInteger::BigInteger(const int b) : a()
    {
        int c, d = b;
        length = 0;
        memset(a, 0, sizeof a);
        while (d > UNIT_MAX)
        {
            c = d - d / UNIT_SIZE * UNIT_SIZE;
            d = d / UNIT_SIZE;
            a[length++] = c;
        }
        a[length++] = d;
    }

    BigInteger::BigInteger(const char *s) : a()
    {
        int t, k, index, l, i;
        memset(a, 0, sizeof a);
        l = (int) strlen(s);
        length = l / UNIT_LENGTH;
        if (l % UNIT_LENGTH) length++;
        index = 0;
        for (i = l - 1; i >= 0; i -= UNIT_LENGTH)
        {
            t = 0;
            k = i - UNIT_LENGTH + 1;
            if (k < 0) k = 0;
            for (int j = k; j <= i; ++j)
                t = t * 10 + s[j] - '0';
            a[index++] = t;
        }
    }

    BigInteger BigInteger::operator+(const BigInteger &T) const
    {
        BigInteger t(*this);
        int i, big;
        big = T.length > length ? T.length : length;
        for (i = 0; i < big; ++i)
        {
            t.a[i] += T.a[i];
            if (t.a[i] > UNIT_MAX) ++t.a[i + 1], t.a[i] -= UNIT_MAX + 1;
        }
        if (t.a[big] != 0) t.length = big + 1;
        else t.length = big;
        return t;
    }

    BigInteger BigInteger::operator-(const BigInteger &T) const
    {
        int i, j, big;
        bool flag;
        BigInteger t1, t2;
        if (*this > T) t1 = *this, t2 = T, flag = false;
        else t1 = T, t2 = *this, flag = true;
        big = t1.length;
        for (i = 0; i < big; ++i)
        {
            if (t1.a[i] < t2.a[i])
            {
                j = i + 1;
                while (t1.a[j] == 0) ++j;
                --t1.a[j--];
                while (j > i) t1.a[j--] += UNIT_MAX;
                t1.a[i] += UNIT_MAX + 1 - t2.a[i];
            }
            else t1.a[i] -= t2.a[i];
        }
        t1.length = big;
        while (t1.a[t1.length - 1] == 0 && t1.length > 1) t1.length--, big--;
        if (flag) t1.a[big - 1] = 0 - t1.a[big - 1];
        return t1;
    }

    BigInteger BigInteger::operator*(const BigInteger &T) const
    {
        BigInteger ret;
        int i = 0, j = 0, up;
        int temp, temp1;
        for (i = 0; i < length; ++i)
        {
            up = 0;
            for (j = 0; j < T.length; ++j)
            {
                temp = a[i] * T.a[j] + ret.a[i + j] + up;
                if (temp > UNIT_MAX)
                {
                    temp1 = temp - temp / (UNIT_SIZE) * (UNIT_SIZE);
                    up = temp / (UNIT_SIZE);
                    ret.a[i + j] = temp1;
                }
                else up = 0, ret.a[i + j] = temp;
            }
            if (up != 0) ret.a[i + j] = up;
        }
        ret.length = i + j;
        while (ret.a[ret.length - 1] == 0 && ret.length > 1) ret.length--;
        return ret;
    }

    BigInteger BigInteger::operator/(const long long &b) const
    {
        BigInteger ret;
        long long i, down = 0;
        for (i = length - 1; i >= 0; i--)
        {
            ret.a[i] = (int) ((down * (UNIT_SIZE) + a[i]) / b);
            down = a[i] + down * (UNIT_SIZE) - b * ret.a[i] ;
        }
        ret.length = length;
        while (ret.a[ret.length - 1] == 0 && ret.length > 1) ret.length--;
        return ret;
    }

    long long BigInteger::operator%(const long long &b) const
    {
        long long d = 0;
        for (int i = length - 1; i >= 0; --i) d = (d * UNIT_SIZE % b + a[i]) % b;
        return d;
    }

    BigInteger BigInteger::operator^(const long long &n) const
    {
        assert(n >= 0);
        BigInteger res(1);
        if (n == 0) return res;
        if (n == 1) return *this;
        BigInteger tmp = *this;
        for (long long b = n; b; b >>= 1, tmp = tmp * tmp) if (b & 1) res *= tmp;
        return res;
    }

    bool BigInteger::operator>(const BigInteger &T) const
    {
        if (length > T.length) return true;
        if (length == T.length)
        {
            int ln = length - 1;
            while (a[ln] == T.a[ln] && ln >= 0) --ln;
            return ln >= 0 && a[ln] > T.a[ln];
        }
        return false;
    }

    bool BigInteger::operator<(const BigInteger &T) const
    {
        if (length < T.length) return true;
        if (length == T.length)
        {
            int ln = length - 1;
            while (a[ln] == T.a[ln] && ln >= 0) --ln;
            return ln >= 0 && a[ln] < T.a[ln];
        }
        return false;
    }

    bool BigInteger::operator==(const BigInteger &T) const
    {
        if (length == T.length)
        {
            int ln = length - 1;
            while (a[ln] == T.a[ln] && ln >= 0) --ln;
            return ln == -1;
        }
        return false;
    }

    void BigInteger::print(bool stdio)
    {
        int i;
        if (stdio)
        {
            int j;
            int seg;
            char ch[UNIT_LENGTH + 1];
            ch[UNIT_LENGTH] = '\0';
            printf("%d", a[length - 1]);
            for (i = length - 2; i >= 0; --i)
            {
                seg = a[i];
                for (j = 0; j < UNIT_LENGTH; ++j) ch[j] = '0';
                while (seg)
                {
                    ch[--j] = (char) ('0' + seg % 10);
                    seg /= 10;
                }
                printf("%s", ch);
            }
            puts("");
        }
        else
        {
            cout << a[length - 1];
            for (i = length - 2; i >= 0; --i)
            {
                cout.width(UNIT_LENGTH);
                cout.fill('0');
                cout << a[i];
            }
            cout << endl;
        }
    }
}
using high_precision::BigInteger;
