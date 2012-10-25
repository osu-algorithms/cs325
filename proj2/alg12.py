#!/usr/bin/python2

def recursive(a):
    if len(a) == 0:
        return 0
    else:
        max_suffix = 0
        suffix_sum = 0
        for i in a:
            suffix_sum += i
            if suffix_sum > max_suffix:
                max_suffix = suffix_sum
        return max(max_suffix,recursive(a[1:]))

def dynamic_programming(a):
    max_subarray = 0
    for i in range(len(a)):
        max_suffix = 0
        suffix_sum = 0
        for j in a[i:]:
            suffix_sum += j
            if suffix_sum > max_suffix:
                max_suffix = suffix_sum
        if max_suffix > max_subarray
            max_subarray = max_suffix
        return max_subarray
