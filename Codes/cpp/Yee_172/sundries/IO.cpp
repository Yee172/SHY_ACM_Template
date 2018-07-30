#include <bits/stdc++.h>
using namespace std;

namespace fast_io
{
    namespace fast_io_head
    {
        const int __FREAD_BUFFER_SIZE__ = 1 << 20;
        char __BUFFER__[__FREAD_BUFFER_SIZE__], *__P1__=__BUFFER__, *__P2__=__BUFFER__;
        #define __IF_END__ (__P1__ == __P2__)
        #define __READ_ONE__ (fread(__BUFFER__, 1, __FREAD_BUFFER_SIZE__, stdin))
        #define __GET_CHAR__ (__IF_END__ && (__P2__ = (__P1__ = __BUFFER__) + __READ_ONE__, __IF_END__) ? -1 : *__P1__++)
        template <typename T>
        inline bool read(T &x)
        {
            char c;
            bool f = false;
            for (c = __GET_CHAR__; !isdigit(c); c = __GET_CHAR__)
            {
                if (c == EOF) return false;
                if (c == '-') f = true;
            }
            for (x = 0; isdigit(c); c = __GET_CHAR__) x = (x << 1) + (x << 3) + (c ^ 48);
            if (f) x = -x;
            return true;
        }
    }
    using namespace fast_io_head;

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
}

namespace fast_io
{
    namespace fast_io_head
    {
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
            for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
            if (f) x = -x;
            return true;
        }
    }
    using namespace fast_io_head;
    
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
}

