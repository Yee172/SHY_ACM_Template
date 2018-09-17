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
    int a[INITIAL_SIZE];
    int len;

    BigInteger()
    {
        len = 1;
        memset(a, 0, sizeof(a));
    }
    BigInteger(long long);
    BigInteger(int);
    BigInteger(const char *);
    BigInteger(const BigInteger &);
    BigInteger &operator=(const BigInteger &);

    friend istream &operator>>(istream &, BigInteger &);
    friend ostream &operator<<(ostream &, BigInteger &);

    BigInteger operator+(const BigInteger &) const;
    BigInteger operator-(const BigInteger &) const;
    BigInteger operator*(const BigInteger &) const;
    BigInteger operator/(const long long &) const;

    BigInteger operator^(const long long &) const;
    long long  operator%(const long long &) const;
    bool       operator>(const BigInteger &T) const;
    bool       operator>(const long long &t) const;

    void print(bool stdio=true);
};

BigInteger::BigInteger(const long long b)
{
    long long c, d = b;
    len = 0;
    memset(a, 0, sizeof a);
    while (d > UNIT_SIZE)
    {
        c = d - (d / (UNIT_SIZE + 1)) * (UNIT_SIZE + 1);
        d = d / (UNIT_SIZE + 1);
        a[len++] = (int) c;
    }
    a[len++] = (int) d;
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
    int t, k, index, l, i;
    memset(a, 0, sizeof a);
    l = (int) strlen(s);
    len = l / UNIT_LENGTH;
    if (l % UNIT_LENGTH) len++;
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

BigInteger::BigInteger(const BigInteger &T) : len(T.len)
{
    int i;
    memset(a, 0, sizeof a);
    for (i = 0; i < len; ++i)
        a[i] = T.a[i];
}

BigInteger &BigInteger::operator=(const BigInteger &n)
{
    int i;
    len = n.len;
    memset(a, 0, sizeof a);
    for (i = 0; i < len; ++i)
        a[i] = n.a[i];
    return *this;
}

istream &operator>>(istream &in, BigInteger &b)
{
    char ch[BUFFER_SIZE * 4];
    int i, l;
    in >> ch;
    l = (int) strlen(ch);
    int count = 0, sum = 0;
    for (i = l - 1; i >= 0;)
    {
        sum = 0;
        int t = 1;
        for (int j = 0; j < 4 && i >= 0; ++j, --i, t *= 10)
            sum += (ch[i] - '0') * t;
        b.a[count++] = sum;
    }
    b.len = count++;
    return in;
}

ostream &operator<<(ostream &out, BigInteger &b)
{
    int i;
    cout << b.a[b.len - 1];
    for (i = b.len - 2; i >= 0; --i)
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
    int i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; ++i)
    {
        t.a[i] += T.a[i];
        if (t.a[i] > UNIT_SIZE) ++t.a[i + 1], t.a[i] -= UNIT_SIZE + 1;
    }
    if (t.a[big] != 0) t.len = big + 1;
    else t.len = big;
    return t;
}

BigInteger BigInteger::operator-(const BigInteger &T) const
{
    int i, j, big;
    bool flag;
    BigInteger t1, t2;
    if (*this > T) t1 = *this, t2 = T, flag = false;
    else t1 = T, t2 = *this, flag = true;
    big = t1.len;
    for (i = 0; i < big; ++i)
    {
        if (t1.a[i] < t2.a[i])
        {
            j = i + 1;
            while (t1.a[j] == 0) ++j;
            --t1.a[j--];
            while (j > i) t1.a[j--] += UNIT_SIZE;
            t1.a[i] += UNIT_SIZE + 1 - t2.a[i];
        }
        else t1.a[i] -= t2.a[i];
    }
    t1.len = big;
    while (t1.a[t1.len - 1] == 0 && t1.len > 1) t1.len--, big--;
    if (flag) t1.a[big - 1] = 0 - t1.a[big - 1];
    return t1;
}

BigInteger BigInteger::operator*(const BigInteger &T) const
{
    BigInteger ret;
    int i = 0, j = 0, up;
    int temp, temp1;
    for (i = 0; i < len; ++i)
    {
        up = 0;
        for (j = 0; j < T.len; ++j)
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

BigInteger BigInteger::operator/(const long long &b) const
{
    BigInteger ret;
    long long i, down = 0;
    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (int) ((down * (UNIT_SIZE + 1) + a[i]) / b);
        down = a[i] + down * (UNIT_SIZE + 1) - b * ret.a[i] ;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
    return ret;
}

long long BigInteger::operator%(const long long &b) const
{
    long long d = 0;
    for (int i = len - 1; i >= 0; --i) d = ((d * (UNIT_SIZE + 1)) % b + a[i]) % b;
    return d;
}

BigInteger BigInteger::operator^(const long long &n) const
{
    BigInteger t, ret(1);
    long long i;
    if (n < 0) exit(-1);
    if (n == 0) return 1;
    if (n == 1) return *this;
    long long m = n;
    while (m > 1)
    {
        t = *this;
        for (i = 1; i << 1 <= m; i <<= 1) t = t * t;
        m -= i;
        ret = ret * t;
        if (m == 1) ret = ret * (*this);
    }
    return ret;
}

bool BigInteger::operator>(const BigInteger &T) const
{
    int ln;
    if (len > T.len) return true;
    else if (len == T.len)
    {
        ln = len - 1;
        while (a[ln] == T.a[ln] && ln >= 0) ln--;
        return ln >= 0 && a[ln] > T.a[ln];
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
    int i;
    if (stdio)
    {
        int j;
        int seg;
        char ch[UNIT_LENGTH + 1];
        ch[UNIT_LENGTH] = '\0';
        printf("%d", a[len - 1]);
        for (i = len - 2; i >= 0; --i)
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
        cout << a[len - 1];
        for (i = len - 2; i >= 0; --i)
        {
            cout.width(UNIT_LENGTH);
            cout.fill('0');
            cout << a[i];
        }
        cout << endl;
    }
}
