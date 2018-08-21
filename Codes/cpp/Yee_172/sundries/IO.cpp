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
    using fast_io_head::read;

    template <typename T>
    inline bool read(vector<T> &object) { bool flag = true; for (auto &v : object) flag &= read(v); return flag; }

    template <typename H, typename ...T>
    inline bool read(H &head, T &...tail) { return read(head) && read(tail...); }
}
using fast_io::read;

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
    using fast_io_head::read;

    template <typename T>
    inline bool read(vector<T> &object) { bool flag = true; for (auto &v : object) flag &= read(v); return flag; }

    template <typename H, typename ...T>
    inline bool read(H &head, T &...tail) { return read(head) && read(tail...); }
}
