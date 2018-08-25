#include<bits/stdc++.h>
#define LL long long
#define MAXN 20005
#define INF 0x3f3f3f3f
#define MOD 1000000007LL
#define rec(i,x) for(int i=0;i<x;i++)
#define REC(i,x) for(int i=1;i<=x;i++)
#define F(i,s,e) for(int i=s;i<=e;i++)
#define MST(x) memset(x,0,sizeof(x))
#define MSTLOW(x) memset(x,-1,sizeof(x))
#define rd(x) scanf("%d",&x)
#define P pair<int,int>
#define MP(x,y) make_pair(x,y)
#define VinceBlack std::ios::sync_with_stdio(false);
using namespace std;
inline char gc() { static char buf[1<<20],*h=buf,*t=buf;return (h==t&&(t=(h=buf)+fread(buf,1,1<<20,stdin),h==t)?-1:*h++);}
template <typename T> inline bool read(T &x){static int f;static char c;for(c=gc(),f=1;!isdigit(c);c=gc()){if(c==-1)return false;else if(c==45)f=-1;}for(x=c-48;isdigit(c=gc());x=x*10+c-48);return x*=f,true; }
template <typename A, typename B> inline bool read(A&x, B&y) {return read(x) && read(y);}
template <typename A, typename B, typename C> inline bool read(A&x,B&y,C&z){return read(x)&&read(y)&&read(z);}
inline LL pow(LL x,LL y,LL p){LL t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}
struct Edge{
    int v,w;
    Edge* nxt;
    Edge(int vv=0,int ww=0){v=vv,w=ww;}
}E[MAXN];
int tot;
Edge* head[MAXN];
int N,K[105],q;
void AddEdge(int u,int v,int w){
    E[tot]=Edge(v,w);
    E[tot].nxt=head[u];
    head[u]=(&E[tot]);
    ++tot;
}
int sz[MAXN],mxsonsz[MAXN],totsz;
int vis[MAXN],center;
void getCenter(int x,int fa){
    sz[x]=1,mxsonsz[x]=0;
    for(Edge* p=head[x];p!=NULL;p=p->nxt){
        int v=p->v, w=p->w;
        if(vis[v]||v==fa)continue;
        getCenter(v,x);
        sz[x]+=sz[v];
        mxsonsz[x]=max(mxsonsz[x],sz[v]);
    }
    mxsonsz[x]=max(mxsonsz[x],totsz-sz[x]);
    if(center==-1||mxsonsz[x]<mxsonsz[center])center=x;
}
int dpth[MAXN],now[MAXN];
void getdpth(int x,int fa){
    now[++now[0]]=dpth[x];
    for(Edge* p=head[x];p!=NULL;p=p->nxt){
        int v=p->v, w=p->w;
        if(vis[v]||v==fa)continue;
        dpth[v]=dpth[x]+w;
        getdpth(v,x);
    }
}
int getsum(int x,int len,int kn){
    now[0]=0;
    dpth[x]=len;
    getdpth(x,-1);
    sort(now+1,now+1+now[0]);
    int l=1,r=now[0],sm=0;
    while(l<r){
        if(now[l]+now[r]<K[kn])++l;
        else if(now[l]+now[r]>K[kn])--r;
        else ++sm,++l;
    }
    return sm;
}
int ans[105];
void getans(int x){
    vis[x]=1;
    for(int i=1;i<=q;i++)ans[i]+=getsum(x,0,i);
    for(Edge* p=head[x];p!=NULL;p=p->nxt){
        int v=p->v, w=p->w;
        if(vis[v])continue;
        for(int i=1;i<=q;i++)ans[i]-=getsum(v,w,i);
        center=-1;
        totsz=sz[v];
        getCenter(v,x);
        getans(center);
    }
}
int main(){
    scanf("%d",&N);
    for(int i=0;i<=N;i++) head[i]=NULL;
    for(int i=1;i<=N-1;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }
    for(int i=1;i<=q;i++) scanf("%d",&K[i]);
    center=-1;
    getCenter(1,-1);
    getans(center);
    for(int i=1;i<=q;i++){
        if(ans[i]>0)puts("AYE");
        else puts("NAY");
    }
    return  0;
}
