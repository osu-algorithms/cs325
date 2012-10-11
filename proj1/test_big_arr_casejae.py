#!/usr/bin/python

"""
Because I am lazy. Copy and paste the array you get from 
http://cs325-subarray.herokuapp.com/ into the correct spot in myarr.py,
then run this script.  
"""

import alg1
import alg2
import alg3
import alg4
import myarray_casejae

def main():
    algs = (#alg1.alg1, # Obnoxiously slow for big data 
            alg2.alg2, 
            alg3.max_sub,
            alg4.alg4)
    data = myarray_casejae.arr()
    for a in algs:
        print "algorithm " + str(a) + "says the answer is..."
        print a(data)

if __name__ == "__main__":
    main()
