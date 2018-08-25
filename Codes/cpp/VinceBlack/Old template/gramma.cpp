#include<cstdio>
#include<algorithm>
#include<cmath>
#define LL long long
#define MAXN 10005
#define INF 0x3f3f3f3f
using namespace std;
struct Point{
    int x,y;
};
Point vx[MAXN];
int xmul(Point p0,Point p1,Point p2){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
int dis2(Point a,Point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool cmp(Point a,Point b){
    int tmp=xmul(vx[0],a,b);
    if(tmp>0) return true;
    else if(tmp==0 && dis2(a,vx[0])<dis2(b,vx[0])) return true;
    else return false;
}
void init(int n){
    int my=INF;
    int mx=INF;
    int k=-1;
    for(int i=0;i<n;i++){
        scanf("%d%d",&vx[i].x,&vx[i].y);
        if(vx[i].y<my || (vx[i].y==my && vx[i].x<mx)){
            my=vx[i].y;
            mx=vx[i].x;
            k=i;
        }
    }
    swap(vx[k],vx[0]);
    sort(vx+1,vx+n,cmp);
}
int stk[MAXN];
int top;
void gramma(int n){
    if(n==1) {
        top=0;
        stk[0]=0;
        return;
    }
    if(n==2) {
        top=1;
        stk[0]=0;
        stk[1]=1;
        return;
    }
    top=1;
    stk[0]=0;
    stk[1]=1;
    for(int i=2;i<n;i++){
        while(top>0&&xmul(vx[stk[top-1]],vx[stk[top]],vx[i])<=0) top--;
        stk[++top]=i;
    }
    return;
}
double vxArea(){
    double ans=0;
    for(int i=1;i<=top-1;i++){
        ans+=(double)(abs(xmul(vx[stk[i+1]],vx[stk[0]],vx[stk[i]])))/2.0;
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d",&n);
    init(n);
    gramma(n);
    double a=vxArea();
    printf("%d\n",(int)(floor(a/50.0)));
    return 0;
}
