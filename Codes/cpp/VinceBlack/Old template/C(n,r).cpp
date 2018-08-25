//#include<bits/stdc++.h>
//#define VI vector<int>
//#define LL long long
//#define MAXN 100005
//#define MOD 998244353
//#define rep(a,b,c) for(int (a)=(b); (a)<(c); (a)++)
//using namespace std;
//
LL fac[MAXN];
void extgcd(LL a,LL b,LL& d,LL& x,LL& y){
    if(!b){ d=a; x=1; y=0;}
    else{ extgcd(b,a%b,d,y,x); y-=x*(a/b); }
}
inline LL powm(LL x,LL y,LL p){LL t=1;for(;y;y>>=1,x=x*x%p)if(y&1)t=t*x%p;return t;}
//inline LL inv(LL x,LL p) {return powm(x,p-2,p);}
LL inv(LL a,LL p){
    LL d,x,y;
    extgcd(a,p,d,x,y);
    return d==1?(x+p)%p:-1;
}
void geneFac(LL x,LL p){fac[0]=1;for(int i=1;i<=x;i++)fac[i]=fac[i-1]*i%p;}
LL C(LL n,LL r,LL p)
{
    if (n < r) return 0;
    if (n == r || r == 0) return 1;
    return (fac[n]*inv[r]%p)*inv[n-r]%p;
}
//
//int main(){
//    int T;
//    geneFac(100000,MOD);
//    scanf("%d",&T);
//    while(T--){
//        LL a,b,n,m;
//        scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
//        printf("%lld\n",C(n-1,m-1,MOD)*powm(a,n-m,MOD)%MOD*powm(b,m-1,MOD)%MOD);
//    }
//    return 0;
//}
