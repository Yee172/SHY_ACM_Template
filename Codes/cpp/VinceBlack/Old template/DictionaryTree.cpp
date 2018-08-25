#include<bits/stdc++.h>
#define MAXN 4000005
#define MOD 20071027
#define LL long long
using namespace std;

int nxt[MAXN];
int N,head=0;
char wd[4001][1002];
struct Node{
    char c;
    int fst;
    int cnt;
}node[MAXN];
int tot;

void init(){
    node[head].cnt=0;
    node[head].fst=-1;
    tot=1;
    memset(nxt,-1,sizeof(nxt));
}
void update(int k){
    int sz=strlen(wd[k]);
    int cur=head;
    for(int i=0;i<sz;i++){
        int ok=-1;
        char ch=wd[k][i];
        for(int i=node[cur].fst;i!=-1;i=nxt[i]){
            if(node[i].c==ch){
                ok=i;
                break;
            }
        }
        if(ok<0){
            node[tot].c=ch;
            node[tot].cnt=0;
            node[tot].fst=-1;
            nxt[tot]=node[cur].fst;
            node[cur].fst=tot;
            ok=tot;
            tot++;
        }
        cur=ok;
        node[cur].cnt++;
    }
}
LL gogo(int k){
    LL cst=0;
    int sz=strlen(wd[k]);
    int cur=head;
    int f=N;
    for(int i=0;i<sz;i++)
    {
        int ok=-1;
        char ch=wd[k][i];
        for(int i=node[cur].fst;i!=-1;i=nxt[i]){
            if(node[i].c==ch){
                ok=i;
                break;
            }
        }
        cur=ok;
        cst+=(f-node[cur].cnt)+(node[cur].cnt-1)*2;
        f=node[cur].cnt;
    }
    int lst=0;
    for(int i=node[cur].fst;i!=-1;i=nxt[i]){
        lst+=node[i].cnt;
    }
    cst+=lst;
    cst+=(node[cur].cnt-lst-1)*2;
    return cst;
}

int main(){
    int cnt=0;
    while(1){

        scanf("%d",&N);
        if(N==0) break;
        for(int i=0;i<N;i++) scanf("%s",wd[i]);
        init();
        LL ans=0;
        for(int i=0;i<N;i++) update(i);
        for(int i=0;i<N;i++) ans+=gogo(i);
        printf("Case %d: %lld\n",++cnt,ans/2);
    }
    return 0;
}