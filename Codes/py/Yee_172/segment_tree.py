#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'

class SegmentTree():
    """
    zkw segment tree translated by Yee_172 from VinceBlack's magic template
    """
    def __init__(self, n):
        self.d = [0] * (n << 2)
        self.bit = 0

    def build(self, a):
        """
        a : iterator
        """
        self.bit = 1
        while self.bit <= n + 1:
            self.bit <<= 1
        for i in range(self.bit + 1, self.bit + n + 1):
            self.d[i] = next(a)
        for i in range(self.bit - 1, 0, -1):
            self.d[i] = max(self.d[i << 1], self.d[i << 1 | 1])
            self.d[i << 1] -= self.d[i]
            self.d[i << 1 | 1] -= self.d[i]

    def update(self, l, r, val):
        l += self.bit
        r += self.bit
        if (l == r):
            self.d[l] += val
            while l > 1:
                temp = max(self.d[l], self.d[l ^ 1])
                self.d[l] -= temp
                self.d[l ^ 1] -= temp
                self.d[l >> 1] += temp
                l >>= 1
            return
        self.d[l] += val
        self.d[r] += val
        while l ^ r ^ 1:
            if ~ s & 1:
                self.d[l ^ 1] += val
            if t & 1:
                self.d[r ^ 1] += val
            temp = max(self.d[l], self.d[l^1])
            self.d[l] -= temp
            self.d[l ^ 1] -= temp
            self.d[l >> 1] += temp
            temp = max(self.d[r], self.d[r^1])
            self.d[r] -= temp
            self.d[r ^ 1] -= temp
            self.d[r >> 1] += temp
            l >>= 1
            r >>= 1
        while l > 1:
            temp = max(self.d[l], self.d[l ^ 1])
            self.d[l] -= temp
            self.d[l ^ 1] -= temp
            self.d[l >> 1] += temp

    def query(self, l, r):
        lans = 0
        rans = 0
        if l == r:
            l += self.bit
            while l:
                lans += self.d[l]
                l >>= 1
            return lans
        l += self.bit
        r += self.bit
        while l ^ r ^ 1:
            lans += self.d[l]
            rans += self.d[r]
            if ~ l & 1:
                lans = max(lans, self.d[l ^ 1])
            if r & 1:
                rans = max(rans, self.d[r ^ 1])
            l >>= 1
            r >>= 1
        lans += self.d[l]
        rans += self.d[r]
        ans = max(lans, rans)
        while l > 1:
            l >>= 1
            ans += self.d[l]
        return ans


class SegmentTree(object):
    '''
    # https://github.com/leonsim/segmenttree/blob/master/segmenttree/__init__.py
    '''
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.max_value = {}
        self.sum_value = {}
        self.len_value = {}
        self._init(start, end)

    def add(self, start, end, weight=1):
        start = max(start, self.start)
        end = min(end, self.end)
        self._add(start, end, weight, self.start, self.end)
        return True

    def query_max(self, start, end):
        return self._query_max(start, end, self.start, self.end)

    def query_sum(self, start, end):
        return self._query_sum(start, end, self.start, self.end)

    def query_len(self, start, end):
        return self._query_len(start, end, self.start, self.end)

    """"""
    def _init(self, start, end):
        self.max_value[(start, end)] = 0
        self.sum_value[(start, end)] = 0
        self.len_value[(start, end)] = 0
        if start < end:
            mid = start + int((end - start) / 2)
            self._init(start, mid)
            self._init(mid + 1, end)

    def _add(self, start, end, weight, in_start, in_end):
        key = (in_start, in_end)
        if in_start == in_end:
            self.max_value[key] += weight
            self.sum_value[key] += weight
            self.len_value[key] = 1 if self.sum_value[key] > 0 else 0
            return
        mid = in_start + int((in_end - in_start) / 2)
        if mid >= end:
            self._add(start, end, weight, in_start, mid)
        elif mid+1 <= start:
            self._add(start, end, weight, mid + 1, in_end)
        else:
            self._add(start, mid, weight, in_start, mid)
            self._add(mid + 1, end, weight, mid + 1, in_end)
        self.max_value[key] = max(self.max_value[(in_start, mid)], self.max_value[(mid + 1, in_end)])
        self.sum_value[key] = self.sum_value[(in_start, mid)] + self.sum_value[(mid + 1, in_end)]
        self.len_value[key] = self.len_value[(in_start, mid)] + self.len_value[(mid + 1, in_end)]

    def _query_max(self, start, end, in_start, in_end):
        if start == in_start and end == in_end:
            ans = self.max_value[(start, end)]
        else:
            mid = in_start + int((in_end - in_start) / 2)
            if mid >= end:
                ans = self._query_max(start, end, in_start, mid)
            elif mid < start:
                ans = self._query_max(start, end, mid + 1, in_end)
            else:
                ans = max(self._query_max(start, mid, in_start, mid),
                          self._query_max(mid + 1, end, mid + 1, in_end))
        return ans

    def _query_sum(self, start, end, in_start, in_end):
        if start == in_start and end == in_end:
            ans = self.sum_value[(start, end)]
        else:
            mid = in_start + int((in_end - in_start) / 2)
            if mid >= end:
                ans = self._query_sum(start, end, in_start, mid)
            elif mid < start:
                ans = self._query_sum(start, end, mid + 1, in_end)
            else:
                ans = self._query_sum(start, mid, in_start, mid) + self._query_sum(mid + 1, end, mid + 1, in_end)
        return ans

    def _query_len(self, start, end, in_start, in_end):
        if start == in_start and end == in_end:
            ans = self.len_value[(start, end)]
        else:
            mid = in_start + int((in_end - in_start) / 2)
            if mid >= end:
                ans = self._query_len(start, end, in_start, mid)
            elif mid < start:
                ans = self._query_len(start, end, mid+1, in_end)
            else:
                ans = self._query_len(start, mid, in_start, mid) + self._query_len(mid + 1, end, mid + 1, in_end)
        return ans


class Tree(object):
    def __init__(self, l, r):
        self.l = l
        self.r = r
        self.value = 0
        self.left = None
        self.right = None
        if l < r:
            mid = (l + r) // 2
            self.left = Tree(l, mid)
            self.right = Tree(mid + 1, r)
    def set_value(self, p, value):
        if self.l == self.r:
            self.value = value
            return
        mid = (self.l + self.r) // 2
        if p <= mid:
            self.left.set_value(p, value)
        else:
            self.right.set_value(p, value)
        self.push_up()
    def push_up(self):
        self.value = self.left.value + self.right.value
    def query(self, x, y):
        if x <= self.l and y >= self.r:
            return self.value
        if self.l == self.r:
            return self.value
        mid = (self.l + self.r) // 2
        if mid >= y:
            return self.left.query(x, y)
        elif mid < x:
            return self.right.query(x, y)
        else:
            return self.left.query(x, mid) + self.right.query(mid + 1, y)


class FenwickTree(object):
    """Implementation of Fenwick Tree (a.k.a Binary Indexed Tree). [v1.0]
    This implentation uses 0-based indexing.
    """
    def __init__(self, n, lst=None):
        """Initialize Fenwick Tree for n elements. If lst is given, Fenwick
        Tree is initiailzed from the list in O(n) time.
        """
        if not lst:
            self._data = [0] * n
        else:
            self._data = lst
            for i in range(1, n + 1):
                j = i + (i & -i)
                if j <= n:
                    self._data[j - 1] += self._data[i - 1]

    def sum(self, beg, end):
        """Return the sum of elements in range [beg, end)."""
        if beg > 0:
            return self.sum(0, end) - self.sum(0, beg)
        s = 0
        while end > 0:
            s += self._data[end - 1]
            end -= end & -end
        return s

    def add(self, idx, val):
        """Add val to the element at idx."""
        idx += 1
        while idx <= len(self._data):
            self._data[idx - 1] += val
            idx += idx & -idx
