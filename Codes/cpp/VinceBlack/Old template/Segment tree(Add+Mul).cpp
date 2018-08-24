#include<cmath>
#include<cstdio>
#include<algorithm>
#include<set>
#include<cstring>
#include<vector>
#define MAXN 100005
#define LL long long
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
using namespace std;
LL MOD;
LL D[MAXN<<2],ADD[MAXN<<2],MUL[MAXN<<2];
void build(int l,int r,int rt);
void add(int L,int R,LL x,int l,int r,int rt);
void mul(int L,int R,LL x,int l,int r,int rt);
void changeto(int L,int R,LL x);
LL getans(int L,int R,int l,int r,int rt);
void pushup(int l,int r,int rt);
void pushdown(int l,int r,int rt);
int n,m;
int main(){
    scanf("%d%lld",&n,&MOD);
    build(1,n,1);
    scanf("%d",&m);
    while(m--){
        int opt;
        scanf("%d",&opt);
        if(opt==1){
            int t1,t2;
            LL t3;
            scanf("%d%d%lld",&t1,&t2,&t3);
            mul(t1,t2,t3,1,n,1);
        }else if(opt==2){
            int t1,t2;
            LL t3;
            scanf("%d%d%lld",&t1,&t2,&t3);
            add(t1,t2,t3,1,n,1);
        }else{
            int t1,t2;
            scanf("%d%d",&t1,&t2);
            printf("%lld\n",getans(t1,t2,1,n,1));
        }
    }
    return 0;
}
void build(int l,int r,int rt){
    ADD[rt]=0;
    MUL[rt]=1;
    if(l==r) {
        scanf("%lld",&D[rt]);
        D[rt]%=MOD;
        return;
    }
    int mid=(l+r)>>1;
    build(lson);build(rson);
    D[rt]=(D[rt<<1]+D[rt<<1|1])%MOD;
}

void add(int L,int R,LL x,int l,int r,int rt){
    if(L<=l && r<=R){
        ADD[rt]=(ADD[rt]+x)%MOD;
        D[rt]=(D[rt]+x*(r-l+1))%MOD;
        return;
    }
    pushdown(l,r,rt);
    int mid=(l+r)>>1;
    if(L<=mid) add(L,R,x,lson);
    if(R>mid)  add(L,R,x,rson);
    pushup(l,r,rt);
}
void mul(int L,int R,LL x,int l,int r,int rt){
    if(L<=l && r<=R){
        MUL[rt]=(MUL[rt]*x)%MOD;
        ADD[rt]=(ADD[rt]*x)%MOD;
        D[rt]=(x*D[rt])%MOD;
        return;
    }
    pushdown(l,r,rt);
    int mid=(l+r)>>1;
    if(L<=mid) mul(L,R,x,lson);
    if(R>mid)  mul(L,R,x,rson);
    pushup(l,r,rt);
}
void changeto(int L,int R,LL x){
    mul(L,R,0,1,n,1);
    add(L,R,x,1,n,1);
}

LL getans(int L,int R,int l,int r,int rt){
    if(L<=l && r<=R){
        return D[rt];
    }
    pushdown(l,r,rt);
    int mid=(l+r)>>1;
    LL ans=0;
    if(L<=mid) ans+=getans(L,R,lson);
    if(R>mid)  ans+=getans(L,R,rson);
    return ans%MOD;
}
void pushdown(int l,int r,int rt){
    int mid=(l+r)>>1;

    if(MUL[rt]!=1){
        ADD[rt<<1]=MUL[rt]*ADD[rt<<1]%MOD;
        ADD[rt<<1|1]=MUL[rt]*ADD[rt<<1|1]%MOD;
        MUL[rt<<1]=MUL[rt<<1]*MUL[rt]%MOD;
        MUL[rt<<1|1]=MUL[rt<<1|1]*MUL[rt]%MOD;
    }
    if(ADD[rt]!=0){
        ADD[rt<<1]=(ADD[rt<<1]+ADD[rt])%MOD;
        ADD[rt<<1|1]=(ADD[rt<<1|1]+ADD[rt])%MOD;
    }
    if(MUL[rt]!=1 || ADD[rt]!=0){
        LL A=ADD[rt],M=MUL[rt],ll=mid-l+1,lr=r-mid;
        D[rt<<1]=(D[rt<<1]*M+A*ll)%MOD;
        D[rt<<1|1]=(D[rt<<1|1]*M+A*lr)%MOD;
        ADD[rt]=0;MUL[rt]=1;
    }
}
void pushup(int l,int r,int rt){
    D[rt]=(D[rt<<1]+D[rt<<1|1])%MOD;
}
