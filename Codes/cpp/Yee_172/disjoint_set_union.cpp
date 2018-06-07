#include <bits/stdc++.h>
using namespace std;
#define MAXN 10050

struct DSU
{
    int fa[MAXN];

    void init(int n)
    {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }

    int find(int x)
    {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y) fa[x] = y;
    }
} dsu;
