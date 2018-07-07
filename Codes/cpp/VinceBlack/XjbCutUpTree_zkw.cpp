/*
	HDU3966-Aragorn's Story
	Range add, decrease or query on the whole path between any two nodes on a tree
*/
#include<bits/stdc++.h>
#define MAXN 200005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LL long long
#define mms(x) memset(x,0,sizeof(x))
using namespace std;
int A[MAXN],n,N;
int Sum[MAXN],Add[MAXN];
void build(int n){
    N=1;
    while(N<n+2)N<<=1;
    for(int i=1;i<=n;i++)Sum[i+N]=A[i];
    for(int i=N-1;i>0;i--){
        Sum[i]=Sum[i<<1]+Sum[i<<1|1];
        Add[i]=0;
    }
}
void Update(int l,int r,int c){
    int s,t,ln=0,rn=0,x=1;
    for(s=N+l-1,t=N+r+1;s^t^1;s>>=1,t>>=1,x<<=1){
        Sum[s]+=c*ln;
        Sum[t]+=c*rn;
        if(~s&1) Add[s^1]+=c,Sum[s^1]+=c*x,ln+=x;
        if( t&1) Add[t^1]+=c,Sum[t^1]+=c*x,rn+=x;
    }
    for(;s;s>>=1,t>>=1){
        Sum[s]+=c*ln;
        Sum[t]+=c*rn;
    }
}
int Query(int l,int r){
    int s,t,ln=0,rn=0,x=1;
    int ans=0;
    for(s=N+l-1,t=N+r+1;s^t^1;s>>=1,t>>=1,x<<=1){
        ans+=Add[s]*ln;
        ans+=Add[t]*rn;
        if(~s&1) ans+=Sum[s^1],ln+=x;
        if( t&1) ans+=Sum[t^1],rn+=x;
    }
    for(;s;s>>=1,t>>=1){
        ans+=Add[s]*ln;
        ans+=Add[t]*rn;
    }
    return ans;
}
int son[MAXN],value[MAXN],f[MAXN],dpth[MAXN],sonsz[MAXN];
int ftop[MAXN],id[MAXN],tot;
vector<int> E[MAXN];
void init(int n){
    mms(son);
    mms(value);
    mms(f);
    mms(dpth);
    mms(sonsz);
    mms(ftop);
    mms(id);
    mms(Sum);
    mms(A);
    mms(Add);
    for(int i=0;i<=n;i++) E[i].clear();
    tot=0;
}
void dfs1(int x,int v,int dpt){
    f[x]=v;
    sonsz[x]=1;
    dpth[x]=dpt;
    int sz=E[x].size();
    int mxsz=0;
    int mxn=0;
    for(int i=0;i<sz;i++){
        int u=E[x][i];
        if(u==v)continue;
        dfs1(u,x,dpt+1);
        sonsz[x]+=sonsz[u];
        if(sonsz[u]>mxsz){
            mxsz=sonsz[u];
            mxn=u;
        }
    }
    son[x]=mxn;
}
void dfs2(int x,int ftp){
    ftop[x]=ftp;
    id[x]=++tot;
    if(son[x]){
        dfs2(son[x],ftp);
    }
    int sz=E[x].size();
    for(int i=0;i<sz;i++){
        int u=E[x][i];
        if(u==f[x]||u==son[x])continue;
        dfs2(u,u);
    }
}
int gao(int x,int y,int c,int opt){
    int ans=0;
    while(ftop[x]!=ftop[y]){
        if(dpth[ftop[x]]<dpth[ftop[y]]){
            if(opt==0){
                Update(id[ftop[y]],id[y],c);
            }else{
                ans+=Query(id[ftop[y]],id[y]);
            }
            y=f[ftop[y]];
        }else{
            if(opt==0){
                Update(id[ftop[x]],id[x],c);
            }else{
                ans+=Query(id[ftop[x]],id[x]);
            }
            x=f[ftop[x]];
        }
    }
    if(dpth[x]>dpth[y])swap(x,y);
    if(opt==0){
        Update(id[x],id[y],c);
    }else{
        ans+=Query(id[x],id[y]);
    }
    return ans;
}
int main(){
    int m,q;
    while(scanf("%d%d%d",&n,&m,&q)!=EOF){
        init(n);
        for(int i=1;i<=n;i++) scanf("%d",&value[i]);
        for(int i=1;i<=m;i++){
            int t1,t2;
            scanf("%d%d",&t1,&t2);
            E[t1].push_back(t2);
            E[t2].push_back(t1);
        }
        dfs1(1,1,0);
        dfs2(1,1);
        for(int i=1;i<=n;i++){
            A[id[i]]=value[i];
        }
        build(n);
        for(int i=1;i<=q;i++){
            char s[3];
            scanf("%s",s);
            if(s[0]=='I'){
                int t1,t2,t3;
                scanf("%d%d%d",&t1,&t2,&t3);
                gao(t1,t2,t3,0);
            }else if(s[0]=='D'){
                int t1,t2,t3;
                scanf("%d%d%d",&t1,&t2,&t3);
                gao(t1,t2,-t3,0);
            }else{
                int t1;
                scanf("%d",&t1);
                printf("%d\n",gao(t1,t1,0,1));
            }
        }
    }

    return 0;
}
