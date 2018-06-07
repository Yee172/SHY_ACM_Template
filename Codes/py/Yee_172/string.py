#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@Author    : Yee_172
@Date      : 2018/05/28
"""
__author__ = 'Yee_172'


'''
copied from
https://zhuanlan.zhihu.com/p/36892462
haven't tested
'''
class KMP:
    def getnext(self,needle):
        needleLen=len(needle)
        next=[-1]*needleLen
        i,k=0,-1
        while i<needleLen-1:
            if k==-1 or needle[i]==needle[k]:
                i += 1
                k += 1
                if needle[i]==needle[k]:
                    next[i]=next[k]
                else:
                    next[I]=k
            else:
                k=next[k]

        return next

    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        if len(needle)<1:
            return 0
        if len(haystack)<1:
            return -1

        needleLen = len(needle)
        haystackLen=len(haystack)
        next=self.getnext(needle)
        i,j=0,0
        while i<haystackLen and j<needleLen:
            if j==-1 or haystack[i]==needle[j]:
                I+=1
                j+=1
            else:
                j=next[j]

        if j==needleLen:
            return i-j
        return -1

def ConsecutiveLCS(self,s1,s2):
    s1Len=len(s1)
    s2Len=len(s2)
    arr=[[0]*(s2Len+1) for i in range(s1Len+1)]

    res=0
    for i in range(1,s1Len+1):
        for j in  range(1,s2Len+1):
            if s1[i-1]==s2[j-1]:
                arr[i][j]=arr[i-1][j-1]+1
                if res<arr[i][j]:
                    res=arr[i][j]
            else:
                arr[i][j]=0

    return res

def LCS(self,s1,s2):
    s1Len=len(s1)
    s2Len=len(s2)
    arr=[[0]*(s2Len+1) for i in range(s1Len+1)]

    for i in range(1,s1Len+1):
        for j in  range(1,s2Len+1):
            if s1[i-1]==s2[j-1]:
                arr[i][j]=arr[i-1][j-1]+1
            else:
                arr[i][j]=max(arr[i-1][j],arr[i][j-1])

    return arr[s1Len][s2Len]

def EditDistance(self,s1,s2):
    s1Len=len(s1)
    s2Len=len(s2)
    arr=[[0]*(s2Len+1) for i in range(s1Len+1)]

    for i in range(s1Len+1):
        arr[i][0]=i
    for i in range(s2Len+1):
        arr[0][i]=i
    for i in range(1,s1Len+1):
        for j in  range(1,s2Len+1):
            tmp=1
            if s1[i-1]==s2[j-1]:
                tmp=0
            arr[i][j]=min([arr[i][j-1]+1,arr[i-1][j]+1,arr[i-1][j-1]+tmp])
    return arr[s1Len][s2Len]
