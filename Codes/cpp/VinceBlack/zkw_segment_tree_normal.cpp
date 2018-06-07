//zkw线段树，实现区间加值，区间查询

//模板，摘自SinGuLaRiTy2001博客
#include<cstdio>
#include<algorithm>
using namespace std;
 
#define lson pos << 1
#define rson pos << 1 | 1
#define fa(x) (x >> 1)
const int MAXN = 50000;
int d1[MAXN << 2], d2[MAXN << 2], M = 1, n, m;
// d1 -> max // d2 -> min
 
inline void Read(int &Ret){
    char ch; int flg = 1;
    while(ch = getchar(), ch < '0' || ch > '9')
        if(ch == '-') flg = -1;
    Ret = ch - '0';
    while(ch = getchar(), ch >= '0' && ch <= '9')
        Ret = Ret * 10 + ch - '0';
    Ret *= flg;
}
 
void build(int n){
    while(M < n) M <<= 1;
    int pos = M --;
    while(pos <= M + n){
        Read(d1[pos]);
        d2[pos] = d1[pos];
        pos ++;
    }
    pos = M;
    while(pos){
        d1[pos] = max(d1[lson], d1[rson]);
        d2[pos] = min(d2[lson], d2[rson]);
        d1[lson] -= d1[pos]; d1[rson] -= d1[pos];
        d2[lson] -= d2[pos]; d2[rson] -= d2[pos];
        pos --;
    }
}
 
inline void Insert(int L, int R, int v){//区间更新
    L += M; R += M;
    int A;
    if(L == R){
        d1[L] += v; d2[L] += v;
        while(L > 1){
            A = max(d1[L], d1[L ^ 1]); d1[L] -= A; d1[L ^ 1] -= A; d1[fa(L)] += A;
            A = min(d2[L], d2[L ^ 1]); d2[L] -= A; d2[L ^ 1] -= A; d2[fa(L)] += A;
            L >>= 1;
        }
        return;
    }
    d1[L] += v; d1[R] += v; d2[L] += v; d2[R] += v;
    while(L ^ R ^ 1){
        if(~L & 1) d1[L ^ 1] += v, d2[L ^ 1] += v;
        if(R & 1) d1[R ^ 1] += v, d2[R ^ 1] += v;
        A = max(d1[L], d1[L ^ 1]); d1[L] -= A; d1[L ^ 1] -= A; d1[fa(L)] += A;
        A = max(d1[R], d1[R ^ 1]); d1[R] -= A; d1[R ^ 1] -= A; d1[fa(R)] += A;
        A = min(d2[L], d2[L ^ 1]); d2[L] -= A; d2[L ^ 1] -= A; d2[fa(L)] += A;
        A = min(d2[R], d2[R ^ 1]); d2[R] -= A; d2[R ^ 1] -= A; d2[fa(R)] += A;
        L >>= 1; R >>= 1;
    }
    while(L > 1){
        A = max(d1[L], d1[L ^ 1]); d1[L] -= A; d1[L ^ 1] -= A; d1[fa(L)] += A;
        A = min(d2[L], d2[L ^ 1]); d2[L] -= A; d2[L ^ 1] -= A; d2[fa(L)] += A;
        L >>= 1;
    }
}
 
inline int getans(int L, int R){
    L += M; R += M;
    int ans1 = 0, ans2 = 0;
    if(L == R){
        while(L){
            ans1 += d1[L]; ans2 += d2[L];
            L >>= 1;
        }
        return ans1 - ans2;
    }
    int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
    while(L ^ R ^ 1){
        l1 += d1[L]; r1 += d1[R];
        l2 += d2[L]; r2 += d2[R];
        if(~L & 1) l1 = max(l1, d1[L ^ 1]), l2 = min(l2, d2[L ^ 1]);
        if(R & 1) r1 = max(r1, d1[R ^ 1]), r2 = min(r2, d2[R ^ 1]);
        L >>= 1; R >>= 1;
    }
    l1 += d1[L]; r1 += d1[R]; l2 += d2[L]; r2 += d2[R];
    ans1 = max(l1, r1); ans2 = min(l2, r2);
    while(L > 1){
        L >>= 1;
        ans1 += d1[L]; ans2 += d2[L];
    }
    //printf("max=%d min=%d\n",ans1, ans2);
    return ans1 - ans2;
}
 
int main(){
    int a, b, c;
    char id[3];
    Read(n); Read(m);
    build(n);
    while(m --){
        scanf("%s",id);
        Read(a); Read(b);
        switch(id[0]){
            case 'C': Read(c), Insert(a, b, c); break;
            default: printf("%d\n",getans(a, b));
        }
    }
    return 0;
}