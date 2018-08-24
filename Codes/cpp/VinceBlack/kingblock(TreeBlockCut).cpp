// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 0x3f3f3f3f
#define LL long long
#define rec(i,x) for(int i=0;i<x;i++)
#define REC(i,x) for(int i=1;i<=x;i++)
#define P pair<int,int>
#define MIN(x,y) ((x<y)?x:y)
using namespace std;

namespace fast_io_head{

const int __FREAD_BUFFER_SIZE__ = 1 << 20;
char __BUFFER__[__FREAD_BUFFER_SIZE__], *__P1__=__BUFFER__, *__P2__=__BUFFER__;
#define __IF_END__ (__P1__ == __P2__)
#define __READ_ONE__ (fread(__BUFFER__, 1, __FREAD_BUFFER_SIZE__, stdin))
#define __GET_CHAR__ (__IF_END__ && (__P2__ = (__P1__ = __BUFFER__) + __READ_ONE__, __IF_END__) ? -1 : *__P1__++)
template <typename T>
inline bool read(T &x)
{
    char c;
    bool f = false;
    for (c = __GET_CHAR__; !isdigit(c); c = __GET_CHAR__)
    {
        if (c == EOF) return false;
        if (c == '-') f = true;
    }
    for (x = 0; isdigit(c); c = __GET_CHAR__) x = (x << 1) + (x << 3) + (c ^ 48);
    if (f) x = -x;
    return true;
}

using namespace fast_io_head;

template <typename A, typename B>
inline bool read(A &a, B&b)
{
    return read(a) && read(b);
}

template <typename A, typename B, typename C>
inline bool read(A &a, B &b, C &c)
{
    return read(a) && read(b) && read(c);
}

template <typename A, typename B, typename C, typename D>
inline bool read(A &a, B &b, C &c, D &d)
{
    return read(a) && read(b) && read(c) && read(d);
}

template <typename A, typename B, typename C, typename D, typename E>
inline bool read(A &a, B &b, C &c, D &d, E &e)
{
    return read(a) && read(b) && read(c) && read(d) && read(e);
}

template <typename A, typename B, typename C, typename D, typename E, typename F>
inline bool read(A &a, B &b, C &c, D &d, E &e, F &f)
{
    return read(a) && read(b) && read(c) && read(d) && read(e) && read(f);
}
}

vector<int> E[MAXN];
int province[MAXN],pN=0;
int capital[MAXN];
int stk[MAXN],tp=0;

int N,B;
void KingBlockDfs(int x,int f){
    int p=tp;
    int sz=E[x].size();
    for(int i=0;i<sz;i++){
        int v=E[x][i];
        if(v==f)continue;
        KingBlockDfs(v,x);
        if(tp-p>=B){
            ++pN;
            while(tp>p){
                province[stk[tp-1]]=pN;
                --tp;
            }
            capital[pN]=x;
        }
    }
    stk[tp++]=x;
    return;
}
void KingBlockGao(){
    KingBlockDfs(1,0);
    while(tp>0){
        province[stk[tp-1]]=pN;
        --tp;
    }
}
int main()
{

    scanf("%d%d",&N,&B);
    rec(i,N-1){
        int t1,t2;
        scanf("%d%d",&t1,&t2);
        E[t1].push_back(t2);
        E[t2].push_back(t1);
    }
    KingBlockGao();

    printf("%d\n",pN);
    if(pN==0)return 0;
    REC(i,N){
        if(i>1)putchar(' ');
        printf("%d",province[i]);
    }
    putchar('\n');
    REC(i,pN){
        if(i>1)putchar(' ');
        printf("%d",capital[i]);
    }
    return 0;
}
