#include<bits/stdc++.h>
#define MAXN 5005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define rec(i,x) for(int i=0;i<x;i++)
#define REC(i,x) for(int i=1;i<=x;i++)
#define Rec(i,f,t) for(LL i=f;i<=t;i++)
#define P pair<int,int>
#define LL long long
#define mms(x) memset(x,0,sizeof(x))
using namespace std;
namespace EDGE{
    struct Node{
        int u,v;
        LL w;
        Node* nxt;
    }E[MAXN*2];
    Node* Head[MAXN];
    int Tot;
    void Init(){
        memset(Head,NULL,sizeof(Head));
        Tot=0;
    }
    void addedge(int u,int v,LL w){
        Node* tmp=head[u];
        E[tot]={u,v,w,tmp};
        head[u]=(&E[tot]);
        ++tot;
    }
}
namespace HLD{ //heavy-light decomposition (edge based)
    int Dpth[MAXN],Sz[MAXN],Tp[MAXN],F[MAXN],Pos[MAXN],Son[MAXN],Fp[MAXN];
    //pos[u] indicates the hash of edge of point u to fa[u]
    int Tot;
    void Init(){
        EDGE::Init();
        memset(Son,-1,sizeof(Son));
        Tot=0;
    }
    void dfs1(int x,int fa,int d){
        Dpth[x]=d;
        F[x]=fa;
        Sz[x]=1;
        for(EDGE::Node* p=EDGE::Head[x];p;p=p->nxt){
            int v=p->v;
            if(v==fa)continue;
            dfs1(v,x,d+1);
            Sz[x]+=Sz[v];
            if(Son[x]==-1||Sz[Son[x]]<Sz[v]){
                Son[x]=v;
            }
        }
    }
    void dfs2(int x,int fa){
        Tp[x]=fa;
        Pos[x]=Tot++;
        Fp[Pos[x]]=x;
        if(Son[x]==-1)return;
        dfs2(Son[x],fa);
        for(EDGE::Node* p=EDGE::Head[x];p;p=p->nxt){
            int v=p->v;
            if(v!=Son[x]&&v!=F[x]){
                dfs2(v,v);
            }
        }
    }
    #define Calculate(x,y) (x+y)
    #define INITIAL_VALUE 0
    void Change(int u,int v,LL val,int EdgeBased){ //0 for point based, 1 for edge based
        int f1=Tp[u],f2=Tp[v];
        while(f1!=f2){
            if(Dpth[f1]<Dpth[f2]){
                swap(f1,f2);
                swap(u,v);
            }
            ST::Change(Pos[f1],Pos[u],val);
            u=F[f1];
            f1=Tp[u];
        }
        if(Dpth[u]>Dpth[v])swap(u,v);
        if(EdgeBased){
            if(u==v) return;
            ST::Change(Pos[Son[u]],Pos[v],val);
        }else{
            ST::Change(Pos[u],Pos[v],val);
        }
    }
    LL query(int u,int v,int EdgeBased){
        LL ans=INITIAL_VALUE;
        int f1=Tp[u],f2=Tp[v];
        while(f1!=f2){
            if(Dpth[f1]<Dpth[f2]){
                swap(f1,f2);
                swap(u,v);
            }
            ans=Calculate(ans,ST::Query(Pos[f1],Pos[u]));
            u=F[f1];
            f1=Tp[u];
        }
        if(Dpth[u]>Dpth[v])swap(u,v);
        if(EdgeBased){
            if(u==v) return ans;
            return Calculate(ans,ST::Query(Pos[Son[u]],Pos[v]));
        }else{
            return Calculate(ans,ST::Query(Pos[u],Pos[v]));
        }
    }
}

int main(){
    
    return 0;
}

