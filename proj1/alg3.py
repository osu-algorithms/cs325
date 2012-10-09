#!/usr/bin/python

from sys import argv

def max_prefix(a):
    max = a[0]
    sum = 0
    for i in a:
        sum += i
        if sum > max:
            max = sum
    return max

def max_suffix(a):
    a.reverse()
    max = a[0]
    sum = 0
    for i in a:
        sum += i
        if sum > max:
            max = sum
    return max

def max_sub(a):
    l = len(a)
    if l <= 1:
        if l == 1:
            return a[0]
        else:
            exit(1)
    else:
        b = a[:int(len(a)/2)]
        c = a[int(len(a)/2):]
        first = max_sub(b)
        last = max_sub(c)
        middle = max_suffix(b) + max_prefix(c)
        return max([first, last, middle])

args = map(int,argv[1:])
print max_sub(args)
