#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<ctime>
#define LL long long
#define MAXN 700
#define MOD 1000000007
#define P pair<int,int>
#define INF 0x3f3f3f3f
using namespace std;
int E[MAXN][MAXN];
int pre[MAXN];
int vis[MAXN];
int no[MAXN];
int tot;
bool bfs(int s,int t){
    memset(pre,-1,sizeof(pre));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s]=1;
    while(!q.empty()){
        int tp=q.front(); q.pop();
        for(int i=1;i<=tot;i++)if(E[tp][i] && !vis[i]){
            pre[i]=tp;
            vis[i]=1;
            if(i==t) return true;
            q.push(i);
        }
    }
    return false;
}
int EK(int s,int t){
    int ans=0;
    while(bfs(s,t)){
        int mi=INF;
        for(int i=t;i!=s;i=pre[i]){
            mi=min(mi,E[pre[i]][i]);
        }
        for(int i=t;i!=s;i=pre[i]){
            E[pre[i]][i]-=mi;
            E[i][pre[i]]+=mi;
        }
        ans+=mi;
    }
    return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    clock_t st=clock();
#endif // ONLINE_JUDGE
    int n,f,d;
    scanf("%d%d%d",&n,&f,&d);
    for(int i=1;i<=n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        for(int j=0;j<a;j++)
        {
            int t;
            scanf("%d",&t);
            E[t][i+f]=1;
            E[f+n+n+d+1][t]=1;
        }
        for(int j=0;j<b;j++)
        {
            int t;
            scanf("%d",&t);
            E[i+f+n][t+f+n+n]=1;
            E[t+f+n+n][f+n+n+d+2]=1;
        }
    }
    for(int i=1;i<=n;i++) E[i+f][i+f+n]=1;
    tot=f+d+n+n+2;
    int ans=EK(f+d+n+n+1,f+d+n+n+2);
    printf("%d\n",ans);

#ifndef ONLINE_JUDGE
    fprintf(stderr,"Time Cost:%lf\n",(double)(clock()-st)/CLOCKS_PER_SEC);
#endif // ONLINE_JUDGE
    return 0;
}
