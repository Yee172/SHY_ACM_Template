//poj 3805 判断凸包是否相交，nlogn复杂度
//直接copy，未整合
//只要有一个点重合就算交，包含也算
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point
{
    double x,y;
    Point (double x=0, double y=0) :x(x),y(y) {}
    void show() { cout<<"("<<x<<","<<y<<")"<<endl; }
};
typedef Point Vector;

bool operator < (const Point& A, const Point& B )
{
    return A.x < B.x || (A.x == B.x && A.y < B.y);
}
Vector operator - ( Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
double Cross(Vector A, Vector B) { return A.x*B.y - B.x*A.y; }

const double eps = 1e-10;
int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    return x>0? 1: -1;
}

int ConvexHull ( Point* p, int n, Point* ch)
{
    sort(p, p+n);
    int m = 0;
    for(int i = 0; i<n; i++)
    {
        while(m > 1 && Cross( ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i>=0; i--)
    {
        while(m > k && Cross( ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    ///还要改一下生成多边形。
    ch[m++] = ch[0];
    if(n > 1) m--;
    return m;
}

Point black[120],white[120],cw[120],cb[120];
int nb,nw,n,m;

void reset()
{
    memset(black,0,sizeof(black));
    memset(white,0,sizeof(white));
    memset(cw,0,sizeof(cw));
    memset(cb,0,sizeof(cb));
}

bool SideCross(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
           c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool pInConvex(Point a, Point* ch, int n)
{
    int i;
    if(n==3)
    {
        if(a.x < min(ch[0].x, ch[1].x) || a.x > max(ch[0].x, ch[1].x)) return 0;
        if(a.y < min(ch[0].y, ch[1].y) || a.y > max(ch[0].y, ch[1].y)) return 0;
    }
    for(i=1;i<n;i++)
    {
        if(Cross( ch[i]-ch[i-1], a-ch[i-1] ) < 0 ) return 0;
    }
    return 1;
}

int solve()
{
    int i,j;
    if(n==1&&m==1) return 1;
    else if(n==1)
    {
        ///找白子凸包多边形。判断这个黑子是否在白包内
        nw=ConvexHull(white, m, cw);
        if(pInConvex(black[0], cw, nw)) return 0;
    }
    else if(m==1)
    {
        ///找黑子凸包多边形。判断这个白子是否在黑包内
        nb=ConvexHull(black, n, cb);
        if(pInConvex(white[0], cb, nb)) return 0;
    }
    else
    {
        ///找黑白凸包多边形。判断是否有线段相交或点在另一个凸包内。
        nb=ConvexHull(black, n, cb);
        nw=ConvexHull(white, m, cw);
        for(i=1;i<nb;i++)
        {
            for(j=1;j<nw;j++)
                if(SideCross( cb[i], cb[i-1], cw[j] ,cw[j-1] )) return 0;
        }
        for(i=0;i<n;i++)
            if(pInConvex(black[i], cw, nw)) return 0;
        for(i=0;i<m;i++)
            if(pInConvex(white[i], cb, nb)) return 0;
    }
    return 1;
}

int main()
{
    int i,tx,ty;
    n=m=4;
    reset();
    for(i=0;i<n;i++)
    {
        cin>>tx>>ty;
        black[i]=Point(tx,ty);
    }
    for(i=0;i<m;i++)
    {
        cin>>tx>>ty;
        white[i]=Point(tx,ty);
    }
    int ans=solve();
    if(ans)
        cout<<"NO"<<endl;
    else
        cout<<"YES"<<endl;

    return 0;
}
