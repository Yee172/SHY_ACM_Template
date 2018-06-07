#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


from math import *
def fft(fx, inverse=False):
    n = len(fx)
    if n == 1:
        return [fx[0]]
    fx1 = []
    fx2 = []
    for i in range(0, n, 2):
        fx1.append(fx[i])
        fx2.append(fx[i + 1])
    y1 = fft(fx1, inverse=inverse)
    y2 = fft(fx2, inverse=inverse)
    y = []
    for i in range(n):
        w = cos(2 * i * pi / n) + 1j * sin(2 * i * pi / n)
        if inverse:
            w = 1 / w
        yi = y1[i % (n // 2)] + w * y2[i % (n // 2)]
        y.append(yi)
    return y

def fx_mul(fx1, fx2):
    n = max(len(fx1), len(fx2))
    k = 1
    while n > k:
        k *= 2
    n = 2 * k
    fx1 = fx1 + [0] * (n - len(fx1))
    fx2 = fx2 + [0] * (n - len(fx2))
    y1 = fft(fx1)
    y2 = fft(fx2)
    y = [y1 * y2 for y1, y2 in zip(y1, y2)]
    fx = fft(y, inverse=True)
    l = len(fx)
    fx = [i / l for i in fx]
    return fx
