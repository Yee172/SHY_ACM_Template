#include <bits/stdc++.h>
using namespace std;

namespace segment_tree
{
    typedef long long LL;
    const int MAXN = 1e5 + 5;
    const LL INF = 2e18;
    LL a[MAXN];

    struct Node
    {
        int left, right;
        LL mi, ma;
        LL sum;
        LL add;
        int set;
    } tree[MAXN * 4];

    void PushUp(int rt)
    {
        int lson = rt << 1, rson = rt << 1 | 1;
        tree[rt].mi = min(tree[lson].mi, tree[rson].mi);
        tree[rt].ma = max(tree[lson].ma, tree[rson].ma);
        tree[rt].sum = tree[lson].sum + tree[rson].sum;
    }

    void PushDown(int rt)
    {
        if (tree[rt].left < tree[rt].right)
        {
            int lson = rt << 1, rson = rt << 1 | 1;
            if (tree[rt].set != -1)
            {
                tree[lson].set = tree[rt].set;
                tree[rson].set = tree[rt].set;
                tree[lson].add = tree[rson].add = 0;
                tree[lson].mi = tree[rson].mi = tree[rt].set;
                tree[lson].ma = tree[rson].ma = tree[rt].set;
                tree[lson].sum = (LL) tree[rt].set * (tree[lson].right - tree[lson].left + 1);
                tree[rson].sum = (LL) tree[rt].set * (tree[rson].right - tree[rson].left + 1);
                tree[rt].set = -1;
            }
            if (tree[rt].add)
            {
                tree[lson].add += tree[rt].add;
                tree[rson].add += tree[rt].add;
                tree[lson].mi += tree[rt].add;
                tree[rson].mi += tree[rt].add;
                tree[lson].ma += tree[rt].add;
                tree[rson].ma += tree[rt].add;
                tree[lson].sum += (LL) tree[rt].add * (tree[lson].right - tree[lson].left + 1);
                tree[rson].sum += (LL) tree[rt].add * (tree[rson].right - tree[rson].left + 1);
                tree[rt].add = 0;
            }
        }
    }

    void Build(int rt, int L, int R)
    {
        tree[rt].left = L;
        tree[rt].right = R;
        tree[rt].add = 0;
        tree[rt].set = -1;
        if (L == R)
        {
            tree[rt].sum = tree[rt].mi = tree[rt].ma = a[L];
            return;
        }
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        Build(rt << 1, L, mid);
        Build(rt << 1 | 1, mid + 1, R);
        PushUp(rt);
    }

    LL QuerySum(int rt, int L, int R)
    {
        if (R < tree[rt].left || L > tree[rt].right) return 0;
        if (L <= tree[rt].left && tree[rt].right <= R) return tree[rt].sum;
        PushDown(rt);
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        LL res = 0;
        if (L <= mid) res += QuerySum(rt << 1, L, R);
        if (R > mid) res += QuerySum(rt << 1 | 1, L, R);
        PushUp(rt);
        return res;
    }

    LL QueryMin(int rt, int L, int R)
    {
        if (L <= tree[rt].left && tree[rt].right <= R) return tree[rt].mi;
        PushDown(rt);
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        LL res = INF;
        if (L <= mid) res = min(res, QueryMin(rt << 1, L, R));
        if (R > mid) res = min(res, QueryMin(rt << 1 | 1, L, R));
        PushUp(rt);
        return res;
    }

    LL QueryMax(int rt, int L, int R)
    {
        if (L <= tree[rt].left && tree[rt].right <= R) return tree[rt].ma;
        PushDown(rt);
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        LL res = -INF;
        if (L <= mid) res = max(res, QueryMax(rt << 1, L, R));
        if (R > mid) res = max(res, QueryMax(rt << 1 | 1, L, R));
        PushUp(rt);
        return res;
    }

    void UpdateAdd(int rt, int L, int R, int x)
    {
        if (L <= tree[rt].left && tree[rt].right <= R)
        {
            tree[rt].add += x;
            tree[rt].sum += (LL) x * (tree[rt].right - tree[rt].left + 1);
            tree[rt].mi += x;
            tree[rt].ma += x;
            return;
        }
        PushDown(rt);
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        if (L <= mid) UpdateAdd(rt << 1, L, R, x);
        if (R > mid) UpdateAdd(rt << 1 | 1, L, R, x);
        PushUp(rt);
    }

    void Display(int rt)
    {
        cout << "-------------" << endl;
        cout << "id: " << rt << endl;
        cout << "[" << tree[rt].left << "," << tree[rt].right << "]" << endl;
        cout << "mi: " << tree[rt].mi << endl;
        cout << "ma: " << tree[rt].ma << endl;
        cout << "sum: " << tree[rt].sum << endl;
        cout << "add: " << tree[rt].add << endl;
        cout << "set: " << tree[rt].set << endl;
    }

    void bfs(int rt)
    {
        queue<int> q;
        while (!q.empty()) q.pop();
        q.push(rt);
        while (!q.empty())
        {
            int fst = q.front();
            q.pop();
            Display(fst);
            if (tree[fst].right > tree[fst].left)
            {
                q.push(fst << 1);
                q.push(fst << 1 | 1);
            }
        }
    }

    void UpdateSet(int rt, int L, int R, int x)
    {
        if (L <= tree[rt].left && tree[rt].right <= R)
        {
            tree[rt].set = x;
            tree[rt].sum = (LL) x * (tree[rt].right - tree[rt].left + 1);
            tree[rt].mi = x;
            tree[rt].ma = x;
            tree[rt].add = 0;
            return;
        }
        PushDown(rt);
        int mid = (tree[rt].left + tree[rt].right) >> 1;
        if (L <= mid) UpdateSet(rt << 1, L, R, x);
        if (R > mid)
        {
            UpdateSet(rt << 1 | 1, L, R, x);
        }
        PushUp(rt);
    }
}

template <typename T>
class SegmentTree
{
public:
    int n;
    int bit;
    SegmentTree() {}
    SegmentTree(int n) : n(n) {bit = 0;}

    void build(const T a[], const int start=1)
    {
        bit = 1;
        while (bit <= n + 1) bit <<= 1;
        for (int i = bit + 1, k = start; i <= bit + n; i++, k++)
            tree[i].minimum = tree[i].maximum = a[k];
        for (int i = bit - 1; i > 0; i--)
        {
            tree[i].maximum = max(tree[i << 1].maximum, tree[i << 1 | 1].maximum);
            tree[i].minimum = min(tree[i << 1].minimum, tree[i << 1 | 1].minimum);
            tree[i << 1].maximum -= tree[i].maximum;
            tree[i << 1].minimum -= tree[i].minimum;
            tree[i << 1 | 1].maximum -= tree[i].maximum;
            tree[i << 1 | 1].minimum -= tree[i].minimum;
        }
    }

    inline T query_maximum(int left, int right)
    {
        T lans = 0;
        T rans = 0;
        if (left == right)
        {
            left += bit;
            while (left) lans += tree[left].maximum, left >>= 1;
            return lans;
        }
        left += bit;
        right += bit;
        while (left ^ right ^ 1)
        {
            lans += tree[left].maximum;
            rans += tree[right].maximum;
            if (~ left & 1) lans = max(lans, tree[left ^ 1].maximum);
            if (right & 1) rans = max(rans, tree[right ^ 1].maximum);
            left >>= 1;
            right >>= 1;
        }
        lans += tree[left].maximum;
        rans += tree[right].maximum;
        T ans = max(lans, rans);
        while (left > 1) left >>= 1, ans += tree[left].maximum;
        return ans;
    }

    inline T query_minimum(int left, int right)
    {
        T lans = 0;
        T rans = 0;
        if (left == right)
        {
            left += bit;
            while (left) lans += tree[left].minimum, left >>= 1;
            return lans;
        }
        left += bit;
        right += bit;
        while (left ^ right ^ 1)
        {
            lans += tree[left].minimum;
            rans += tree[right].minimum;
            if (~ left & 1) lans = min(lans, tree[left ^ 1].minimum);
            if (right & 1) rans = min(rans, tree[right ^ 1].minimum);
            left >>= 1;
            right >>= 1;
        }
        lans += tree[left].minimum;
        rans += tree[right].minimum;
        T ans = min(lans, rans);
        while (left > 1) left >>= 1, ans += tree[left].minimum;
        return ans;
    }

private:
    struct node
    {
        T minimum, maximum;
    }tree[MAXN << 2];
};

template <typename T>
class SegmentTree
{
public:
    SegmentTree(int n) : n(n) {for (bit = 1; bit < n + 1; bit <<= 1);}
    inline void build(const T * a, const int start=1)
    {
        for (int i = bit + 1, k = start; i <= bit + n; i++, k++)
            sum[i] = maximum[i] = a[k];
        for (int i = bit - 1; i; i--)
        {
            sum[i] = sum[i << 1] + sum[i << 1 | 1];
            maximum[i] = max(maximum[i << 1], maximum[i << 1 | 1]);
        }
    }
    inline void update(const int index, const T val)
    {
        int i = index + bit;
        sum[i] = maximum[i] = val;
        for (i >>= 1; i; i >>= 1)
        {
            sum[i] = sum[i << 1] + sum[i << 1 | 1];
            maximum[i] = max(maximum[i << 1], maximum[i << 1 | 1]);
        }
    }
    inline T query_sum(const int left, const int right)
    {
        int l = left + bit - 1;
        int r = right + bit + 1;
        T lans = 0;
        T rans = 0;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1)
        {
            if (~ l & 1) lans += sum[l ^ 1];
            if (r & 1) rans += sum[r ^ 1];
        }
        return lans + rans;
    }
    inline T query_maximum(const int left, const int right)
    {
        int l = left + bit - 1;
        int r = right + bit + 1;
        T lans = -inf;
        T rans = -inf;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1)
        {
            if (~ l & 1) lans = max(lans, maximum[l ^ 1]);
            if (r & 1) rans = max(rans, maximum[r ^ 1]);
        }
        return max(lans, rans);
    }
private:
    int n;
    int bit;
    T sum[MAXN << 2];
    T maximum[MAXN << 2];
};

template <typename T>
class SegmentTree
{
public:
    SegmentTree(int n) : n(n) {for (bit = 1; bit < n + 1; bit <<= 1);}

    void build(const T * a, const int start=1)
    {
        for (int i = bit + 1, k = start; i <= bit + n; i++, k++)
            sum[i] = a[k];
        for (int i = bit - 1; i; i--)
        {
            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }
        for (int i = 1; i <= bit + n; i++) add[i] = 0;
    }

    inline void update(const int left, const int right, T val)
    {
        T lans = 0;
        T rans = 0;
        T k = 1;
        int l = left + bit - 1;
        int r = right + bit + 1;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1, k <<= 1)
        {
            sum[l] += val * lans;
            sum[r] += val * rans;
            if (~ l & 1)
                sum[l ^ 1] += val * k, add[l ^ 1] += val, lans += k;
            if (r & 1)
                sum[r ^ 1] += val * k, add[r ^ 1] += val, rans += k;
        }
        for (; l; l >>= 1, r >>= 1)
        {
            sum[l] += val * lans;
            sum[r] += val * rans;
        }
    }

    inline T query(const int left, const int right)
    {
        T lans = 0;
        T rans = 0;
        T k = 1;
        T ans = 0;
        int l = left + bit - 1;
        int r = right + bit + 1;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1, k <<= 1)
        {
            if (add[l]) ans += add[l] * lans;
            if (add[r]) ans += add[r] * rans;
            if (~ l & 1)
                ans += sum[l ^ 1], lans += k;
            if (r & 1)
                ans += sum[r ^ 1], rans += k;
        }
        for (; l; l >>= 1, r >>= 1)
        {
            ans += add[l] * lans;
            ans += add[r] * rans;
        }
        return ans;
    }
private:
    int n;
    int bit;
    T sum[MAXN << 2];
    T add[MAXN << 2];
};
