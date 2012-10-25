#!/usr/bin/python

"""
Make up a random array and see whether all 3 algorithms claim the same max 
subarray in it. 
"""

import alg12
import alg3
import random
import sys

def randarray(size, mx):
    ret = []
    for i in range(0,size):
        ret.append(random.randint(-mx, mx))
    return ret

def check(res):
    el = res[0]
    for r in res:
        if r != el:
            return False
    return True

def main():
    argv = sys.argv
    if len(argv) > 2:
        ntests = int(argv[1])
        sz = int(argv[2])
        mx = int(argv[3])
    else:
        ntests = int(raw_input("how many tests? "))
        sz = int(raw_input("array size? "))
        mx = int(raw_input("max absolute value of an array element? "))
    print "Testing with arrays size " + str(sz) + " max val " + str(mx) + " for " + str(ntests) + " tests."
    algs = (alg12.dynamic_programming, alg3.max_sub)
    for i in range(0, ntests):
        arr = randarray(sz, mx)
        results = []
        for a in algs:
            results.append(a(arr))
        if not check(results):
            print "FAILED A TEST"
            print arr
            for a in range(0, len(algs)):
                print "\t" + str(algs[a])
                print "\t" + str(results[a])
                

if __name__ == "__main__":
    main()
