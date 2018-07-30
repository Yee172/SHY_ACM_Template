#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100500;
const ll M = 100500;
const static ll inf = 0x3f3f3f3f3f3f3f3f;

struct edge
{
    ll u;
    ll v;
    ll w;
};
vector<edge> e[N];

inline void insert_edge(ll u, ll v, ll w)
{
    e[u].push_back(edge{u, v, w});
}

inline void insert_double_edge(ll u, ll v, ll w)
{
    insert_edge(u, v, w);
    insert_edge(v, u, w);
}

ll vis[N];
ll dis[N];

ll dij(ll st, ll n)
{
    for (ll i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    priority_queue<pair<ll, ll> > q;
    q.push(make_pair(dis[st] = 0, st));
    while (!q.empty())
    {
        ll u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (ll i = 0; i < e[u].size(); i++)
        {
            ll v = e[u][i].v;
            ll w = e[u][i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push(make_pair(- dis[v], v));
            }
        }
    }
    return dis[n];
}

ll dp[N][N];
void floyd(ll n)
{
    for (ll k = 1; k <= n; k++)
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= n; j++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
}

// Judge the negative cycle
bool bellman_ford(ll st, ll n)
{
    for (ll i = 1; i <= n; ++i) dis[i] = inf;
    dis[st] = 0;
    for (ll t = 1; t <= n; t++)
        for (ll u = 1; u <= n; u++)
            for (ll i = 0; i < e[u].size(); i++)
            {
                ll v = e[u][i].v;
                ll w = e[u][i].w;
                if (dis[v] > dis[u] + w)
                    dis[v] = dis[u] + w;
            }
    for (ll u = 1; u <= n; u++)
        for (ll i = 0; i < e[u].size(); i++)
        {
            ll v = e[u][i].v;
            ll w = e[u][i].w;
            if (dis[v] > dis[u] + w) return true;
        }
    return false;
}

// Judge the negative cycle
bool spfa(ll st, ll n)
{
    queue<ll> q;
    for (ll i = 1; i <= n; ++i)
    {
        dis[i] = inf;
        vis[i] = 0;
    }
    q.push(st);
    dis[st] = 0;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        for (ll i = 0; i < e[u].size(); i++)
        {
            ll v = e[u][i].v;
            ll w = e[u][i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                vis[v]++;
                if (vis[v] > n) return true;
                q.push(v);
            }
        }
    }
    if (dis[st] < 0) return true;
    return false;
}


struct edge
{
    ll v;
    ll w;
    edge * next;
}e[M];

ll top;
edge * adjacency_list[N];

inline void insert_edge(ll u, ll v, ll w)
{
    e[top].v = v;
    e[top].w = w;
    e[top].next = adjacency_list[u];
    adjacency_list[u] = &e[top++];
}

inline void insert_edge_double(ll u, ll v, ll w)
{
    insert_edge(u, v, w);
    insert_edge(v, u, w);
}

ll dis[N];
ll vis[N];
ll dij(ll st, ll n, ll end)
{
    for (ll i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    priority_queue<pair<ll, ll> > q;
    q.push(make_pair(dis[st] = 0, st));
    while (!q.empty())
    {
        ll u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (edge * t = adjacency_list[u]; t; t = t->next)
        {
            ll v = t->v;
            ll w = t->w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push(make_pair(- dis[v], v));
            }
        }
    }
    return dis[end];
}

bool spfa(ll st, ll n)
{
    queue<ll> q;
    for (ll i = 1; i <= n; ++i)
    {
        dis[i] = inf;
        vis[i] = 0;
    }
    q.push(st);
    dis[st] = 0;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        for (edge * t = adjacency_list[u]; t; t = t->next)
        {
            ll v = t->v;
            ll w = t->w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                vis[v]++;
                if (vis[v] > n) return true;
                q.push(v);
            }
        }
    }
    return dis[st] < 0;
}


const int N = 205;
const int INF = 0x3f3f3f3f;
int n, m;

struct edge
{
    int v;
    int w;
    unsigned long rev;
};
vector<edge> G[N];

inline void insert_edge(int u, int v, int w)
{
    G[u].push_back(edge{v, w, G[v].size()});
    G[v].push_back(edge{u, 0, G[u].size() - 1});
}

int level[N];
int iter[N];
inline void bfs(int s)
{
    for (int i = 1; i <= n; i++) level[i] = -1;
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        for(int i = 0; i < G[u].size(); i++)
        {
            edge &e = G[u][i];
            if (e.w > 0 && level[e.v] < 0)
            {
                level[e.v] = level[u] + 1;
                que.push(e.v);
            }
        }
    }
}

int dfs(int u, int t, int f)
{
    if (u == t) return f;
    for(int &i = iter[u]; i < G[u].size(); i++)
    {
        edge &e = G[u][i];
        if (level[u] < level[e.v] && e.w > 0)
        {
            int d = dfs(e.v, t, min(f, e.w));
            if (d > 0)
            {
                e.w -= d;
                G[e.v][e.rev].w += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic(int s, int t)
{
    int flow = 0;
    for (;;)
    {
        bfs(s);
        if (level[t] < 0) return flow;
        for (int i = 1; i <= n; i++) iter[i] = 0;
        int f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

