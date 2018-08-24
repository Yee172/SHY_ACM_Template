#include<bits/stdc++.h>
#define MAXN 1<<20
#define zfj 5
using namespace std;
const double PI = acos(-1.0);
typedef complex<double> cp;

int len;
char S[MAXN],T[MAXN];
cp A[zfj][MAXN],B[zfj][MAXN];
void FFTinit(int l){
    len=1;
    while(len<(l<<1)) len<<=1;
}
void FFT(cp* y,int op){
    for(int i=1,j=len>>1,k;i<len-1;i++){
        if(i<j) swap(y[i],y[j]);
        k = len>>1;
        while(j>=k){
            j-=k;
            k>>=1;
        }
        if(j<k) j+=k;
    }
    for(int h=2;h<=len;h<<=1){
        cp wn=cp(cos(op*2*PI/h),sin(op*2*PI/h));
        for(int i=0;i<len;i+=h){
            cp w=cp(1,0);
            for(int j=i;j<i+h/2;j++){
                cp u=y[j];
                cp t=w*y[j+h/2];
                y[j]=u+t;
                y[j+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(op==-1) for(int i=0;i<len;i++) y[i]=cp(y[i].real()/len,y[i].imag());
}
int inflns[zfj][MAXN];
int match[MAXN];
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s%s",S,T);
    FFTinit(n+m);
    for(int i=0;i<m;i++){
        B[T[i]-'A'][m-i-1]=cp(1,0);
    }
    for(int i=0;i<n;i++){
        int l=max(0,i-k);
        int r=min(n-1,i+k);
        inflns[S[i]-'A'][l]++;
        inflns[S[i]-'A'][r+1]--;
    }
    for(int i=0;i<zfj;i++){
        int cnt=0;
        for(int j=0;j<n;j++){
            cnt+=inflns[i][j];
            if(cnt>0) A[i][j]=cp(1,0);
        }
    }
    for(int i=0;i<zfj;i++){
        FFT(A[i],1); FFT(B[i],1);
        for(int j=0;j<len;j++){
            A[i][j]=A[i][j]*B[i][j];
        }
        FFT(A[i],-1);
        for(int j=0;j<len;j++){
            match[j]+=(int)(A[i][j].real()+0.5);
        }
    }
    int ans=0;
    for(int i=0;i<len;i++){
        if(match[i]==m){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
