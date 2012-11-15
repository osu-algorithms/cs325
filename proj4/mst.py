def mst(a):
    v = set(range(1,len(a)))
    g = set([0])
    e = set([])
    while v:
        w = v.pop()
        v.add(w)
        l = (a[0][w],0,w)
        for n in g:
            for i in v:
                if a[n][i] < l[0]:
                    l = (a[n][i],n,i)
        e.add((l[1],l[2]))
        g.add(l[2])
        v.remove(l[2])
    return e

