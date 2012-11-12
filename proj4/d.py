from distance import distance
from time import time

n = 90
m = []
for i in range(n):
    for j in range(n):
        m.append((i,j))
t = time()
distance(m)
#for i in distance(m):
#    print i
print (time() - t)

