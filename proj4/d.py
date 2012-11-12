from distance import distance, mirror
from time import time

n = 125
m = []
for i in range(n):
    for j in range(n):
        m.append((i,j))
t = time()
mirror(distance(m))
#for i in mirror(distance(m)):
#    print i
print (time() - t)

