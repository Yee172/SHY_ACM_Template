#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


import sys


rl = lambda l: tuple(map(int, l.split()))
readin = list(map(rl, __import__('sys').stdin.readlines()))


for line in __import__('sys').stdin:
    pass


rd = lambda: next(__import__('sys').stdin, '').strip()


__import__('sys').setrecursionlimit(10 ** 6)


if locals()['__file__'][-2:] == 'py': __import__('sys').stdin = open('in.txt', 'r')
