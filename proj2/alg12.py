#!/usr/bin/python2

def dynamic_programming(a):
    max_subarray = 0
    max_suffix = 0
    for i in a:
        max_suffix = max(0,max_suffix+i)
        max_subarray = max(max_subarray, max_suffix)
    return max_subarray
