#this is Kadane's algorithm (http://en.wikipedia.org/wiki/Maximum_subarray_problem)
#it solves the problem in linear time and returns the indices of the solution

     
     
def alg4(x):
  if not x : return
  max_sum = x[0]
  current_sum = 0
  start = end = tmp_start=0
  for indx, i in enumerate(x):
      current_sum += i
      if current_sum > max_sum :
           max_sum = current_sum
           end = indx
           start = tmp_start
      if current_sum < 0 :
           current_sum = 0
           tmp_start = indx
     
      if max_sum < 0 :
           start = end
     
  return max_sum,start,end 



def main():
    t1 = [22, -27, 38, -34, 49, 40, 13, -44, -13, 28, 46, 7, -26, 42, 29, 0, -6, 35, 23, -37, 10, 12, -2, 18, -12, -49, -10, 37, -5, 17, 6, -11, -22, -17, -50, -40, 44, 14, -41, 19, -15, 45, -23, 48, -1, -39, -46, 15, 3, -32, -29, -48, -19, 27, -33, -8, 11, 21, -43, 24, 5, 34, -36, -9, 16, -31, -7, -24, -47, -14, -16, -18, 39, -30, 33, -45, -38, 41, -3, 4, -25, 20, -35, 32, 26, 47, 2, -4, 8, 9, 31, -28, 36, 1, -21, 30, 43, 25, -20, 42]
    print alg4(t1)

if __name__ == "__main__":
    main()
