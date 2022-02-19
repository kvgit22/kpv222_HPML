#
#  dp4.py
#  HPML_Assignment_1
#
#  Created by Kaushik Pobbi Setty Venkatesh on 2/14/22.

import numpy as np
import sys
import time

time_sum = 0.0

def dp(N,A,B):
    R = 0.0
    for j in range(0, N):
        R += A[j] * B[j]
    return R

N = int(sys.argv[1])
iter = int(sys.argv[2])

A = np.ones(N, dtype=np.float32)
B = np.ones(N, dtype=np.float32)

time_per_iter = np.zeros(N, dtype=np.float32)

print("***********************************************************************")
print("dp1 - Testcases parameters N: " + str(N) + " ,Iterations: " + str(iter))
print("***********************************************************************")

for k in range(1, iter+1):
    start = time.monotonic()
    res = dp(N,A,B)
    end = time.monotonic()

    time_per_iter[k] = end - start

    bw_per_iter = ((N * 2 * 4) / (1024 * 1024 * 1024 * time_per_iter[k]))

    thrpt_per_iter = (N * 2) / (time_per_iter[k] * 1000000000);

    print("Iter: {0} ~ R: {1:.2f} ,T: {2:.6f} sec,B: {3:.4f} GB/sec ,F: {4:.4f} GFLOPS/sec".format(k, res, time_per_iter[k], bw_per_iter, thrpt_per_iter))

for i in range(iter//2, iter):
    # global time_sum
    time_sum += time_per_iter[i]

# Average computatio time
avg_comp_time = ((time_sum) / (iter // 2))

if avg_comp_time >= 0:
    # Bandwidth calculation
    bw = ((N * 4 * 2) / (1024 * 1024 * 1024 * avg_comp_time))

    # FLOPS
    prg_thrpt = (N * 2) / (avg_comp_time * 1000000000)
else:
    # Bandwidth calculation
    bw = ((N * 4 * 2) / (1024 * 1024 * 1024 * 0.000000001))

    # FLOPS
    prg_thrpt = (N * 2) / (0.000000001 * 1000000000)

print("\n")
print("Average readings for the second half of iterations")
print("N: {0} ,T: {1:.6f} sec ,B: {2:.4f} GB/sec ,F: {3:.4f} GFLOPS/sec".format(N, avg_comp_time, bw, prg_thrpt))
print("\n")



