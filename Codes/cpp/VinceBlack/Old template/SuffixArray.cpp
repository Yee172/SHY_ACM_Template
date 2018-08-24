#include<bits/stdc++.h>
#define LL long long
#define MAXN 1000005
#define TYPE int
#define eps 1e-9
#define INF 0x3f3f3f3f
#define rec(i,x) for(int i=0;i<x;i++)
#define rrec(i,x) for(int i=x-1;i>=0;i--)
#define REC(i,x) for(int i=1;i<=x;i++)
#define RREC(i,x) for(int i=x;i>=1;i--)
#define rd(x) scanf("%d",&x)
#define P pair<int,int>
#define gcd __gcd
using namespace std;
int y[MAXN],x[MAXN],c[MAXN],sa[MAXN],rk[MAXN],height[MAXN];
char s[MAXN];
int n,m;
//sa[i] means the sub of first letter of ith lexicographical largest suffix
//
void get_sa(){ // s[1..n]
    for(int i=1;i<=n;i++) ++c[x[i]=s[i]];
    for(int i=2;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;
        for(int i=1;i<=n;i++)if(sa[i]>k)y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) ++c[x[i]];
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
        x[sa[1]]=1;
        num=1;
        for(int i=2;i<=n;i++){
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
        }
        if(num==n)break;
        m=num;
    }
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
}
int main()
{
    m='z';
    scanf("%s",s+1);
    n=strlen(s+1);
    get_sa();
    for(int i=1;i<=n;i++) printf("%d ",sa[i]);
    return 0;
}
