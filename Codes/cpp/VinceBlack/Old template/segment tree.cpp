#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
static const int maxm=1e6+10;
LL tree[maxm],lazy[maxm],A[maxm],left[maxm],right[maxm];
int n,m;

void build(int num,int l,int r){
    left[num]=l;right[num]=r;
    int mid=(l+r)>>1;
    if(l==r){ tree[num]=A[l]; return; }
    build(num<<1,l,mid);
    build(num<<1|1,mid+1,r);
    tree[num]=tree[num<<1]+tree[num<<1|1];
}

void pushdown(int num){
    if(lazy[num]){
        int mid=(left[num]+right[num])>>1;
        tree[num<<1]+=(mid-left[num]+1)*lazy[num];
        tree[num<<1|1]+=(right[num]-mid)*lazy[num];
        lazy[num<<1]+=lazy[num];
        lazy[num<<1|1]+=lazy[num];
        lazy[num]=0;
    }
} //pushdown就是将自身lazy标记压给孩子

void update(int num,int l,int r,LL add){
    if(left[num]>=l&&right[num]<=r){
        tree[num]+=(right[num]-left[num]+1)*add;
        lazy[num]+=add;
        return;
    }
    if(left[num]>r||right[num]<l)return;
    pushdown(num); //update孩子之前需要先曝晒down自身
    update(num<<1,l,r,add);
    update(num<<1|1,l,r,add);
    tree[num]=tree[num<<1]+tree[num<<1|1];  //最后更新一下根节点值
}

LL Query(int num,int l,int r){ //返回[l,r]和num节点的交集和
    if(left[num]>=l&&right[num]<=r)return tree[num];
    if(left[num]>r||right[num]<l) return 0;
    LL ret=0;
    pushdown(num);
    ret+=Query(num<<1,l,r);
    ret+=Query(num<<1|1,l,r);
    return ret;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int f,x,y;LL add;
        scanf("%d",&f);
        switch(f){
            case 1:scanf("%d%d%lld",&x,&y,&add);update(1,x,y,add);break;
            case 2:scanf("%d%d",&x,&y);printf("%lld\n",Query(1,x,y));break;
            default:printf("Orz %%%");break;
        }
    }

    return 0;
}
// Fast Sequence Operations I
// Rujia Liu
// 输入格式：
// n m     数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 L R v 表示设a[L]+=v, a[L+1]+v, ..., a[R]+=v
// 2 L R   查询a[L]~a[R]的sum, min和max
//#include<cstdio>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//
//const int maxnode = 1<<17;
//
//int <span style="color:#ff0000;">_sum</span>, _min, _max, op, qL, qR, v; //<span style="color:#ff0000;">_sum为全局变量</span>
//
//struct IntervalTree {
//  int sumv[maxnode], minv[maxnode], maxv[maxnode], addv[maxnode];
//
//   维护信息
//  void maintain(int o, int L, int R) {
//    int lc = o*2, rc = o*2+1;
//    sumv[o] = minv[o] = maxv[o] = 0;
//    if(R > L) {
//      sumv[o] = sumv[lc] + sumv[rc];
//      minv[o] = min(minv[lc], minv[rc]);
//      maxv[o] = max(maxv[lc], maxv[rc]);
//    }
//    if(addv[o]) { minv[o] += addv[o]; maxv[o] += addv[o]; sumv[o] += addv[o] * (R-L+1); }
//  }
//
//  void update(int o, int L, int R) {
//    int lc = o*2, rc = o*2+1;
//    if(qL <= L && qR >= R) { // 递归边界
//      addv[o] += v; // 累加边界的add值
//    } else {
//      int M = L + (R-L)/2;
//      if(qL <= M) update(lc, L, M);
//      if(qR > M) update(rc, M+1, R);
//    }
//    maintain(o, L, R); // 递归结束前重新计算本结点的附加信息
//  }
//
//  void query(int o, int L, int R, int add) {
//    if(qL <= L && qR >= R) { // 递归边界：用边界区间的附加信息更新答案
//      _sum += sumv[o] + add * (R-L+1);
//      _min = min(_min, minv[o] + add);
//      _max = max(_max, maxv[o] + add);
//    } else { // 递归统计，累加参数add
//      int M = L + (R-L)/2;
//      if(qL <= M) query(o*2, L, M, add + addv[o]);
//      if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
//    }
//  }
//};
//
//const int INF = 1000000000;
//
//IntervalTree tree;
//
//int main() {
//  int n, m;
//  while(scanf("%d%d", &n, &m) == 2) {
//    memset(&tree, 0, sizeof(tree));
//    while(m--) {
//      scanf("%d%d%d", &op, &qL, &qR);
//      if(op == 1) {
//        scanf("%d", &v);
//        tree.update(1, 1, n);
//      } else {
//        _sum = 0; _min = INF; _max = -INF;
//        tree.query(1, 1, n, 0);
//        printf("%d %d %d\n", _sum, _min, _max);
//      }
//    }
//  }
//  return 0;
//}
