#include <bits/stdc++.h>
using namespace std;
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
