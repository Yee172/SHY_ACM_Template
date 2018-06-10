char OOXOO[1<<20],*XXOO=OOXOO,*OOXX=OOXOO;
#define gc (XXOO == OOXX && (OOXX = (XXOO = OOXOO) + fread(OOXOO, 1, 1 << 20, stdin), XXOO == OOXX)? -1: *XXOO++)

template <typename T> inline bool read(T &x) {
    bool f = false;
    char c;
    for (c = gc; !isdigit(c); c = gc) {
        if (c == EOF)
            return false;
        if (c == '-')
            f = true;
    }
    for (x = 0; isdigit(c); c = gc) {
        x = x * 10 + c - 48;
    }
    if (f) {
        x = -x;
    }
}

#undef gc
