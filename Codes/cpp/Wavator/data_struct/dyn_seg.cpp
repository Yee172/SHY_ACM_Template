#include <bits/stdc++.h>
using namespace std;
int pid;
struct dyn_seg
{
    static const int N = 300010 * 50;
    struct seg
    {
        int l, r, cnt, flg;
        inline void gao() {
            if (l)
                return;
            l = ++pid;
            r = ++pid;
            assert(pid <= N);
        }
    };

    seg s[N];

    void init() {
        ::pid = 0;
    }

    inline void push_up(int rt) {
        s[rt].cnt = s[s[rt].l].cnt + s[s[rt].r].cnt;
    }

    inline void push_down(int who, int sz, int flg) {
        if (flg) {
            s[who].cnt = (flg == 1? sz: 0);
            s[who].flg = flg;
        }
    }

    void change(int L, int R, int val, int l, int r, int rt) {
        if (l >=  L && r <= R) {
            push_down(rt, r - l + 1, val);
            return;
        }
        s[rt].gao();
        int mid = l + r >> 1;
        push_down(s[rt].l, mid - l + 1, s[rt].flg);
        push_down(s[rt].r, r - mid, s[rt].flg);
        s[rt].flg = 0;
        if (L <= mid)
            change(L, R, val, l, mid, s[rt].l);
        if (R > mid)
            change(L, R, val, mid + 1, r, s[rt].r);
        push_up(rt);
    }

};
dyn_seg tree;
