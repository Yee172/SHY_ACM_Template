#include<bits/stdc++.h>
#define MAXN 100005
#define INF 0x3f3f3f3f
#define BU 15
#define LL long long
#define P pair<int,int>
using namespace std;

int f[MAXN][BU];
int Value[MAXN][BU]; //Value[x][i]: least value on the path from x to his 2^i ancestor.
int dpth[MAXN];
vector<P> E[MAXN];

void init(){
    memset(dpth,-1,sizeof(dpth));
}

void dfs(int root,int deep) //initial the depth from root
{
    dpth[root]=deep;
    int sz=E[root].size();
    for(int i=0;i<sz;i++){
        int v=E[root][i].first;
        int Va=E[root][i].second;
        if(dpth[v]<0){
            f[v][0]=root;
            Value[v][0]=Va;
            dfs(v,deep+1);
        }
    }
}
void init_f(int n){//f[x][0],Value[x][0] should have been read before using

    for(int j=1;j<BU;j++)
    for(int i=1;i<=n;i++){
        f[i][j]=f[ f[i][j-1] ][j-1];
    }
    for(int j=1;j<BU;j++)
    for(int i=1;i<=n;i++){
        Value[i][j]=min(Value[i][j-1],Value[f[i][j-1]][j-1]);
    }
}
int LCA(int u,int v,int& ans){//Least Common Ancestors, ans is the least value in the path(u,v)
    ans=INF;
    if(dpth[u]<dpth[v])swap(u,v);
    int d=dpth[u]-dpth[v];
    for(int i=0;i<BU;i++){
        if(d&(1<<i)){
            ans=min(ans,Value[u][i]);
            u=f[u][i];
        }
    }
    if(u==v)return u;
    for(int i=BU-1;i>=0;i--){
        if(f[u][i]!=f[v][i]){
            ans=min(ans,Value[u][i]);
            ans=min(ans,Value[v][i]);
            u=f[u][i];
            v=f[v][i];
        }
    }
    ans=min(ans,Value[u][0]);
    ans=min(ans,Value[v][0]);
    return f[u][0];
}

int main(){
    int n;
    scanf("%d",&n);
    init();
    for(int i=1;i<n;i++){
        int t1,t2,t3;
        scanf("%d%d%d",&t1,&t2,&t3);
        E[t1].push_back(P(t2,t3));
        E[t2].push_back(P(t1,t3));
    }
    dfs(1,0);
    init_f(n);
    int q;
    scanf("%d",&q);
    while(q--){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        int ans;
        int lca=LCA(t1,t2,ans);
        printf("%d %d\n",lca,ans);
    }
    return 0;
}

