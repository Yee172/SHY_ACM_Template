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
