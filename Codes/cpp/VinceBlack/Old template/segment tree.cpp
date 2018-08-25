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
} //pushdown���ǽ�����lazy���ѹ������

void update(int num,int l,int r,LL add){
    if(left[num]>=l&&right[num]<=r){
        tree[num]+=(right[num]-left[num]+1)*add;
        lazy[num]+=add;
        return;
    }
    if(left[num]>r||right[num]<l)return;
    pushdown(num); //update����֮ǰ��Ҫ����ɹdown����
    update(num<<1,l,r,add);
    update(num<<1|1,l,r,add);
    tree[num]=tree[num<<1]+tree[num<<1|1];  //������һ�¸��ڵ�ֵ
}

LL Query(int num,int l,int r){ //����[l,r]��num�ڵ�Ľ�����
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
// �����ʽ��
// n m     ���鷶Χ��a[1]~a[n]����ʼ��Ϊ0��������m��
// 1 L R v ��ʾ��a[L]+=v, a[L+1]+v, ..., a[R]+=v
// 2 L R   ��ѯa[L]~a[R]��sum, min��max
//#include<cstdio>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//
//const int maxnode = 1<<17;
//
//int <span style="color:#ff0000;">_sum</span>, _min, _max, op, qL, qR, v; //<span style="color:#ff0000;">_sumΪȫ�ֱ���</span>
//
//struct IntervalTree {
//  int sumv[maxnode], minv[maxnode], maxv[maxnode], addv[maxnode];
//
//   ά����Ϣ
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
//    if(qL <= L && qR >= R) { // �ݹ�߽�
//      addv[o] += v; // �ۼӱ߽��addֵ
//    } else {
//      int M = L + (R-L)/2;
//      if(qL <= M) update(lc, L, M);
//      if(qR > M) update(rc, M+1, R);
//    }
//    maintain(o, L, R); // �ݹ����ǰ���¼��㱾���ĸ�����Ϣ
//  }
//
//  void query(int o, int L, int R, int add) {
//    if(qL <= L && qR >= R) { // �ݹ�߽磺�ñ߽�����ĸ�����Ϣ���´�
//      _sum += sumv[o] + add * (R-L+1);
//      _min = min(_min, minv[o] + add);
//      _max = max(_max, maxv[o] + add);
//    } else { // �ݹ�ͳ�ƣ��ۼӲ���add
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
