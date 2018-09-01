#include<bits/stdc++.h>
#define LL long long

using namespace std;
#define MAXN 2000005
#define MOD 1000000007
#define N 10
char str[MAXN];
int strl;
LL ten[MAXN];
struct palindromic_tree{
    int nxt[MAXN][N];//nxt[i][c]: add char c at the beginning and the end of string point i, nxt is the sub of the new string
    int fail[MAXN];//fail[i]: the longest true shorter palindrome of string point i, if i fails to be matched, fail[i] will be used.
    int cnt[MAXN];//cnt[i]: the number of unique string that i has.
    int num[MAXN];//num[i]:number of palindrome that end with the last char of point i
    int len[MAXN];  //length of each string point
    int S[MAXN]; //the stored string
    LL Value[MAXN];
    int last,n,p;//  last is the longest palindrome after adding, n is the number of string, p is the number of points of strings
    int newnode(int l){//l: length of new string node
        //for (int i=0;i<N;i++) nxt[p][i]=0;
        cnt[p]=num[p]=0;
        len[p]=l;
        return p++;
    }
    void init(){
        p=0;
        newnode(0);
        newnode(-1);
        last=0;
        n=0;
        S[n]=-1;//-1 means the character that unique to every character in the string
        fail[0]=1;
    }
    int get_fail(int x){
        while((S[n-len[x]-1])!=S[n]){ //can we find a existed string point that have the same char before and behind?
            x=fail[x];  //NO? So go and try shorter one
        } //similar to KMP
        return x; //x is now the point have the same char before and behind(these two char is not included in x!)
    }
    void add(int c){//but c is char you know
        c-='0';
        S[++n]=c;
        int cur=get_fail(last);
        if (!nxt[cur][c]){// it never exist before.
            if(len[cur]+2==2){
                Value[p]=c*10+c;
            }else if(len[cur]+2==1){
                Value[p]=c;
            }else{
                Value[p]=Value[cur]+(ten[len[cur]]*c)%MOD;
                Value[p]%=MOD;
                Value[p]*=10;
                Value[p]%=MOD;
                Value[p]+=c;
                Value[p]%=MOD;
            }
            int now =  newnode(len[cur]+2); //add 2 char before and behind, so...len[cur]+2
            fail[now] = nxt[get_fail(fail[cur])][c];/*pretty hard to understand...we want the true shorter of now,
                                                    so try to look for on fail[cur] and its sons*/
            nxt[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=nxt[cur][c];
        ++cnt[last];
    }
    void makecnt(){// cnt is not right before use makecnt()
        for (int i=p-1;i>=0;--i) {
            cnt[fail[i]]+=cnt[i];
        }
    }
};
palindromic_tree tree;
int main(){
        //palindromic_tree* tree=new palindromic_tree();
    ten[0]=1;
    for(int i=1;i<=MAXN-1;i++) {
        ten[i]=ten[i-1]*10;
        ten[i]%=MOD;
    }
    scanf("%s",str);
    strl=strlen(str);
    tree.init();
    for (int i=0;i<strl;i++){
        tree.add(str[i]);
    }
    tree.makecnt();
    LL ans=0;
    for (int i=2;i<tree.p;i++){
        ans+=tree.Value[i];
        ans%=MOD;
    }
    printf("%lld\n",ans);

    return 0;
}