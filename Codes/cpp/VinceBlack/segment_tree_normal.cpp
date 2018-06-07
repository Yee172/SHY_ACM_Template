//线段树 区间增加/区间改值


//模板如下
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 200005
#define INF 0x3f3f3f3f
#define LL long long
#define P pair<double,int>
using namespace std;
struct Node{
    int l,r; //区间[l,r]
    int add; //区间加法
    int tobe; //区间改值成
    bool readyTobe; //准备开始进行区间改值
    int sm;
    int mx;
    int mn;
}seg[MAXN<<2];
void push_up(int x){ //更新父节点操作，应该在递归完子节点之后使用
    seg[x].sm=seg[x<<1].sm+seg[x<<1|1].sm;
    seg[x].mx=max(seg[x<<1].mx,seg[x<<1|1].mx);
    seg[x].mn=min(seg[x<<1].mn,seg[x<<1|1].mn);
}
void push_down(int x){
    if(seg[x].add){
        seg[x<<1].sm+=(seg[x<<1].r-seg[x<<1].l+1)*seg[x].add;
        seg[x<<1].mx+=seg[x].add;
        seg[x<<1].mn+=seg[x].add;
		seg[x<<1].add+=seg[x].add;
        seg[x<<1|1].sm+=(seg[x<<1|1].r-seg[x<<1|1].l+1)*seg[x].add;
        seg[x<<1|1].mx+=seg[x].add;
        seg[x<<1|1].mn+=seg[x].add;
		seg[x<<1|1].add+=seg[x].add;
        seg[x].add=0;
    }
    if(seg[x].readyTobe){
        seg[x<<1].sm=(seg[x<<1].r-seg[x<<1].l+1)*seg[x].tobe;
        seg[x<<1].mx=seg[x].tobe;
        seg[x<<1].mn=seg[x].tobe;
		seg[x<<1].readyTobe=1;
		seg[x<<1].tobe=seg[x].tobe;
        seg[x<<1|1].sm=(seg[x<<1|1].r-seg[x<<1|1].l+1)*seg[x].tobe;
        seg[x<<1|1].mx=seg[x].tobe;
        seg[x<<1|1].mn=seg[x].tobe;
		seg[x<<1|1].readyTobe=1;
		seg[x<<1|1].tobe=seg[x].tobe;
        seg[x].readyTobe=0;
    }
}
void build(int l,int r,int x){
    seg[x].l=l;
    seg[x].r=r;
    seg[x].add=0; seg[x].readyTobe=0;
    if(l==r){
        scanf("%d",&seg[x].sm); //
        seg[x].mn=seg[x].mx=seg[x].sm;
        return;
    }
    seg[x].sm=0; seg[x].mx=-INF; seg[x].mn=INF;
    int mid=(l+r)>>1;
    build(l,mid,x<<1);
    build(mid+1,r,x<<1|1);
    push_up(x);
}
void update(int L,int R,int x,int val,int changeOrAdd){
    if(L<=seg[x].l && R>=seg[x].r){
        if(changeOrAdd){
            seg[x].readyTobe=1;
            seg[x].tobe=val;
            seg[x].sm=(seg[x].r-seg[x].l+1)*val;
            seg[x].mn=seg[x].mx=val;
        }
        else{
            seg[x].add=val;
            seg[x].sm+=(seg[x].r-seg[x].l+1)*val;
            seg[x].mx+=val;
            seg[x].mn+=val;
        }
        return;
    }
    push_down(x);
    int mid=(seg[x].l+seg[x].r)>>1;
    if(L<=mid) update(L,R,x<<1,val,changeOrAdd);
    if(R>=mid+1) update(L,R,x<<1|1,val,changeOrAdd);
    push_up(x);
}
void query(int L,int R,int x,int& Sm,int& Mx,int& Mn){
    if(L<=seg[x].l && R>=seg[x].r){
        Sm = seg[x].sm;
        Mx = seg[x].mx;
        Mn = seg[x].mn;
        return;
    }
    push_down(x);
    int mid=(seg[x].l+seg[x].r)>>1;
    int ansSm=0;
    int ansMx=-INF;
    int ansMn=INF;
    if(L<=mid){
        int tmp1,tmp2,tmp3;
        query(L,R,x<<1,tmp1,tmp2,tmp3);
        ansSm+=tmp1;
        ansMx=max(ansMx,tmp2);
        ansMn=min(ansMn,tmp3);
    }
    if(R>=mid+1){
        int tmp1,tmp2,tmp3;
        query(L,R,x<<1|1,tmp1,tmp2,tmp3);
        ansSm+=tmp1;
        ansMx=max(ansMx,tmp2);
        ansMn=min(ansMn,tmp3);
    }
    Sm=ansSm;
    Mx=ansMx;
    Mn=ansMn;
    return;
}

char str[20];
int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
        int q;
        scanf("%d",&q);
        build(1,n,1);
        while(q--){
            int a,b;
            scanf("%s",str);
            scanf("%d%d",&a,&b);
            if(str[0]=='U'){
                update(a,a,1,b,1);
            }
            else if(str[0]=='Q'){
                int ans=0;int tmp1,tmp2;
                query(a,b,1,ans,tmp1,tmp2);
                printf("%d\n",tmp1);
            }
        }
    }
    return 0;
}
