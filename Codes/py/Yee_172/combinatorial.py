#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


'''
sti -> a linear function to generate stirling numbers of the second kind

Stirling(n, m)
&= \frac{1}{m!} \sum_{k = 0}^{m} (-1)^{k} \binom{m}{k} (m - k)^{n}
&= \sum_{k = 0}^{m} \frac{(-1)^{k} (m - k)^{n}}{(m - k)! k!}
'''
M = 0x3b9aca07
MAXN = 200005
modinv = [0, 1]
for i in range(2, MAXN):
    modinv.append((M - M // i) * modinv[M % i] % M)
fa_inv = [1]
for i in range(1, MAXN):
    fa_inv.append(fa_inv[-1] * modinv[i] % M)
def sti(n, m):
    r = 0
    f = [1, -1]
    if n >= m:
        for i in range(m + 1):
            r = (r + f[i & 1] * fa_inv[m - i] * fa_inv[i] * pow(m - i, n, M)) % M
    return r
