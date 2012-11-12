from distance import distance
from time import time

n = 100
m = []
for i in range(n):
    for j in range(n):
        m.append((i,j))
t = time()
distance(m)
print (time() - t)
