#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define ll long long
static const ll N = 1e5 + 5;
static const ll M = 2e5 + 98;

struct VinceGragh
{
    struct edge
    {
        ll u;
        ll v;
        ll w;
        bool operator <(const edge &o)const
        {
            return w < o.w;
        }
    };
    vector<edge> e[N];

    inline void insert_Vince(ll u, ll v, ll w = 0)
    {
        e[u].push_back(edge{u, v, w});
    }

    inline void insert_double_Vince(ll u, ll v, ll w = 0)
    {
        insert_Vince(u, v, w);
        insert_Vince(v, u, w);
    }

    ll dis[N];
    ll vis[N];
    const static ll inf = 0x3f3f3f3f3f3f3f3f;
    ll Vince_solve_this_dij(ll st, ll n)
    {
        for (ll i = 1; i <= n; ++i)
            dis[i] = inf;
        memset(vis,0,sizeof vis);
        priority_queue<pair<ll, ll> > q;
        q.push(make_pair(dis[st]=0,st));
        while(!q.empty())
        {
            ll u = q.top().second;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            for (ll i = 0; i < e[u].size(); ++i)
            {
                ll v = e[u][i].v;
                ll c = e[u][i].w;
                if (dis[v] > dis[u] + c)
                {
                    dis[v] = dis[u] + c;
                    q.push(make_pair(-dis[v],v));
                }
            }
        }
        return dis[n];
    }

    ll Vince_solve_this_spfa(ll st, ll n)
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
            for (ll i = 0; i < e[u].size(); ++i)
            {
                ll v = e[u][i].v;
                ll w = e[u][i].w;
                if (dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    vis[v]++;
                    q.push(v);
                }
            }
            vis[u] = 0;
        }
        return dis[n];
    }

    ll Vince_clk, white[N], Zu, Zuno[N];

    stack<ll> Vs;


    ll in[N], out[N];

    void Vince_Destory_scc(ll n)
    {
        for (ll i = 1; i <= n; ++i)
            for (ll j = 0; j < e[i].size(); ++j)
            {
                ll v = e[i][j].v;
                if (Zuno[i] != Zuno[v])
                {
                    in[Zuno[i]]++;
                    out[Zuno[v]]++;
                }
            }
    }

    pair<ll, ll> Vince_solve_this_scc_pro()
    {
        ll a = 0, b = 0;
        for (ll i = 1; i <= Zu; ++i)
            a+=(in[i]==0), b += (out[i]==0);
        return make_pair(b, max(a, b));
    }

    void Vince_suo(ll n)
    {
        while (!Vs.empty()) Vs.pop();
        Vince_clk = 0;
        memset(white,0,sizeof(white));
        Zu = 0;
        memset(Zuno,0,sizeof(Zuno));
        memset(vis,0,sizeof(vis));
        for (ll i = 1; i <= n; ++i)
            if (!vis[i])
                Vince_solve_this_scc(i);
        Vince_Destory_scc(n);
    }

    void Vince_solve_this_scc(ll u)
    {
        white[u] = vis[u] = ++Vince_clk;
        Vs.push(u);
        for (ll i = 0; i < e[u].size(); ++i)
        {
            ll v = e[u][i].v;
            if (!vis[v])
            {
                Vince_solve_this_scc(v);
                white[u] = min(white[u], white[v]);
            }
            else if(!Zuno[v])
                white[u]=min(white[u], vis[v]);
        }
        if(white[u] == vis[u])
        {
            Zu++;
            for (;;)
            {
                ll now_vince = Vs.top();
                Vs.pop();
                Zuno[now_vince] = Zu;
                if(now_vince == u)
                    break;
            }
        }
    }

    void Vince_solve_this_bcc(ll u, ll fa)
    {

    }

    void Vince_Destory_trashes()
    {
        for (ll i = 0; i < N; ++i)
            e[i].clear();
    }

    vector<edge> Vince_mst_graph;

    ll black[N];

    ll findBlack(ll u)
    {
        return u == black[u] ? u: black[u] = findBlack(black[u]);
    }

    ll Vince_MST()
    {
        ll this_little_Vince = 0;
        Vince_mst_graph.clear();
        for (ll i = 0; i < N; ++i)
            black[i] = i;
        challenge_the_boss_of_the_gym();
        for (ll i = 0; i < N; i++)
            for (ll j = 0; j < e[i].size(); ++j)
                Vince_mst_graph.push_back(e[i][j]);
        sort(Vince_mst_graph.begin(), Vince_mst_graph.end());
        ll tot = (ll)Vince_mst_graph.size();
        for (ll i = 0; i < tot; ++i)
        {
            ll u = Vince_mst_graph[i].u, v = Vince_mst_graph[i].v;
            u = findBlack(u);
            v = findBlack(v);
            if (u != v)
            {
                black[u] = v;
                this_little_Vince += Vince_mst_graph[i].w;
            }
        }
        return this_little_Vince;
    }

    void challenge_the_boss_of_the_gym()
    {
        for (int i = 0; i < N; ++i)
            random_shuffle(e[i].begin(), e[i].end());
    }


    VinceGragh Vince_make_negative_himSelf(ll n)
    {
        VinceGragh myVince;
        myVince.Vince_Destory_trashes();
        for (ll i = 1; i <= n; ++i)
        {
            for (ll j = 0; j < e[i].size(); ++j)
            {
                ll v = e[i][j].v;
                ll c = e[i][j].w;
                myVince.insert_Vince(v, i, c);
            }
        }
        return myVince;
    }


    ll Vince_in_two_vinces(VinceGragh &a, VinceGragh &b, ll n, ll st1, ll st2)
    {
        a.Vince_solve_this_dij(st1,n);
        b.Vince_solve_this_dij(st2,n);
        ll ans = 0;
        for (ll i = 1; i <= n; ++i)
            if(i!=st1 && i!=st2)
                ans = max(ans, a.dis[i] + b.dis[i]);
        return ans;
    }
};

VinceGragh Vince_help_me_solve_this_problem;
