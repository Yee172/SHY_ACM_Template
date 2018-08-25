// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define LL long long
#define MAXN 100005
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
inline char gc() { static char buf[1<<20],*h=buf,*t=buf;return (h==t&&(t=(h=buf)+fread(buf,1,1<<20,stdin),h==t)?-1:*h++);}
template <typename T> inline bool read(T &x){static int f;static char c;for(c=gc(),f=1;!isdigit(c);c=gc()){if(c==-1)return false;else if(c==45)f=-1;}for(x=c-48;isdigit(c=gc());x=x*10+c-48);return x*=f,true; }
template <typename A, typename B> inline bool read(A&x, B&y) {return read(x) && read(y);}
template <typename A, typename B, typename C> inline bool read(A&x,B&y,C&z){return read(x)&&read(y)&&read(z);}
inline LL pow(LL x,LL y,LL p){LL t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}

struct Squeue{
    int A[MAXN],MX[MAXN],MN[MAXN];
    int tp;
    int mxp,mnp;
    void init(){
        tp=0;
        mxp=mnp=-1;
        memset(A,0,sizeof(A));
        memset(MX,0,sizeof(MX));
        memset(MN,0,sizeof(MN));
    }
    void push(int x){
        if(!tp){
            A[tp++]=x;
            MX[0]=MN[0]=-1;
            mxp=mnp=0;
        }else{
            A[tp]=x;
            if(x>A[mxp]){
                MX[tp]=mxp;
                mxp=tp;
            }else{
                MX[tp]=-1;
            }
            if(x<A[mnp]){
                MN[tp]=mnp;
                mnp=tp;
            }else{
                MN[tp]=-1;
            }
            ++tp;
        }
    }
    bool empty(){
        return (tp==0);
    }
    int size(){
        return tp;
    }
    int get_mx(){
        if(empty())return -INF;
        return A[mxp];
    }
    int get_mn(){
        if(empty())return INF;
        return A[mnp];
    }
    int pop(){
        int ans=A[tp-1];
        if(tp-1==mxp){
            mxp=MX[tp-1];
        }
        if(tp-1==mnp){
            mnp=MN[tp-1];
        }
        --tp;
        return ans;
    }
};
Squeue s1,s2;
struct Water{
    int x,y;
    bool operator <(const Water & b) const{
        return x<b.x;
    }
}D[MAXN];
int N,DIS;
bool check(int len){
    int lft=1;
    s1.init();
    s2.init();
    for(int i=1;i<=N;i++){
        s2.push(D[i].y);
        while(D[i].x-len>D[lft].x){
            if(s1.empty()){
                while(!s2.empty()){
                    s1.push(s2.pop());
                }
            }
            s1.pop();
            ++lft;
        }
        if(max(s1.get_mx(),s2.get_mx())-min(s1.get_mn(),s2.get_mn())>=DIS){
            return true;
        }
    }
    return false;
}
int main(){
    scanf("%d%d",&N,&DIS);
    int mxx=-INF,mnx=INF;
    for(int i=1;i<=N;i++){
        scanf("%d%d",&D[i].x,&D[i].y);
        mnx=min(mnx,D[i].x);
        mxx=max(mxx,D[i].x);
    }
    sort(D+1,D+N+1);
    int l=2,r=mxx-mnx+1;
    while(l<r){
        int mid=l+r>>1;
        if(check(mid)){
            r=mid;
        }
        else{
            l=mid+1;
        }
    }
    if(check(l)){
        printf("%d",l);
    }
    else{
        printf("-1");
    }
    return 0;
}
