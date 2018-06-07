#include<bits/stdc++.h>
#define rec(i,x) for(int i=0;i<x;i++)
#define MAXN 200005
#define INF 0x3f3f3f3f
#define LL long long
#define ll long long
#define P pair<double,int>
using namespace std;
LL gcd(LL x, LL y)
{
    if (!y) return x;
    return gcd(y, x%y);
}
LL pow(LL a, LL x, LL mod)
{
    LL ans = 1;
    while(x)
    {
        if (x & 1) (ans *= a) %= mod;
        (a *= a) %= mod;
        x >>= 1;
    }
    return ans;
}
bool MRT(LL x)
{
    if (x<=1) return false;
    if (x == 2) return true;
    for (LL i = 1; i <= 30; ++i)
    {
        LL now = rand()%(x-2) + 2;
        if (pow(now, x-1, x) != 1) return false;
    }
    return true;
}
int n,k;
ll a[25];
int ans=0;
void dfs(int x,int lft,ll cur){
    if(x>=n&&lft>0) return;
    if(lft==0){
        if(MRT(cur)){
            ans++;
        }
        return;
    }
    dfs(x+1,lft-1,cur+a[x]);
    dfs(x+1,lft,cur);
    return;
}
int main(){
    cin>>n>>k;
    rec(i,n) cin>>a[i];
    dfs(0,k,0);
    cout<<ans;
    return 0;
}
