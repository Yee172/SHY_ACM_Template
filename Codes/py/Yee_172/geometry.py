#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


from math import *
class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __add__(self, pt):
        return Point(self.x + pt.x, self.y + pt.y)
    def __iadd__(self, pt):
        return self + pt
    def __mul__(self, n):
        return Point(self.x * n, self.y * n)
    def __imul__(self, n):
        return self * n
    def __truediv__(self, n):
        return Point(self.x / n, self.y / n)
    def __itruediv__(self, n):
        return self / n
    def __str__(self):
        return '%f %f' % (self.x, self.y)
    def distance(self, pt):
        return sqrt((self.x - pt.x) ** 2 + (self.y - pt.y) ** 2)
    def angle(self, pt):
        det_x = pt.x - self.x
        det_y = pt.y - self.y
        if det_x == 0:
            if det_y > 0:
                return pi / 2
            if det_y < 0:
                return pi / 2 * 3
            if det_y == 0:
                raise Exception('Fail to find angle between two identical points.')
        if det_x > 0:
            return atan(det_y / det_x)
        if det_x < 0:
            return atan(det_y / det_x) + pi
    def get_pt_by_dis_ang(self, dis, ang):
        return Point(self.x + cos(ang) * dis, self.y + sin(ang) * dis)

class Convex_polygon():
    def __init__(self):
        self.points = []
        self.core = None
        self.dis = None
        self.base_ang = 0
        self.ang = None
        self.area = None
        self.pin = [0, 1]
    def add(self, pt):
        self.points.append(pt)
    def update(self):
        self.update_core()
        self.update_dis()
        self.update_ang()
    def get_double_area(self, i, j, k):
        s = (self.points[j].x - self.points[i].x) * (self.points[k].y - self.points[i].y)
        s -= (self.points[j].y - self.points[i].y) * (self.points[k].x - self.points[i].x)
        return s
    def cal_core_of_triangle(self, i, j, k):
        s = self.get_double_area(i, j, k)
        return s, (self.points[i] + self.points[j] + self.points[k]) / 3 * s
    def update_core(self):
        self.core = Point(0, 0)
        s = 0
        for i in range(2, len(self.points)):
            det_s, det_core = self.cal_core_of_triangle(0, i, i - 1)
            self.core += det_core
            s += det_s
        self.core /= s
        self.area = abs(s) / 2
    def update_dis(self):
        self.dis = []
        for pt in self.points:
            self.dis.append(self.core.distance(pt))
    def update_ang(self):
        self.ang = []
        for pt in self.points:
            self.ang.append(self.core.angle(pt))
    def get_pt(self, i):
        return self.core.get_pt_by_dis_ang(self.dis[i], self.base_ang + self.ang[i])
    def __str__(self):
        return '\n'.join(('points: ' + '[' + ', '.join(str(pt) for pt in self.points) + ']',
                          'core: ' + str(self.core),
                          'dis: ' + str(self.dis),
                          'base_ang ' + str(self.base_ang),
                          'ang ' + str(self.ang),
                          'area ' + str(self.area),
                          'pin ' + str(self.pin)))


class vector:
    def __init__(self, _x = 0, _y = 0):
        self.x = _x
        self.y = _y
    def len(self):
        return sqrt(self.x ** 2 + self.y ** 2)
    def len_sq(self):
        return self.x ** 2 + self.y ** 2
    def __mul__(self, other):
        if (type(self) == type(other)):
            return self.x * other.x + self.y * other.y
        return vector(self.x * other, self.y * other)
    def __mod__(self, other):
        return self.x * other.y - self.y * other.x
    def normed(self):
        length = self.len()
        return vector(self.x / length, self.y / length)
    def normate(self):
        self = self.normed()
    def __str__(self):
        return "(" + str(self.x) + ", " + str(self.y) + ")"
    def __add__(self, other):
        return vector(self.x + other.x, self.y + other.y);
    def __sub__(self, other):
        return vector(self.x - other.x, self.y - other.y);
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    def rot(self):
        return vector(self.y, -self.x)

class line:
    def __init__(self, a = 0, b = 0, c = 0):
        self.a = a
        self.b = b
        self.c = c
    def intersect(self, other):
        d = self.a * other.b - self.b * other.a
        dx = self.c * other.b - self.b * other.c
        dy = self.a * other.c - self.c * other.a
        return vector(dx / d, dy / d)
    def fake(self, other):
        d = self.a * other.b - self.b * other.a
        return d
    def __str__(self):
        return str(self.a) + "*x + " + str(self.b) + "*y = " + str(self.c)

def line_pt(A, B):
    d = (A - B).rot()
    return line(d.x, d.y, d * A)

class circle:
    def __init__(self, O = vector(0, 0), r = 0):
        self.O = O
        self.r = r
    def intersect(self, other):
        O1 = self.O
        O2 = other.O
        r1 = self.r
        r2 = other.r
        if (O1 == O2):
            return []
        if ((O1 - O2).len_sq() > r1 ** 2 + r2 ** 2 + 2 * r1 * r2):
            return []
        rad_line = line(2 * (O2.x - O1.x), 2 * (O2.y - O1.y), r1 ** 2 - O1.len_sq() - r2 ** 2 + O2.len_sq())
        central = line_pt(O1, O2)
        M = rad_line.intersect(central)
        # print(M)
        if ((O1 - O2).len_sq() == r1 ** 2 + r2 ** 2 + 2 * r1 * r2):
            return [M]
        d = (O2 - O1).normed().rot()
        if (r1 ** 2 - (O1 - M).len_sq() < 0):
            return []
        d = d * (sqrt(r1 ** 2 - (O1 - M).len_sq()))
        return [M + d, M - d]
    def fake(self, other):
        O1 = self.O
        O2 = other.O
        r1 = self.r
        r2 = other.r
        if (O1 == O2):
            return 1
        if ((O1 - O2).len_sq() > r1 ** 2 + r2 ** 2 + 2 * r1 * r2):
            return 1
        rad_line = line(2 * (O2.x - O1.x), 2 * (O2.y - O1.y), r1 ** 2 - O1.len_sq() - r2 ** 2 + O2.len_sq())
        central = line_pt(O1, O2)
        return rad_line.fake(central)
