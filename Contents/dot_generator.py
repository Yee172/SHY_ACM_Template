#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/06/12
"""
__author__ = 'Yee_172'


PATH = __import__('sys').path[0]
SOURCE = PATH + '/CONTENTS.txt'
OUTPUT = PATH + '/tmp.dot'
MAX_LENGTH = 0

with open(SOURCE, 'r') as f:
    CONTENT = f.read().strip().replace('\xa0', ' ').replace(r'\ ', ' ').split('\n')

MAX_LENGTH = max(map(len, CONTENT))
for index, each_line in enumerate(CONTENT):
    CONTENT[index] = each_line + ' ' * (MAX_LENGTH - len(each_line))

with open(OUTPUT, 'w') as f:
    f.write('graph{node [shape=box, color=white, fontname="Menlo Regular"]"\n')
    f.write('\n'.join(CONTENT))
    f.write('\n"}\n')
