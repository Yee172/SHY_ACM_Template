#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


import bisect
bi = bisect.insort
bil = bisect.insort_left
bir = bisect.insort_right
bs = bisect.bisect
bsl = bisect.bisect_left
bsr = bisect.bisect_right


'''
bs -> binary_search
find the index of the left insertion position of the selected value
'''
def bs(a, v):
    l, r = 0, len(a) - 1
    while l < r:
        m = l + (r - l + 1 >> 1)
        t = a[m]
        if t == v:
            return m
        elif t < v:
            l = m
        else:
            r = m - 1
