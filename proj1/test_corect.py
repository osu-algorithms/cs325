#!/usr/bin/python
import alg1
import alg2
import alg3
import data #let's be lazy and hard-code the tests for now
import sys
import os
from time import time

def print2(results, tests, n):
    print "The tester ran " + str(n) + " tests per algorithm on " + str(len(tests)) + " algorithms."
    for i in range(0, len(tests)):
        print "Test " + str(tests[i]) + "\n\tTotal time: " + str(results[i])
        print "\tTime per execution: " + str(results[i]/n)

def main(args, argv):
    algs = (alg1.alg1, alg2.alg2, alg3.max_sub)
    results = []
    fails = 0
    tests, answers = data.get_with_answers()
    for t in range(0, len(tests)):
        for a in algs:
            alg_ans = a(tests[t])
            if answers[t] != alg_ans:
                print "FAILURE!"
                print "\t" + str(a)
                print "\tsaid " + str(alg_ans) + " when correct was " + str(answers[t])
                fails += 1
    print "Done with tests. " + str(fails) + " failures."
if __name__ == "__main__":
    exit(main(len(sys.argv), sys.argv))
