#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline bool read(T &x)
{
    char c = getchar();
    bool f = false;
    for (x = 0; !isdigit(c); c = getchar())
    {
        if (c == EOF) return false;
        if (c == '-') f = true;
    }
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    if (f) x = -x;
    return true;
}

template <typename A, typename B>
inline bool read(A &a, B&b)
{
    return read(a) && read(b);
}

template <typename A, typename B, typename C>
inline bool read(A &a, B &b, C &c)
{
    return read(a) && read(b) && read(c);
}

template <typename A, typename B, typename C, typename D>
inline bool read(A &a, B &b, C &c, D &d)
{
    return read(a) && read(b) && read(c) && read(d);
}

template <typename A, typename B, typename C, typename D, typename E>
inline bool read(A &a, B &b, C &c, D &d, E &e)
{
    return read(a) && read(b) && read(c) && read(d) && read(e);
}

template <typename A, typename B, typename C, typename D, typename E, typename F>
inline bool read(A &a, B &b, C &c, D &d, E &e, F &f)
{
    return read(a) && read(b) && read(c) && read(d) && read(e) && read(f);
}

template <typename T>
inline void read(vector<T> &now, const uint &sz)
{
    now.resize(sz);
    for (auto &v: now) read(v);
}
