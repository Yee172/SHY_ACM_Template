#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// modified from
// https://github.com/wcysai/CodeTemplates/blob/master/Math/BigNum.cpp
#define INITIAL_SIZE 500
#define BUFFER_SIZE 10
#define UNIT_LENGTH 4
#define UNIT_SIZE 9999

class BigInteger
{
public:
    ll a[INITIAL_SIZE];
    ll len;

    BigInteger()
    {
        len = 1;
        memset(a, 0, sizeof(a));
    }
    BigInteger(const ll);
    BigInteger(const int);
    BigInteger(const char *);
    BigInteger(const BigInteger &);
    BigInteger &operator=(const BigInteger &);

    friend istream &operator>>(istream &, BigInteger &);
    friend ostream &operator<<(ostream &, BigInteger &);

    BigInteger operator+(const BigInteger &) const;
    BigInteger operator-(const BigInteger &) const;
    BigInteger operator*(const BigInteger &) const;
    BigInteger operator/(const ll &) const;

    BigInteger operator^(const ll &) const;
    ll         operator%(const ll &) const;
    bool       operator>(const BigInteger &T) const;
    bool       operator>(const ll &t) const;

    void print(bool stdio=true);
};

BigInteger::BigInteger(const ll b)
{
    ll c, d = b;
    len = 0;
    memset(a, 0, sizeof a);
    while (d > UNIT_SIZE)
    {
        c = d - (d / (UNIT_SIZE + 1)) * (UNIT_SIZE + 1);
        d = d / (UNIT_SIZE + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigInteger::BigInteger(const int b)
{
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof a);
    while (d > UNIT_SIZE)
    {
        c = d - (d / (UNIT_SIZE + 1)) * (UNIT_SIZE + 1);
        d = d / (UNIT_SIZE + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigInteger::BigInteger(const char *s)
{
    ll t, k, index, l, i;
    memset(a, 0, sizeof a);
    l = (ll) strlen(s);
    len = l / UNIT_LENGTH;
    if (l % UNIT_LENGTH) len++;
    index = 0;
    for (i = l - 1; i >= 0; i -= UNIT_LENGTH)
    {
        t = 0;
        k = i - UNIT_LENGTH + 1;
        if (k < 0) k = 0;
        for (ll j = k; j <= i; j++)
            t = t * 10 + s[j] - '0';
        a[index++] = t;
    }
}

BigInteger::BigInteger(const BigInteger &T) : len(T.len)
{
    ll i;
    memset(a, 0, sizeof a);
    for (i = 0; i < len; i++)
        a[i] = T.a[i];
}

BigInteger &BigInteger::operator=(const BigInteger &n)
{
    ll i;
    len = n.len;
    memset(a, 0, sizeof a);
    for (i = 0; i < len; i++)
        a[i] = n.a[i];
    return *this;
}

istream &operator>>(istream &in, BigInteger &b)
{
    char ch[BUFFER_SIZE * 4];
    ll i, l;
    in >> ch;
    l = (ll) strlen(ch);
    ll count = 0, sum = 0;
    for (i = l - 1; i >= 0;)
    {
        sum = 0;
        ll t = 1;
        for (ll j = 0; j < 4 && i >= 0; j++, i--, t *= 10)
            sum += (ch[i] - '0') * t;
        b.a[count] = sum;
        count++;
    }
    b.len = count++;
    return in;
}

ostream &operator<<(ostream &out, BigInteger &b)
{
    ll i;
    cout << b.a[b.len - 1];
    for (i = b.len - 2; i >= 0; i--)
    {
        cout.width(UNIT_LENGTH);
        cout.fill('0');
        cout << b.a[i];
    }
    return out;
}

BigInteger BigInteger::operator+(const BigInteger &T) const
{
    BigInteger t(*this);
    ll i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        t.a[i] += T.a[i];
        if (t.a[i] > UNIT_SIZE)
            t.a[i + 1]++, t.a[i] -= UNIT_SIZE + 1;
    }
    if (t.a[big] != 0)
        t.len = big + 1;
    else
        t.len = big;
    return t;
}

BigInteger BigInteger::operator-(const BigInteger &T) const
{
    ll i, j, big;
    bool flag;
    BigInteger t1, t2;
    if (*this > T)
        t1 = *this, t2 = T, flag = 0;
    else
        t1 = T, t2 = *this, flag = 1;
    big = t1.len;
    for (i = 0; i < big; i++)
    {
        if (t1.a[i] < t2.a[i])
        {
            j = i + 1;
            while (t1.a[j] == 0) j++;
            t1.a[j--]--;
            while (j > i) t1.a[j--] += UNIT_SIZE;
            t1.a[i] += UNIT_SIZE + 1 - t2.a[i];
        }
        else t1.a[i] -= t2.a[i];
    }
    t1.len = big;
    while (t1.a[t1.len - 1] == 0 && t1.len > 1)
        t1.len--, big--;
    if (flag)
        t1.a[big - 1] = 0 - t1.a[big - 1];
    return t1;
}

BigInteger BigInteger::operator*(const BigInteger &T) const
{
    BigInteger ret;
    ll i = 0, j = 0, up;
    ll temp, temp1;
    for (i = 0; i < len; i++)
    {
        up = 0;
        for (j = 0; j < T.len; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if (temp > UNIT_SIZE)
            {
                temp1 = temp - temp / (UNIT_SIZE + 1) * (UNIT_SIZE + 1);
                up = temp / (UNIT_SIZE + 1);
                ret.a[i + j] = temp1;
            }
            else up = 0, ret.a[i + j] = temp;
        }
        if (up != 0) ret.a[i + j] = up;
    }
    ret.len = i + j;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
    return ret;
}

BigInteger BigInteger::operator/(const ll &b) const
{
    BigInteger ret;
    ll i, down = 0;
    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (a[i] + down * (UNIT_SIZE + 1)) / b;
        down = a[i] + down * (UNIT_SIZE + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
    return ret;
}

ll BigInteger::operator%(const ll &b) const
{
    ll i, d = 0;
    for (i = len - 1; i >= 0; i--)
        d = ((d * (UNIT_SIZE + 1)) % b + a[i]) % b;
    return d;
}

BigInteger BigInteger::operator^(const ll &n) const
{
    BigInteger t, ret(1);
    ll i;
    if (n < 0) exit(-1);
    if (n == 0) return 1;
    if (n == 1) return *this;
    ll m = n;
    while (m > 1)
    {
        t = *this;
        for (i = 1; i << 1 <= m; i <<= 1)
            t = t * t;
        m -= i;
        ret = ret * t;
        if (m == 1) ret = ret * (*this);
    }
    return ret;
}

bool BigInteger::operator>(const BigInteger &T) const
{
    ll ln;
    if (len > T.len) return true;
    else if (len == T.len)
    {
        ln = len - 1;
        while (a[ln] == T.a[ln] && ln >= 0) ln--;
        if (ln >= 0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}

bool BigInteger::operator>(const ll &t) const
{
    BigInteger b(t);
    return *this > b;
}

void BigInteger::print(bool stdio)
{
    if (stdio)
    {
        ll j;
        char ch[UNIT_LENGTH + 1];
        ch[UNIT_LENGTH] = '\0';
        printf("%lld", a[len - 1]);
        for (ll i = len - 2; i >= 0; i--)
        {
            for (j = 0; j < UNIT_LENGTH; j++) ch[j] = '0';
            while (a[i])
            {
                ch[--j] = (char) ('0' + a[i] % 10);
                a[i] /= 10;
            }
            printf("%s", ch);
        }
        puts("");
    }
    else
    {
        cout << a[len - 1];
        for (ll i = len - 2; i >= 0; i--)
        {
            cout.width(UNIT_LENGTH);
            cout.fill('0');
            cout << a[i];
        }
        cout << endl;
    }
}
