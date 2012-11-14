from distance import distance, mirror
from mst import mst
from time import time

n = 125
m = []
for i in range(n):
    for j in range(n):
        m.append((i,j))
t = time()
m = distance(m)
print (time() - t)
t = time()
g = mst(m)
l = 0
for e in g:
    l += m[e[0]][e[1]]
print g
print l
print (time() - t)
