#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


inf = 0x3f3f3f3f3f3f3f3f


a = frozenset()


from collections import defaultdict
a = defaultdict(int)


from decimal import *
getcontext().prec = 50
a = Decimal(1)
a = Decimal('0.3')


'''
a -> args
k -> kwargs
rd -> read
gcd -> greatest common divisor
'''
rd = lambda: map(int, input().split())
gcd = lambda a, b: gcd(b, a % b) if b else a
from math import gcd


'''
fpm -> fast_power_mod
b -> base
e -> exponent
m -> module
r -> result
'''
def fpm(b, e, m):
    r = 1
    while e:
        if e & 1: r = r * b % m
        e >>= 1
        b = b * b % m
    return r
fpm = pow
