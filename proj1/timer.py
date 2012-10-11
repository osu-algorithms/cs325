#!/usr/bin/python
import alg1
import alg2
import alg3
import test_consistent as tc
import sys
import os
from time import time

def print2(results, tests, n):
    print "The tester ran " + str(n) + " tests per algorithm on " + str(len(tests)) + " algorithms."
    for i in range(0, len(tests)):
        print "Test " + str(tests[i]) + "\n\tTotal time: " + str(results[i])
        print "\tTime per execution: " + str(results[i]/n)

def duration(alg, testdata):
    start = time()
    alg(testdata)
    return time() - start

def avg(alg, sz, num_tests):
    sm = 0 # sum
    for t in range(0, num_tests):
        sm += duration(alg, tc.randarray(sz, 300)) # randarray(size, max_abs_val_of_element)
    return sm/num_tests

def main(args, argv):
    algs = (alg1.alg1, alg2.alg2, alg3.max_sub)
    sizes = (100,  200,  300,  400,  500,  600,  700,  800,  900,
             1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000)
    print "ALGORITHM 1 TESTS:"
    for i in range(0,9):
        print "\tSize: " + str(sizes[i]) + "\tAvg. Time: " + str(avg(algs[0], sizes[i], 10))
    print "\nALGORITHM 2 TESTS:"
    for i in range(0, len(sizes)):
        print "\tSize: " + str(sizes[i]) + "\tAvg. Time: " + str(avg(algs[1], sizes[i], 10))
    print "\nALGORITHM 3 TESTS:"
    for i in range(0, len(sizes)):
        print "\tSize: " + str(sizes[i]) + "\tAvg. Time: " + str(avg(algs[2], sizes[i], 10))


if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
