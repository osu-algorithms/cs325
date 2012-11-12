#!/usr/bin/python2
from math import sqrt

def distance(a):
    d = []
    for i in range(len(a)):
        d.append([])
    for i in range(len(a)):
        x1 = a[i][0]
        y1 = a[i][1]
        #d[i][i] = 0
        for j in range(i+1,len(a)):
            x2 = a[j][0]
            y2 = a[j][1]
            d[j].append(int(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) + 0.5))
            #d[i][j] = d[j][i]
    return d
