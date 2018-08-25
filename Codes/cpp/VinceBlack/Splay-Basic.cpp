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

namespace fast_io_head
{
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

struct Mon
{
    int no,a;
    bool operator <(const Mon & ot)const
    {
        return a<ot.a;
    }
};
int n,k;
int v[5];
int a[MAXN][5],b[MAXN][5];
Mon A[5][MAXN];
int p[5];
void __LOCAL_TEST__()
{
    static int __INDEX__ = 0;
    static time_t __START__;
    static time_t __TEMP__;
    static time_t __END__;
    if (__INDEX__)
    {
        __END__ = clock();
        fprintf(stderr,
                "┏TIME CONSUMED BY STAGE %d: %.12f ms\n"
                "┗TOTAL TIME UNTIL STAGE %d: %.12f ms\n",
                __INDEX__,
                (__END__ - __TEMP__) / (double)CLOCKS_PER_SEC * 1000,
                __INDEX__,
                (__END__ - __START__) / (double)CLOCKS_PER_SEC * 1000);
        __TEMP__ = __END__;
        __INDEX__++;
    }
    else
    {
        freopen("in.txt","r",stdin);
        __START__ = __TEMP__ = clock();
        __INDEX__++;
    }
}
}

struct SPLAY{
    #define TreeMAXN 100005
    int tot=0;
    int root=0;
    struct Node{
        int f,ch[2],v,cnt,sz;
        Node(){f=cnt=ch[0]=ch[1]=v=sz=0;}
    }t[TreeMAXN];
    void push_up(int x){
        t[x].sz=t[t[x].ch[0]].sz+t[t[x].ch[1]].sz+t[x].cnt;
    }
    void rotate(int x){
        int y=t[x].f,z=t[y].f;
        int k=(t[y].ch[1]==x);
        t[z].ch[t[z].ch[1]==y]=x;   t[x].f=z;
        t[y].ch[k]=t[x].ch[k^1];    t[t[x].ch[k^1]].f=y;
        t[x].ch[k^1]=y;             t[y].f=x;
        push_up(y);
        push_up(x);
    }
    void play(int x,int goal){//x rotate to goal's son
        while(t[x].f!=goal){
            int y=t[x].f,z=t[y].f;
            if(z!=goal){
                (t[z].ch[0]==y)^(t[y].ch[0]==x)?rotate(x):rotate(y);
            }
            rotate(x);
        }
        if(goal==0)root=x;
    }
    inline void find(int x){//rotate value x node to root
        int u=root;
        if(!u)return;
        while(t[u].ch[x>t[u].v]&&x!=t[u].v){
            u=t[u].ch[x>t[u].v];
        }
        play(u,0);
    }
    inline void insert(int x){
        int u=root,f=0;
        while(u&&t[u].v!=x){
            f=u;
            u=t[u].ch[x>t[u].v];
        }
        if(u){
            ++t[u].cnt;
        }else{
            u=++tot;
            if(f){
                t[f].ch[x>t[f].v]=u;
            }
            t[u].ch[0]=t[u].ch[1]=0;
            t[u].f=f;
            t[u].v=x;
            t[u].cnt=t[u].sz=1;
        }
        play(u,0);
    }
    inline int getNext(int x,int op){//value x, op?Back:front, return node number;
        find(x);
        int u=root;
        if((t[u].v>x&&op)||(t[u].v<x&&!op))return u;
        u=t[u].ch[op];
        while(t[u].ch[op^1]){
            u=t[u].ch[op^1];
        }
        return u;
    }
    inline void Delete(int x){//value x

        int pre=getNext(x,0);
        int nxt=getNext(x,1);
        play(pre,0);
        play(nxt,pre);
        int del=t[nxt].ch[0];
        if(t[del].cnt>1){
            t[del].cnt--;
            play(del,0);
        }
        else{
            t[nxt].ch[0]=0;
        }
    }
    int getKth(int k){
        int u=root;
        if(t[u].sz<k){
            return -1;
        }
        while(1){
            int y=t[u].ch[0];
            if(k>t[y].sz+t[u].cnt){
                k-=t[y].sz+t[u].cnt;
                u=t[u].ch[1];
            }
            else if(t[y].sz>=k){
                u=y;
            }
            else return u;
        }
    }
}spaly;
int main()
{
    spaly.insert(-2147483647);
    spaly.insert(2147483647);
    int n;
    scanf("%d",&n);
    rec(i,n){

    }
    return 0;
}
