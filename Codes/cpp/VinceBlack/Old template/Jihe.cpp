#include <bits/stdc++.h>  
using namespace std;  
  
struct Point {  
    double x, y;  
    Point(double x = 0, double y = 0) : x(x), y(y) {}  
};  
  
typedef Point Vector;  
  
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }  
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }  
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.x*p); }  
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.x/p); }  
  
bool operator < (const Point& a, const Point b) {  
    return a.x < b.x || (a.x == b.x && a.y < b.y);  
}  
  
const double EPS = 1e-10;  
  
int dcmp(double x) {  
    if(fabs(x) < EPS) return 0;  
    else return x < 0 ? -1 : 1;  
}  
  
bool operator == (const Point& a, const Point& b) {  
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y);  
}  
  
//����a�ļ���  
double Angle(const Vector& v) {  
    return atan2(v.y, v.x);\share\CodeBlocks\templates\wizard\console\cpp  
}  
  
//�������  
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }  
  
//��������\share\CodeBlocks\templates\wizard\console\cpp  
double Length(Vector A) { return sqrt(Dot(A, A)); }  
  
//�����н�  
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }  
  
//�������  
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }  
  
//��������������Ķ���  
double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }  
  
//������ʱ����תrad��(����)  
Vector Rotate(Vector A, double rad) {  
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));  
}  
  
//��������A�ĵ�λ����������ת90�㣬�ѳ��ȹ�һ������ǰȷ��A������������  
Vector Normal(Vector A) {  
    double L = Length(A);  
    return Vector(-A.y/L, A.x/L);  
}  
  
/************************************************************************ 
ʹ�ø�����ʵ�ֵ㼰�����ļ򵥲��� 
 
#include <complex> 
typedef complex<double> Point; 
typedef Point Vector; 
 
double Dot(Vector A, Vector B) { return real(conj(A)*B)} 
double Cross(Vector A, Vector B) { return imag(conj(A)*B);} 
Vector Rotate(Vector A, double rad) { return A*exp(Point(0, rad)); } 
 
*************************************************************************/  
  
/**************************************************************************** 
* ��ֱ���ϵ�һ��p0�ͷ�������v��ʾһ��ָ��ֱ���ϵ����е�P����P = P0+t*v; 
* ���֪��ֱ���ϵ���������������ΪB-A, ���Բ�������ΪA+(B-A)*t; 
* ��t ������ʱ�� �ò������̱�ʾֱ�ߡ� 
* ��t > 0ʱ�� �ò������̱�ʾ���ߡ� 
* �� 0 < t < 1ʱ�� �ò������̱�ʾ�߶Ρ� 
*****************************************************************************/  
  
//ֱ�߽���,��ȷ����ֱ����Ψһ���㡣  
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {  
    Vector u = P - Q;  
    double t = Cross(w, u)/Cross(v, w);  
    return P+v*t;  
}  
  
//�㵽ֱ�߾���  
double DistanceToLine(Point P, Point A, Point B) {  
    Vector v1 = B - A, v2 = P - A;  
    return fabs(Cross(v1, v2) / Length(v1)); //��ȡ����ֵ���õ������������  
}  
  
//�㵽�߶εľ���  
double DistanceToSegmentS(Point P, Point A, Point B) {  
    if(A == B) return Length(P-A);  
    Vector v1 = B-A, v2 = P-A, v3 = P-B;  
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);  
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);  
    else return fabs(Cross(v1, v2)) / Length(v1);  
}  
  
//����ֱ���ϵ�ͶӰ  
Point GetLineProjection(Point P, Point A, Point B) {  
    Vector v = B - A;  
    return A+v*(Dot(v, P-A)/Dot(v, v));  
}  
  
//�߶��ཻ�ж������㲻��һ���߶εĶ˵�  
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {  
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);  
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);  
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;  
}  
  
//�жϵ��Ƿ��ڵ���ϣ��������˵�  
bool OnSegment(Point P, Point a1, Point a2) {  
    return dcmp(Cross(a1-P, a2-P) == 0 && dcmp((Dot(a1-P, a2-P)) < 0));  
}  
  
//����͹��������  
double ConvexPolygonArea(Point *p, int n) {  
    double area = 0;  
    for(int i = 1; i < n-1; i++)  
        area += Cross(p[i] - p[0], p[i+1] - p[0]);  
    return area/2;  
}  
  
//�������ε��������  
double PolygonArea(Point *p, int n) {  
    double area = 0;  
    for(int i = 1; i < n-1; i++)  
        area += Cross(p[i] - p[0], p[i+1] - p[0]);  
    return area/2;  
}  
  
/*********************************************************************** 
* Morley����������ÿ���ڽǵ����ȷ��ߣ��ཻ�ɵ��������ǵȱ������Ρ� 
* ŷ��������ƽ��ͼ�Ķ������������������ֱ�ΪV,E,F����V+F-E = 2; 
************************************************************************/  
  
struct Circle {  
    Point c;  
    double r;  
  
    Circle(Point c, double r) : c(c), r(r) {}  
    //ͨ��Բ�Ľ�ȷ��Բ������  
    Point point(double a) {  
        return Point(c.x + cos(a)*r, c.y + sin(a)*r);  
    }  
};  
  
struct Line {  
    Point p;  
    Vector v;  
    double ang;  
    Line() {}  
    Line(Point p, Vector v) : p(p), v(v) {}  
    bool operator < (const Line& L) const {  
        return ang < L.ang;  
    }  
};  
  
//ֱ�ߺ�Բ�Ľ��㣬���ؽ���������������sol�С�  
//�ô���û�����sol��  
int getLineCircleIntersecion(Line L, Circle C, double& t1, double& t2, vector<Point>& sol) {  
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;  
    double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;  
    double delta = f*f - 4*e*g;  
    if(dcmp(delta) < 0) return 0; //����  
    if(dcmp(delta) == 0) {        //����  
        t1 = t2 = -f / (2*e);  
        sol.push_back(C.point(t1));  
        return 1;  
    }  
    //�ཻ  
    t1 = (-f - sqrt(delta)) / (2*e); sol.push_back(C.point(t1));  
    t2 = (-f + sqrt(delta)) / (2*e); sol.push_back(C.point(t2));  
    return 2;  
}  
  
//��Բ�ཻ  
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {  
    double d = Length(C1.c - C2.c);  
    if(dcmp(d) == 0) {  
        if(dcmp(C1.r - C2.r == 0)) return -1;    //��Բ��ȫ�غ�  
        return 0;                                //ͬ��Բ���뾶��һ��  
    }  
    if(dcmp(C1.r + C2.r - d) < 0) return 0;  
    if(dcmp(fabs(C1.r - C2.r) == 0)) return -1;  
  
    double a = Angle(C2.c - C1.c);               //����C1C2�ļ���  
    double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));  
    //C1C2��C1P1�Ľ�  
    Point p1 = C1.point(a-da), p2 = C1.point(a+da);  
    sol.push_back(p1);  
    if(p1 == p2) return 1;  
    sol.push_back(p2);  
    return 2;  
}  
  
const double PI = acos(-1);  
//��������Բ������  
//����p��ԲC�����ߣ��������߸�����v[i]��ʾ��i������  
int getTangents(Point p, Circle C, Vector* v) {  
    Vector u = C.c - p;  
    double dist = Length(u);  
    if(dist < C.r) return 0;  
    else if(dcmp(dist - C.r) == 0) {  
        v[0] = Rotate(u, PI/2);  
        return 1;  
    } else {  
        double ang = asin(C.r / dist);  
        v[0] = Rotate(u, -ang);  
        v[1] = Rotate(u, +ang);  
        return 2;  
    }  
}  
  
//��Բ�Ĺ�����  
//�������ߵĸ�����-1��ʾ�������������ߡ�  
//a[i], b[i] ��ʾ��i��������ԲA��ԲB�ϵ��е�  
int getTangents(Circle A, Circle B, Point *a, Point *b) {  
    int cnt = 0;  
    if(A.r < B.r) {  
        swap(A, B); swap(a, b);  
    }  
    int d2 = (A.c.x - B.c.x)*(A.c.x - B.c.x) + (A.c.y - B.c.y)*(A.c.y - B.c.y);  
    int rdiff = A.r - B.r;  
    int rsum = A.r + B.r;  
    if(d2 < rdiff*rdiff) return 0;   //�ں�  
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);  
    if(d2 == 0 && A.r == B.r) return -1;   //���޶�������  
    if(d2 == rdiff*rdiff) {         //����һ������  
        a[cnt] = A.point(base);  
        b[cnt] = B.point(base);  
        cnt++;  
        return 1;  
    }  
    //���⹲����  
    double ang = acos((A.r-B.r) / sqrt(d2));  
    a[cnt] = A.point(base+ang); b[cnt] = B.point(base+ang); cnt++;  
    a[cnt] = A.point(base-ang); b[cnt] = B.point(base-ang); cnt++;  
    if(d2 == rsum*rsum) {  //һ��������  
        a[cnt] = A.point(base);  
        b[cnt] = B.point(PI+base);  
        cnt++;  
    } else if(d2 > rsum*rsum) {   //����������  
        double ang = acos((A.r + B.r) / sqrt(d2));  
        a[cnt] = A.point(base+ang); b[cnt] = B.point(PI+base+ang); cnt++;  
        a[cnt] = A.point(base-ang); b[cnt] = B.point(PI+base-ang); cnt++;  
    }  
    return cnt;  
}  
  
typedef vector<Point> Polygon;  
  
//���ڶ�����ڵ��ж�  
int isPointInPolygon(Point p, Polygon poly) {  
    int wn = 0;  
    int n = poly.size();  
    for(int i = 0; i < n; i++) {  
        if(OnSegment(p, poly[i], poly[(i+1)%n])) return -1; //�ڱ߽���  
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));  
        int d1 = dcmp(poly[i].y - p.y);  
        int d2 = dcmp(poly[(i+1)%n].y - p.y);  
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;  
        if(k < 0 && d2 <= 0 && d1 > 0) wn++;  
    }  
    if(wn != 0) return 1;       //�ڲ�  
    return 0;                   //�ⲿ  
}  
  
//͹��  
/*************************************************************** 
* ���������p�� ����Ϊp�� ���������ch�� ����͹�������� 
* ��ϣ��͹���ı���������㣬������<= �ĳ� < 
* �߾���Ҫ��ʱ������dcmp�Ƚ� 
* ����㲻�����ظ��㡣����ִ�����Ժ�������˳���ƻ� 
****************************************************************/  
int ConvexHull(Point *p, int n, Point* ch) {  
    sort(p, p+n);      //�ȱȽ�x���꣬�ٱȽ�y����  
    int m = 0;  
    for(int i = 0; i < n; i++) {  
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i]-ch[m-2]) <= 0) m--;  
        ch[m++] = p[i];  
    }  
    int k = m;  
    for(int i = n-2; i >= 0; i++) {  
        while(m > k && Cross(ch[m-1] - ch[m-2], p[i]-ch[m-2]) <= 0) m--;  
        ch[m++] = p[i];  
    }  
    if(n > 1) m--;  
    return m;  
}  
  
//������ֱ��A->B�и�����poly�� ���ء���ࡱ�� ����˻������ܻ᷵��һ����������߶�  
//���Ӷ�O(n2);  
Polygon CutPolygon(Polygon poly, Point A, Point B) {  
    Polygon newpoly;  
    int n = poly.size();  
    for(int i = 0; i < n; i++) {  
        Point C = poly[i];  
        Point D = poly[(i+1)%n];  
        if(dcmp(Cross(B-A, C-A)) >= 0) newpoly.push_back(C);  
        if(dcmp(Cross(B-A, C-D)) != 0) {  
            Point ip = GetLineIntersection(A, B-A, C, D-C);  
            if(OnSegment(ip, C, D)) newpoly.push_back(ip);  
        }  
    }  
    return newpoly;  
}  
  
//��ƽ�潻  
  
//��p������ֱ��L����ߡ������ϲ��㣩  
bool Onleft(Line L, Point p) {  
    return Cross(L.v, p-L.p) > 0;  
}  
  
//��ֱ�߽��㣬�ٶ�����Ψһ����  
Point GetIntersection(Line a, Line b) {  
    Vector u = a.p - b.p;  
    double t = Cross(b.v, u) / Cross(a.v, b.v);  
    return a.p+a.v*t;  
}  
  
int HalfplaneIntersection(Line* L, int n, Point* poly) {  
    sort(L, L+n);               //����������  
  
    int first, last;            //˫�˶��еĵ�һ��Ԫ�غ����һ��Ԫ��  
    Point *p = new Point[n];    //p[i]Ϊq[i]��q[i+1]�Ľ���  
    Line *q = new Line[n];      //˫�˶���  
    q[first = last = 0] = L[0]; //���г�ʼ��Ϊֻ��һ����ƽ��L[0]  
    for(int i = 0; i < n; i++) {  
        while(first < last && !Onleft(L[i], p[last-1])) last--;  
        while(first < last && !Onleft(L[i], p[first])) first++;  
        q[++last] = L[i];  
        if(fabs(Cross(q[last].v, q[last-1].v)) < EPS) {  
            last--;  
            if(Onleft(q[last], L[i].p)) q[last] = L[i];  
        }  
        if(first < last) p[last-1] = GetIntersection(q[last-1], q[last]);  
    }  
    while(first < last && !Onleft(q[first], p[last-1])) last--;  
    //ɾ������ƽ��  
    if(last-first <= 1) return 0;   //�ռ�  
    p[last] = GetIntersection(q[last], q[first]);  
  
    //��deque���Ƶ������  
    int m = 0;  
    for(int i = first; i <= last; i++) poly[m++] = p[i];  
    return m;  
}  
int main() {  
  
    return 0;  
}  