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

