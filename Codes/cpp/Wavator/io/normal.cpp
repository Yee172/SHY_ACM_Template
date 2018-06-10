#define gc getchar()

template <typename T> inline bool read(T &x) {
    bool f = false;
    char c;
    for (c = gc; !isdigit(c); c = gc) {
        if (c == EOF)
            return false;
        if (c == '-')
            f ^= true;
    }
    for (x = 0; isdigit(c); c = gc) {
        x = x << 1 + x << 3 + x ^ 48;
    }
    if (f) {
        x = -x;
    }
}

#undef gc
