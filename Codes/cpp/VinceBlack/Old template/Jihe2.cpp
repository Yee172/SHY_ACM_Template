#include<cmath>
#include<cstdio>
#include<iostream>
using namespace std;

const double eps=1e-8;
const double INF=1e20;
const double PI=acos(-1.0);

int sgn(double a)
{
    if(fabs(a)<eps) return 0;
    return (a<0?-1:1);
}
struct Point
{
    double x,y;
    Point (double _x=0,double _y=0):x(_x),y(_y) {}
    Point (Point a,Point b)
    {
        x=b.x-a.x;
        y=b.y-a.y;
    }
    bool operator <(const Point &b) const  //less is more left, same then more down
    {
        return (sgn(x-b.x)==0?sgn(y-b.y)<0:x<b.x);
    }
    Point operator +(const Point &b) const
    {
        return Point(x+b.x,y+b.y);
    }
    Point operator -(const Point &b) const
    {
        return Point(x-b.x,y-b.y);
    }
    Point operator *(double a)
    {
        return Point(x*a,y*a);
    }
    Point operator /(double a)
    {
        return Point(x/a,y/a);
    }
    double len2()
    {
        return x*x+y*y;
    }
    double len()
    {
        return sqrt(len2());
    }
    Point change_len(double r)
    {
        double l=len();
        if(sgn(l)==0) return *this;
        r/=l;
        return Point(x*r,y*r);
    }
};
double xmul(const Point& a,const Point& b)
{
    return a.x*b.y-a.y*b.x;
}
double dmul(const Point& a,const Point& b)
{
    return a.x*b.x+a.y*b.y;
}
double dis(Point A,Point B)
{
    return Point(A,B).len();
}
struct Line
{
    Point s,e;
    double k;
    Line() {}
    Line(Point _s,Point _e)
    {
        s=_s,e=_e;
        k=atan2(e.y-s.y,e.x-s.x);
    }
    double len()
    {
        return dis(s,e);
    }
};
int PointAtLine(Point p,Line l)
{
    //1. at left, 2. at right, 3. on the line
    int a=sgn(xmul(p-l.s,l.e-l.s));
    if (a<0) return 1;
    if (a>0) return 2;
    else return 3;
}
bool PointAtSegment(Point p,Line l)
{
    return (sgn(xmul(p-l.s,l.e-l.s))==0 && sgn(dmul(p-l.s,p-l.e))<=0);
    // including the endpoints
}
bool PointAtHalfline(Point p,Line l)
{
    if(PointAtLine(p,l)!=3) return 0;
    return sgn(dmul(p-l.s,l.e-l.s))>=0;
}
double DisPointLine(Point p,Line l)
{
    return fabs(xmul(p-l.s,l.e-l.s)/l.len());
}
Point ProjPointOnLine(Point p,Line l)
{
    return (l.s+(l.e-l.s)*(dmul(p-l.s,l.e-l.s)/(l.e-l.s).len2()));
}
Point SymPointToLine(Point p,Line l)
{
    Point q=ProjPointOnLine(p,l);
    return (q*2.0-p);
}

double LineWithLine(Line a,Line b,Point& p)
{
    //<0 insect at p, other distance
    double s1,s2;
    s1=xmul(a.e-a.s,b.s-a.s);
    s2=xmul(a.e-a.s,b.e-a.s);
    if(sgn(s1)==0 && sgn(s2)==0)
        return 0;
    if(sgn(s1-s2)==0) return DisPointLine(a.e,b);
    p=(b.s*s2-b.e*s1)/(s2-s1);
    return -1.0;
}
bool SegmentWithSegment(Line la,Line lb)
{
	Point aa=la.s,bb=la.e,cc=lb.s,dd=lb.e;
    if(max(aa.x,bb.x)<min(cc.x,dd.x))
        return false;
    if(max(aa.y,bb.y)<min(cc.y,dd.y))
        return false;
    if(max(cc.x,dd.x)<min(aa.x,bb.x))
        return false;
    if(max(cc.y,dd.y)<min(aa.y,bb.y))
        return false;
    if(sgn(xmul(cc,bb,aa)*xmul(bb,dd,aa))<=0)  // if two segments must cross strictly with each other, use <=; other <
        return false;
    if(sgn(xmul(aa,dd,cc)*xmul(dd,bb,cc))<=0)
        return false;
   return true;
}

struct Circle
{
    Point p;
    double r;
    Circle() {}
    Circle(Point _p,double _r) :p(_p),r(_r) {}
};
int PointInCircle(Point p,Circle c)
{
    //0:out 1:on 2:in
    double d=dis(p,c.p)-c.r;
    if(sgn(d)<0) return 2;
    return sgn(d)==0;
}
int LineWithCircle(Line l,Circle c)
{
    //0: Deviation 1: tangent 2: intersect
    double p=DisPointLine(c.p,l);
    if(sgn(p-c.r)==0) return 1;
    return (sgn(p-c.r)<0)?2:0;
}
int LineCircleIntersect(Line l,Circle c,Point &p1,Point &p2)
{
    if(!LineWithCircle(l,c)) return 0;
    double d=DisPointLine(c.p,l);
    Point  a=ProjPointOnLine(c.p,l);
    d = sqrt(c.r*c.r-d*d);
    if(sgn(d)==0)
    {
        p1=p2=a;
        return 1;
    }
    p1=a+(l.e-l.s).change_len(d);
    p2=a-(l.e-l.s).change_len(d);
    return 2;
}
int inConvexPoly(Point a,vector<Point>& p,int n)
{
    for(int i = 0;i < n;i++)
    {
        if(sgn((p[i]-a)^(p[(i+1)%n]-a)) < 0)return -1;
        else if(PointAtSegment(a,Line(p[i],p[(i+1)%n])))return 0;
    }
    return 1;
}
int main()
{
    int t;
    cin>>t;
    int cnt=0;
    while(t--)
    {
        cnt++;
        double ox,oy,r,ax,ay,vx,vy,bx,by;
        cin>>ox>>oy>>r>>ax>>ay>>vx>>vy>>bx>>by;
        Point O=Point(ox,oy);
        Circle C=Circle(O,r);
        Point A=Point(ax,ay);
        Point B=Point(bx,by);
        Point V=Point(vx,vy);
        Line L=Line(A,A+V);
        if(sgn(dmul(Point(A,A+V),Point(O,A)))>=0)
        {
            if(PointAtHalfline(B,L))  printf("Case #%d: Yes\n",cnt);
            else printf("Case #%d: No\n",cnt);
            continue;
        }
        Point p1,p2;
        int num=LineCircleIntersect(L,C,p1,p2);
        if(num<2)
        {
            if(PointAtHalfline(B,L))  printf("Case #%d: Yes\n",cnt);
            else printf("Case #%d: No\n",cnt);
            continue;
        }
        Point P;
        P=(Point(p1,A).len()<Point(p2,A).len())?p1:p2;
        if(PointAtSegment(B,Line(A,P)))
        {
            printf("Case #%d: Yes\n",cnt);
            continue;
        }
        Line OP=Line(O,P);
        Point AA=SymPointToLine(A,OP);
        Line PAA=Line(P,AA);
        if(PointAtHalfline(B,PAA))  printf("Case #%d: Yes\n",cnt);
        else printf("Case #%d: No\n",cnt);
    }

    return 0;
}
////////////////
//bool Onsegment(point p1,point p2,point p3)  //快速排斥实验
//{
//    double min_x=min(p1.x,p2.x);
//    double min_y=min(p1.y,p2.y);
//    double max_x=max(p1.x,p2.x);
//    double max_y=max(p1.y,p2.y);
//    if(p3.x>=min_x&&p3.x<=max_x&&p3.y>=min_y&&p3.y<=max_y)
//        return true;
//    return false;
//}
//
//bool Is_intersected(point p1,point p2,point p3,point p4)
//{
//    double d1=x_multi(p1,p2,p3);
//    double d2=x_multi(p1,p2,p4);
//    double d3=x_multi(p3,p4,p1);
//    double d4=x_multi(p3,p4,p2);
//    if(d1*d2<0.0&&d3*d4<0.0)
//        return true;
//    if(d1==0.0&&Onsegment(p1,p2,p3))  //跨立实验
//        return true;
//    if(d2==0.0&&Onsegment(p1,p2,p4))
//        return true;
//    if(d3==0.0&&Onsegment(p3,p4,p1))
//        return true;
//    if(d4==0.0&&Onsegment(p3,p4,p2))
//        return true;
//    return false;
//}
//

struct Square{
    double x1,y1,x2,y2;
};
Square Xsquare (Square A,Square B)
{

    LL x1,x2,y1,y2,xx1,xx2,yy1,yy2,temp;
    x1=A.x1,x2=A.x2;
    y1=A.y1,y2=A.y2;
    xx1=B.x1,xx2=B.x2;
    yy1=B.y1,yy2=B.y2;

    if(x1>x2)
    {
        temp=x1,  x1=x2,   x2=temp;
    }
    if(y1>y2)
    {
        temp=y1,  y1=y2,   y2=temp;
    }
    if(xx1>xx2)
    {
        temp=xx1, xx1=xx2, xx2=temp;
    }
    if(yy1>yy2)
    {
        temp=yy1;
        yy1=yy2, yy2=temp;
    }
    if(x1>xx1)
    {
        temp=x1, x1=xx1, xx1=temp, temp=y1, y1=yy1,  yy1=temp;
        temp=x2, x2=xx2, xx2=temp, temp=y2, y2=yy2,  yy2=temp;
    }
    if( (xx1>=x2)||yy1>=y2 ||y1>yy2 )
    {
        LL tx1=xx1<x1?xx1:x1,tx2=xx2>x2?xx2:x2,ty1=y1<yy1?y1:yy1,ty2=y2>yy2?y2:yy2;
        return Square(0,0,0,0);
    }
    else
    {
        LL tx1=(x1>xx1?x1:xx1),ty1=(y1>yy1?y1:yy1),tx2=(x2<xx2?x2:xx2),ty2=(y2<yy2?y2:yy2),l=tx2-tx1,w=ty2-ty1;
        return Square(tx1,ty1,tx1+l,ty1+w);
    }
}
