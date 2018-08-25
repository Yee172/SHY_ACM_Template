#include<bits/stdc++.h>
#define MAXN 75
using namespace std;

int nxt[MAXN],extend[MAXN];
void getextend(char* s,char *t,int n,int m)
{
    nxt[1]=n;
    int a=0,p=0;
    for(int i=2;i<=n;i++)
    {
        int j=nxt[i-a+1];
        if(i+j>p) for(j=max(0,p-i);i+j<=n && t[i+j]==t[j+1];j++);
        nxt[i]=j;
        if(i+j-1>p) a=i,p=i+j-1;
    }
    a=p=0;
    for(int i=1;i<=n;i++)
    {
        int j=nxt[i-a+1];
        if(i+j>p) for(j=max(0,p-i+1);i+j<=n && s[i+j]==t[j+1];j++);
        extend[i]=j;
        if(i+j-1>p) a=i,p=i+j-1;
    }
}

int main(){

}
