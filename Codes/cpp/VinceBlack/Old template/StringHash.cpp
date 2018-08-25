#include<bits/stdc++.h>
#define LL long long
#define MAXN 2000005
#define INF 0x3f3f3f3f
#define rec(i,x) for(int i=0;i<x;i++)
#define REC(i,x) for(int i=1;i<=x;i++)
#define F(i,s,e) for(int i=s;i<=e;i++)
#define MST(x) memset(x,0,sizeof(x))
#define MSTLOW(x) memset(x,-1,sizeof(x))
#define rd(x) scanf("%d",&x)
#define P pair<int,int>
#define MP(x,y) make_pair(x,y)
#define VinceBlack std::ios::sync_with_stdio(false);
#define lson x<<1
#define rson x<<1|1
#define SEED 131LL
#define pii pair<long long,long long>
using namespace std;

inline LL pow(LL x,LL y,LL p){LL t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}
const LL mod[2]={532919237LL,9587LL};
char S[MAXN];
LL F[2][MAXN];
LL pre[2][MAXN];
void init_pre(){
    for(int t=0;t<2;t++){
        F[t][0]=1LL;
        for(int i=1;i<MAXN;i++){
            F[t][i]=(LL)F[t][i-1]*SEED%mod[t];
        }
    }
}
pii Hash(char* s,int len){
    LL ret[2]={0};
    for(int t=0;t<2;t++){
        for(int i=0;i<len;i++){
            ret[t]=(ret[t]*SEED+s[i])%mod[t];
            pre[t][i]=ret[t];
        }
    }
    return pii(ret[0],ret[1]);
}
pii Hash(char* s,int l,int r){
    LL ret[2];
    for(int t = 0; t <= 1; t++){
        ret[t]=(pre[t][r]-((l-1>=0)?pre[t][l-1]:0LL)*F[t][r-l+1]%mod[t]+mod[t])%mod[t];
    }
    return pii(ret[0],ret[1]);
}
int vis[MAXN];
vector<int>* head;
int nxt[MAXN];
int tail[MAXN];
int tmpv[MAXN];
int tot;
pii* tmp;
int main(){
    tmp = new pii[MAXN];
    head = new vector<int>[1000007];
    memset(nxt,-1,sizeof(nxt));
    memset(tail,-1,sizeof(tail));
    init_pre();
    int n=0;
    int c;
    while((c=getchar())!=EOF){
        if(!isalpha(c))break;
        S[n++]=c;
    }

    for(int i=0;i<n;i++) S[i+n]=S[i];
    Hash(S,n<<1);
    for(int i=0;i<n;i++){
        tmp[i]=Hash(S,i,i+n);
        LL p=(tmp[i].first^tmp[i].second)%1000007;
        int boom=0;
        int sz=head[p].size();
        for(int j=0;j<sz;j++){
            if(tmp[i]==tmp[head[p][j]]){
                nxt[tail[head[p][j]]]=i;
                boom=1;
                tail[head[p][j]]=i;
                break;
            }
        }
        if(!boom){
            head[p].push_back(i);
            tail[i]=i;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            ++ans;
            int cur=i;
            vis[i]=1;
            while(nxt[cur]!=-1){
                cur=nxt[cur];
                vis[cur]=1;
            }
        }
    }
    printf("%d",ans);
    putchar('\n');
    memset(vis,0,sizeof(vis));
    for(int i=0;i<n;i++){
        if(!vis[i]){
            tot=0;
            tmpv[tot++]=i;
            int cur=i;
            vis[i]=1;
            while(nxt[cur]!=-1){
                cur=nxt[cur];
                vis[cur]=1;
                tmpv[tot++]=(cur);
            }
            printf("%d",tot);
            putchar(' ');
            for(int j=0;j<tot;j++){
                printf("%d",tmpv[j]);
                putchar(' ');
            }
            putchar('\n');
        }
    }
    return 0;
}
