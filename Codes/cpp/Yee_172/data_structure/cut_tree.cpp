#include<bits/stdc++.h>
using namespace std;

class CutTree
{
public:
    int son[MAXN], father[MAXN];
    int depth[MAXN], son_size[MAXN];
    int father_top[MAXN], id[MAXN], tot;
    CutTree() {}
    void init()
    {
        dfs1(1, 1, 0);
        dfs2(1, 1);
    }
    inline void insert_edge(int u, int v)
    {
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
private:
    vector<int> edge[MAXN];
    void dfs1(int x, int v, int dpt)
    {
        father[x] = v;
        son_size[x] = 1;
        depth[x] = dpt;
        int sz = edge[x].size();
        int mxsz = 0;
        int mxn = 0;
        for(int i = 0; i < sz; i++)
        {
            int u = edge[x][i];
            if (u==v) continue;
            dfs1(u, x, dpt + 1);
            son_size[x] += son_size[u];
            if(son_size[u] > mxsz)
            {
                mxsz = son_size[u];
                mxn = u;
            }
        }
        son[x] = mxn;
    }
    void dfs2(int x, int ftp)
    {
        father_top[x] = ftp;
        id[x] = ++tot;
        if (son[x]) dfs2(son[x],ftp);
        int sz = edge[x].size();
        for(int i = 0; i < sz; i++)
        {
            int u = edge[x][i];
            if(u == father[x] || u == son[x]) continue;
            dfs2(u, u);
        }
    }
};

inline void gao(CutTree &t, SegmentTree<ll> &s, int x, int y)
{
    ll ans = 0;
    while(t.father_top[x] != t.father_top[y])
    {
        if(t.depth[t.father_top[x]] < t.depth[t.father_top[y]])
        {
            ans += s.query(t.id[t.father_top[y]], t.id[y]);
            y = t.father[t.father_top[y]];
        }
        else
        {
            ans += s.query(t.id[t.father_top[x]], t.id[x]);
            x = t.father[t.father_top[x]];
        }
    }
    if(t.depth[x] > t.depth[y]) x ^= y, y ^= x, x ^= y;
    printf("%lld\n", ans + s.query(t.id[x], t.id[y]));
}
