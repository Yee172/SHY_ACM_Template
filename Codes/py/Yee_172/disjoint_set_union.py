#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


class DSet:
    def __init__(self, n):
        self.parents = [-1 for i in range(n)]
        self.rank = [0 for i in range(n)]

    def find(self, n):
        if self.parents[n] is -1:
            return n
        ret = self.find(self.parents[n])
        self.parents[n] = ret
        return ret

    def union(self, a, b):
        if a is -1 or b is -1:
            return False
        x, y = self.find(a), self.find(b)
        if self.find(a) == self.find(b) and x is not -1:
            return False
        if self.rank[x] == self.rank[y]:
            self.parents[x] = y
            self.rank[x] = self.rank[y] = self.rank[x] + 1
        elif self.rank[x] > self.rank[y]:
            self.parents[y] = x
            self.rank[y] = self.rank[x]
        else:
            self.parents[x] = y
            self.rank[x] = self.rank[y]
        return True


uf = [i for i in range(len(s))]

def find(uf, i):
    p = uf[i]
    return p if i == p else find(uf, p)

def union(uf, i, j):
    uf[find(uf, i)] = find(uf, j)
