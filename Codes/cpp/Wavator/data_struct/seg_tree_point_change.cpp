struct segTree {
    static const int N = 100002 << 2;
#define type int
    type a[N];
    
    int n;
    
    void init(int n) {
        this->n = n;
    }
    
    inline void push_up(int rt) {
        a[rt] = a[rt << 1] + a[rt << 1 | 1];
    }
    void build(int l, int r, int rt, type * in) {
        if (l == r) {
            a[rt] = in[l];
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, rt << 1, in);
        build(mid + 1, r, rt << 1 | 1, in);
        push_up(rt);
    }
    
    
    inline void build(type * in) {
        build(1, n, 1, in);
    }
    
    void change(int pos, type x, int l, int r, int rt) {
        if (l == r)
            return (void)(a[rt] = x);
        int mid = l + r >> 1;
        if (pos <= mid)
            change(pos, x, l, mid, rt << 1);
        else
            change(pos, x, mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    
    inline void change(int pos, type x) {
        change(pos, x, 1, n, 1);
    }

    type query(int L, int R, int l, int r, int rt) {
        if (l >= L && r <= R)
            return a[rt];
        int mid = l + r >> 1;
        type res = 0;
        if (L <= mid)
            res += query(L, R, l, mid, rt << 1);
        if (R > mid)
            res += query(L, R, mid + 1, r, rt << 1 | 1);
        return res;
    }
    
    inline type query(int L, int R) {
        return query(L, R, 1, n, 1);
    }
    
#undef type
};
