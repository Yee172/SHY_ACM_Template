#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


M = mod = 1000000007
mod2inv = 500000004


'''
The way to get a series of inverse numbers under module begin with 1
'''
n = 100005
M = 1000000007
inv = [0, 1] + [0] * (n - 1)
for i in range(2, n + 1):
    inv[i] = (mod - mod // i) * inv[mod % i] % mod


'''
Two ways to get single inverse number without generating a table
'''
inv = lambda x: pow(x, M - 2, M)
inv = lambda x: (M - M // x) * inv(M % x) % M if x - 1 else 1


'''
gfp -> generate_first_factor
l -> left  -> lower
r -> right -> upper
n -> num
'''
def gff(l, r):
    if r < l: return -1
    if l is 2: return 2
    l = l + 1 if l & 1 is 0 else l
    for n in range(l, r + 1, 2):
        for i in range(3, int(n ** 0.5), 2):
            if n % i is 0: break
        else: return n
    return -1


'''
gf -> generate_factors
gff -> generate_factors_fully
'''
def gf(n):
    d = 2
    while d * d <= n:
        f = 1
        while n % d is 0:
            if f:
                yield d
            f = 0
            n //= d
        d += 1
    if n > 1:
        yield n


def gff(n):
    d = 2
    while d * d <= n:
        while n % d is 0:
            yield d
            n //= d
        d += 1
    if n > 1:
        yield n


'''
ip -> is_prime
'''
def ip(n):
    if n in [2, 3]:
        return 1
    if n % 6 not in [1, 5]:
        return 0
    i = 5
    while i * i <= n:
        if not min(n % i, n % (i + 2)):
            return 0
        i += 6
    return 1


'''
npp -> number++
a -> number in array form
'''
number = [0] * 100
def npp(a):
    # if a[-1]: return
    a[0] += 1
    i = 0
    while a[i] > 9:
        a[i] = 0
        i += 1
        a[i] += 1
