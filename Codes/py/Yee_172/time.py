#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


'''
Timer for testing
'''
import contextlib
import datetime as dt
@contextlib.contextmanager
def timer():
    start = dt.datetime.now()
    yield
    end = dt.datetime.now()
    print(end - start)
'''
usage:
with timer():
    pass
'''


import time 
def cal_time(func):
    def wrapper(*args, **kwargs):
        t1 = time.time()
        result = func(*args, **kwargs)
        t2 = time.time()
        print("running time:", func.__name__, t2 - t1)
        return result
    return wrapper
'''
usage:
@cal_time
pass
'''
