#include <bits/stdc++.h>
using namespace std;
typedef long double db;
const db eps = 1e-12;

struct Point {
    db x, y;

    Point() {}

    Point(db _x, db _y) : x(_x), y(_y) {}

    Point operator+(const Point &t) const
    {
        return Point(x + t.x, y + t.y);
    }

    Point operator-(const Point &t) const
    {
        return Point(x - t.x, y - t.y);
    }

    Point operator*(const db &t) const
    {
        return Point(x * t, y * t);
    }

    Point operator/(const db &t) const
    {
        return Point(x / t, y / t);
    }

    bool operator<(const Point &t) const
    {
        return fabs(x - t.x) < eps ? y < t.y : x < t.x;
    }

    bool operator==(const Point &t) const
    {
        return fabs(x - t.x) < eps && fabs(y - t.y) < eps;
    }

    db len() const
    {
        return sqrt(x * x + y * y);
    }

    Point rot90() const
    {
        return Point(-y, x);
    }
};

struct Circle {
    Point o;
    db r;

    Circle() {}

    Circle(Point _o, db _r) : o(_o), r(_r) {}

    friend vector<Point> operator&(const Circle &c1, const Circle &c2) {
        db d = (c1.o - c2.o).len();
        if (d > c1.r + c2.r + eps || d < fabs(c1.r - c2.r) - eps)
            return vector<Point>();
        db dt = (c1.r * c1.r - c2.r * c2.r) / d, d1 = (d + dt) / 2;
        Point dir = (c2.o - c1.o) / d, pcrs = c1.o + dir * d1;
        dt = sqrt(max(0.0L, c1.r * c1.r - d1 * d1)), dir = dir.rot90();
        return vector<Point>{pcrs + dir * dt, pcrs - dir * dt};
    }
};

namespace geometry
{
    typedef long double db;
    inline int sign(const db x) { return x < -eps ? -1 : x > eps; }
    struct Point
    {
        db x,y;
        Point() { x = y = 0; }
        Point(db a,db b) : x(a), y(b) {}
        inline Point operator - (const Point &b) const
        { return Point(x - b.x, y - b.y); }
        inline Point operator + (const Point &b) const
        { return Point(x + b.x, y + b.y); }
        inline Point operator * (const db &b) const
        { return Point(x * b, y * b); }
        inline db dot(const Point &b) const
        { return x * b.x + y * b.y; }
        inline db cross(const Point &b,const Point &c) const
        { return (b.x - x) * (c.y - y) - (c.x - x) * (b.y - y); }
        inline db distance(const Point &b) const
        { return sqrt((*this - b).dot(*this - b)); }
        inline bool in_line(const Point &b, const Point &c) const
        { return !sign(cross(b,c)); }
        inline bool on_seg(const Point &b, const Point &c) const
        { return in_line(b, c) && (*this - c).dot(*this - b) < eps; }
    };

    typedef vector<Point> vp;

    inline db min(db a, db b)
    { return a < b ? a : b; }
    inline db max(db a, db b)
    { return a > b ? a : b; }
    inline db square(db x)
    { return x * x; }
    inline db square(const Point &p)
    { return p.dot(p); }
    Point line_cross(const Point &a, const Point &b, const Point &c, const Point &d)
    {
        db u = a.cross(b, c);
        db v = b.cross(a, d);
        return Point((c.x * v + d.x * u) / (u + v), (c.y * v + d.y * u) / (u + v));
    }

    db line_cross_circle(const Point &a, const Point &b, const Point &r, db R, Point &p1, Point &p2)
    {
        Point fp = line_cross(r, Point(r.x + a.y - b.y, r.y + b.x - a.x), a, b);
        db rtol = r.distance(fp);
        db rtos = fp.on_seg(a, b) ? rtol : min(r.distance(a) , r.distance(b));
        db atob = a.distance(b);
        db fptoe = sqrt(R * R - rtol * rtol) / atob;
        if( rtos > R - eps ) return rtos;
        p1 = fp + (a - b) * fptoe;
        p2 = fp + (b - a) * fptoe;
        return rtos;
    }

    db sector_area(const Point &r, const Point &a, const Point &b, db R)
    {
        db A2 = square(r - a);
        db B2 = square(r - b);
        db C2 = square(a - b);
        return square(R) * acos((A2 + B2 - C2) * 0.5 / sqrt(A2) / sqrt(B2)) * 0.5;
    }

    db TACIA(const Point &r, const Point &a, const Point &b, db R)
    {
        db adis = r.distance(a);
        db bdis = r.distance(b);
        if (adis < R + eps && bdis < R + eps) return r.cross(a , b) * 0.5;
        Point ta, tb;
        if (r.in_line(a, b)) return 0.0;
        db rtos = line_cross_circle(a, b, r, R, ta, tb);
        if (rtos > R - eps) return sector_area(r, a, b, R);
        if (adis < R + eps) return r.cross(a, tb) * 0.5 + sector_area(r, tb, b, R);
        if (bdis < R + eps) return r.cross(ta, b) * 0.5 + sector_area(r, a, ta, R);
        return r.cross(ta, tb) * 0.5 + sector_area(r, tb, b, R) + sector_area(r, a, ta, R);
    }

    vp p;

    db SPICA(int n, Point r, db R){
        int i;
        db ret = 0 , if_clock_t;
        for (i = 0 ; i < n ; i++)
        {
            if_clock_t = sign(r.cross(p[i], p[(i + 1) % n]));
            if (if_clock_t < 0) ret -= TACIA(r, p[(i + 1) % n], p[i], R);
            else ret += TACIA(r, p[i], p[(i + 1) % n], R);
        }
        return fabs(ret);
    }
}
