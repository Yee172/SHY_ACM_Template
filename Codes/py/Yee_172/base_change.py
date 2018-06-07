#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


'''
cb -> change_10base_to_base
   int -> string
ct -> change_base_to_10base # t for ten
   string -> int
CR -> CHARS
n -> num
s -> string
b -> base
'''
CR = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
def cb(n, b):
    return cb(n // b, b) + CR[n % b] if n else ''
def ct(s, b):
    return sum(CR.index(s[i]) * (b ** (len(s) - i - 1)) for i in range(len(s) - 1, -1, -1))


f = lambda c: ord(c) - 97
g = lambda x: chr(97 + x)
