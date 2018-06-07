#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
@Author    : Yee_172
@Date      : 2018/04/13
'''
__author__ = 'Yee_172'

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

ax = plt.axes()
ax.xaxis.set_major_locator(plt.MultipleLocator(1.0))
ax.yaxis.set_major_locator(plt.MultipleLocator(1.0))
while 1:
    rd = input()
    if rd == '0':
        break
    x1, y1, x2, y2 = map(int, rd.split())
    ax.add_patch(patches.Rectangle((x1, y1), x2 - x1, y2 - y1, fill=False, edgecolor='black'))
plt.plot(np.arange(0, 0))
plt.grid()
plt.grid(color='b', linewidth='0.3' ,linestyle='--')
plt.show()
