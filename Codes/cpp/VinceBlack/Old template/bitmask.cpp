LL lowerBit(LL i){
    return i&(-i);
}
LL mmax(LL a,LL b){
    return (a<b)?b:a;
}
void addBIT(LL pos,LL x){
    height[pos]=x;
    LL lx;
    while (pos<=n){
        maxh[pos]=height[pos];
        lx=lowerBit(pos);
        for (LL i=1;i<lx;i<<=1){
            maxh[pos]=mmax(maxh[pos-i],maxh[pos]);
        }
        pos+=lx;
    }
}
LL maxInRange(LL x,LL y){
    LL ans=0;
    while (y>=x){
        ans=mmax(height[y],ans);
        --y;
        for (;y-lowerBit(y)>=x;y-=lowerBit(y)){
            ans=mmax(maxh[y],ans);
        }
    }
    return ans;
}




/////////////二维区间增值，单点查
LL n,m;
vector<vector<LL> > mx;
struct BitTree{
    vector<vector<LL> > t;
    void init(LL n,LL m){
        this->t.assign(n+1,vector<LL>(m+1,0));
    }
    inline LL bt(LL x){
        return x&-x;
    }
    void addD(LL x,LL y,LL z){
        for(LL X=x;X<=n;X+=bt(X))
        for(LL Y=y;Y<=m;Y+=bt(Y)){
            t[X][Y]+=z;
        }
    }
    void range_add(LL xa,LL ya,LL xb,LL yb,LL z){
        addD(xa,ya,z);
        addD(xa,yb+1,-z);
        addD(xb+1,ya,-z);
        addD(xb+1,yb+1,z);
    }

    LL query(LL x,LL y){
        LL res=0;
        for(LL i=x;i>0;i-=bt(i))
        for(LL j=y;j>0;j-=bt(j)){
            res+=t[i][j];
        }
        return res;
    }

}t1;

//二维区间查值，二维区间加值
#include<bits/stdc++.h>
#define LL long long
#define MAXN 1000005
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
using namespace std;
inline LL pow(LL x,LL y,LL p){LL t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}
const LL BASE=10000000000000LL;
LL n,m;
vector<vector<LL> > t1,t2,t3,t4,mx;

void init(){
    t1.assign(n+1,vector<LL>(m+1,0));
    t2.assign(n+1,vector<LL>(m+1,0));
    t3.assign(n+1,vector<LL>(m+1,0));
    t4.assign(n+1,vector<LL>(m+1,0));
    mx.assign(n+1,vector<LL>(m+1,0));
}
inline LL bt(LL x){
    return x&-x;
}
void addD(LL x,LL y,LL z){
    for(LL X=x;X<=n;X+=bt(X))
    for(LL Y=y;Y<=m;Y+=bt(Y)){
        t1[X][Y]+=z;
        t2[X][Y]+=z*x;
        t3[X][Y]+=z*y;
        t4[X][Y]+=z*x*y;
    }
}
void range_add(LL xa,LL ya,LL xb,LL yb,LL z){
    addD(xa,ya,z);
    addD(xa,yb+1,-z);
    addD(xb+1,ya,-z);
    addD(xb+1,yb+1,z);
}

LL query(LL x,LL y){
    LL res=0;
    for(LL i=x;i;i-=bt(i))
    for(LL j=y;j;j-=bt(j)){
        res+=(x+1)*(y+1)*t1[i][j]-(y+1)*t2[i][j]-(x+1)*t3[i][j]+t4[i][j];
    }
    return res;
}
LL range_query(LL xa,LL ya,LL xb,LL yb){
    return query(xb,yb)-query(xb,ya-1)-query(xa-1,yb)+query(xa-1,ya-1);
}

int main(){
    int T;
    scanf("%lld%lld%d",&n,&m,&T);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            LL tmp;
            scanf("%lld",&tmp);
            mx[i][j]=tmp;
        }
    }
    for(int i=1;i<=T;i++){
        LL x1,y1,x2,y2,k;
        scanf("%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&k);
        range_add(x1,y1,x2,y2,BASE+k);
    }
    LL ans=0;
    for(LL i=1;i<=n;i++)
    for(LL j=1;j<=m;j++){
        LL cur=range_query(i,j,i,j);
        //printf("%lld %lld: %lld\n",i,j,cur);
        LL times=cur/BASE;
        if(times>1||(cur%BASE!=mx[i][j]))continue;
        ++ans;
    }
    printf("%lld",n*m-ans);
    return 0;
}

//以上是维护最值的树状数组
//以下是维护区间和的树状数组

//#include<cstdio>
//#include<cstring>
//#include<algorithm>
//#define MAXN 200050
//using namespace std;
//
//struct interval{
//    int s,t,id;
//}itv[MAXN];
//int n,tot;
//int ansId[MAXN];
//bool cmp(interval a,interval b){
//    if (a.s!=b.s)
//        return a.s<b.s;
//    else
//        return a.t>b.t;
//}
//bool cmp2(interval a,interval b){
//    return a.t<b.t;
//}
//int C[MAXN];
//int lowerbit(int x){
//    return x&(-x);
//}
//int addBit(int pos,int x){
//    for (;pos<=tot;pos+=lowerbit(pos)){
//        C[pos]+=x;
//    }
//    return 1;
//}
//int getSum(int pos){
//    int ans=0;
//    for (;pos>0;pos-=lowerbit(pos)){
//        ans+=C[pos];
//    }
//    return ans;
//}
//void init(){
///////
//    memset(C,0,sizeof(C));
//    memset(ansId,0,sizeof(ansId));
//}
//
//int main(){
//    while(scanf("%d",&n)!=EOF){
//        init();
//        for (int i=1;i<=n;i++){
//            scanf("%d%d",&itv[i].s,&itv[i].t);
//            itv[i].id=i;
//        }
//        sort(itv+1,itv+n+1,cmp2);
//        int pre=-1;
//        tot=0;
//        for (int i=1;i<=n;i++){
//            if (itv[i].t==pre) itv[i].t=tot;
//            else {
//                pre=itv[i].t;
//                itv[i].t=++tot;
//            }
//        }
//        sort(itv+1,itv+n+1,cmp);
//        int lasts=-1,lastt=-1,lastans=-1;
//        for (int i=1;i<=n;i++){
//            if (itv[i].s==lasts && itv[i].t==lastt){
//                ansId[itv[i].id]=lastans;
//                addBit(itv[i].t,1);
//            }
//            else {
//                lasts=itv[i].s;
//                lastt=itv[i].t;
//                lastans=ansId[itv[i].id]=getSum(tot)-getSum(itv[i].t-1);
//                addBit(itv[i].t,1);
//            }
//        }
//        for (int i=1;i<=n;i++){
//            printf("%d ",ansId[i]);
//        }
//        printf("\n");
//    }
//
//    return 0;
//}
