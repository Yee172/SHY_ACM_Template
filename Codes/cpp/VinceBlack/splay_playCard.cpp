// luogu-judger-enable-o2
/*
    原题见 P2596 [ZJOI2006]书架
    1． Top S——表示把编号为S的书放在最上面。

    2． Bottom S——表示把编号为S的书放在最下面。

    3． Insert S T——T∈{-1，0，1}，若编号为S的书上面有X本书，则这条命令表示把这本书放回去后它的上面有X+T本书；

    4． Ask S——询问编号为S的书的上面目前有多少本书。

    5． Query S——询问从上面数起的第S本书的编号。
*/
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 0x3f3f3f3f3f3f3f3f
#define LL long long
#define rec(i,x) for(LL i=0;i<x;i++)
#define REC(i,x) for(LL i=1;i<=x;i++)
#define Rec(i,f,t) for(LL i=f;i<=t;i++)
#define P pair<int,int>
#define MIN(x,y) ((x<y)?x:y)
using namespace std;
struct SPLAY{
    #define TreeMAXN 100005
    int tot=0;
    int root=0;
    int pos[TreeMAXN];
    inline void clear(){
        memset(pos,0,sizeof(pos));
        root=tot=0;
    }
    struct Node{
        int f,ch[2],v,cnt,sz;
        Node(){f=cnt=ch[0]=ch[1]=v=sz=0; }
        Node(int F,int CH0,int CH1,int V,int CNT,int SZ,int no)
        :f(F),v(V),cnt(CNT),sz(SZ)
        {
            ch[0]=CH0,ch[1]=CH1;
        }
    }t[TreeMAXN];
    inline void push_up(int x){
        if(x)t[x].sz=t[t[x].ch[0]].sz+t[t[x].ch[1]].sz+t[x].cnt;
    }
    inline void rotate(int x){
        int y=t[x].f,z=t[y].f;
        int k=(t[y].ch[1]==x);
        t[z].ch[t[z].ch[1]==y]=x;   t[x].f=z;
        t[y].ch[k]=t[x].ch[k^1];    t[t[x].ch[k^1]].f=y;
        t[x].ch[k^1]=y;             t[y].f=x;
        push_up(y);
        push_up(x);
    }
    inline void play(int x,int goal){//x rotate to goal's son
        while(t[x].f!=goal){
            int y=t[x].f,z=t[y].f;
            if(z!=goal){
                (t[z].ch[0]==y)^(t[y].ch[0]==x)?rotate(x):rotate(y);
            }
            rotate(x);
        }
        if(goal==0)root=x;
    }
    inline void findv(int v){
        if(!root)return;
        play(pos[v],0);
    }
    inline int getNextV(int op){
        if(!root)return 0;
        int cur=t[root].ch[op];
        if(!cur)return 0;
        while(t[cur].ch[!op]){
            cur=t[cur].ch[!op];
        }
        return t[cur].v;
    }
    inline void connect(int fa,int son,int dir){
        t[fa].ch[dir]=son;
        t[son].f=fa;
    }
    inline void moveTopBottom(int v,int op){
        findv(v);
        if(!t[root].ch[op])return;
        if(!t[root].ch[!op]){
            t[root].ch[!op]=t[root].ch[op];
            t[root].ch[op]=0;
            return;
        }
        int nxt=pos[getNextV(!op)];
        connect(nxt,t[root].ch[op],op);
        t[root].ch[op]=0; //更新sz的时候一定要仔细考虑哪些点sz变了，很可能所有的祖先
        while(nxt){
            push_up(nxt);
            nxt=t[nxt].f;
        }
    }
    inline void insertBack(int v){
        int cur=root;
        if(!cur){
            root=++tot;
            t[tot]=Node(0,0,0,v,1,1,tot);
            pos[v]=tot;
        }
        else{
            ++tot;
            while(t[cur].ch[1])cur=t[cur].ch[1];
            t[tot]=Node(cur,0,0,v,1,1,tot);
            pos[v]=tot;
            t[cur].ch[1]=tot;
        }
        play(tot,0);
    }
    inline void SwapV(int v,int op){//0 for X-1, 1 for X+1
        findv(v);
        int nxt=pos[getNextV(op)];
        swap(pos[t[root].v],pos[t[nxt].v]);
        swap(t[root].v,t[nxt].v);
    }
    inline int AskFrontNumber(int v){
        findv(v);
        int nxt=pos[getNextV(0)];
        if(!nxt)return 0;
        findv(t[nxt].v);
        return t[t[root].ch[0]].sz+t[root].cnt;
    }
    inline int getKthV(int k){
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
            else return t[u].v;
        }
    }
    inline void debug(){
        printf("Debug:\n----------------------------\n");
        printf("Size:%d\n",tot);
        for(int i=0;i<=tot;i++){
            printf("Node%d: f=%d ch0=%d ch1=%d v=%d sz=%d cnt=%d\n",
                   i,t[i].f,t[i].ch[0],t[i].ch[1],t[i].v,t[i].sz,t[i].cnt);
        }
        printf("----------------------------s\n");
    }
}spaly;
char tmps[10];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    rec(i,n){
        int tmp;
        scanf("%d",&tmp);
        spaly.insertBack(tmp);
    }
    rec(i,m){
        scanf("%s",tmps);
        if(tmps[0]=='D'){
            spaly.debug();
        }
        if(tmps[0]=='T'){
            int t1;
            scanf("%d",&t1);
            spaly.moveTopBottom(t1,0);
        }else if(tmps[0]=='B'){
            int t1;
            scanf("%d",&t1);
            spaly.moveTopBottom(t1,1);
        }else if(tmps[0]=='I'){
            int t1,t2;
            scanf("%d%d",&t1,&t2);
            if(t2==0)continue;
            if(t2==-1)t2=0;
            spaly.SwapV(t1,t2);
        }else if(tmps[0]=='A'){
            int t1;
            scanf("%d",&t1);
            printf("%d\n",spaly.AskFrontNumber(t1));
        }else{
            int t1;
            scanf("%d",&t1);
            printf("%d\n",spaly.getKthV(t1));
        }
    }
    return 0;
}
