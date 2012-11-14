def mst(a):
    v = range(1,len(a))
    g = [0]
    e = []
    while v:
        l = [a[0][v[0]],0,v[0]]
        for n in g:
            for i in v:
                if a[n][i] < l[0]:
                    l = [a[n][i],n,i]
        e.append(l[1:])
        g.append(l[2])
        v.remove(l[2])
    return e
