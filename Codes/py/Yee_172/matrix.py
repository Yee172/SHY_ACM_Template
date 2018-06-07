#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'

class Matrix():
    mod = 0x3b9aca07

    def __init__(self, n):
        self.n = n
        self.a = [[0] * n for _ in range(n)]

    def __mul__(self, b):
        res = Matrix(self.n)
        for i in range(self.n):
            for j in range(self.n):
                for k in range(self.n):
                    res.a[i][j] += self.a[i][k] * b.a[k][j] % Matrix.mod
                    res.a[i][j] %= Matrix.mod
        return res

    def __pow__(self, e):
        res = Matrix(self.n)
        for i in range(self.n):
            res.a[i][i] = 1
        tmp = self
        while e:
            if e & 1:
                res = res * tmp
            e >>= 1
            tmp = tmp * tmp
        return res

    def __str__(self):
        return str(self.a)
