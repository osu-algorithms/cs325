#!/usr/bin/python
import alg1
import alg3
import data #let's be lazy and hard-code the tests for now
import sys
import os
from time import time

def printy(results, tests, n):
	print "The tester ran " + str(n) + " tests per algorithm"
	print "Functions tested were: "
	print tests
	print "Times were: "
	print results

def print2(results, tests, n):
	print "The tester ran " + str(n) + " tests per algorithm on " + str(len(tests)) + " algorithms."
	for i in range(0, len(tests)):
		print "Test " + str(tests[i]) + " took total time " + str(results[i])
		print "\tTime per execution: " + str(results[i]/n)

def main(args, argv):
	num_tests = int(argv[1]) if args > 0 else 1
	tests = (alg1.alg1, alg3.max_sub)
	results = []
	testdata = data.get_data(num_tests)
	for t in tests:
		start = time()
		for d in testdata:
			t(d)
		results.append(time()-start) 
	print2(results, tests, num_tests)		

if __name__ == "__main__":
	exit(main(len(sys.argv), sys.argv))
