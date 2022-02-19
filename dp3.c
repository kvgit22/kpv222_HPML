//
//  dp3.c
//  HPML_Assignment_1
//
//  Created by Kaushik Pobbi Setty Venkatesh on 2/14/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mkl_cblas.h>

 float bdp(long N, float *pA, float *pB)
 {
    float R = cblas_sdot(N, pA, 1, pB, 1);
    return R;
 }

 int main(int argc, const char * argv[]) {
     
     long arr_size = atol(argv[1]);
     int iter = atoi(argv[2]);
     
     struct timespec start, end;
     
     float *arr_1 = (float*)malloc(arr_size * sizeof(float));
     float *arr_2 = (float*)malloc(arr_size * sizeof(float));
     float *time_per_iter = (float*)malloc(arr_size * sizeof(float));
     
     if((arr_1 != NULL)&&(arr_2 != NULL)&&(time_per_iter != NULL))
     {
         for(long i = (arr_size - 1); i >= 0; i--)
         {
             arr_1[i] = arr_2[i] = 1.0;
         }
         
         float res;
         
         printf("***********************************************************************\n");
         printf("dp3 - Testcases parameters N: %ld, Iter: %d\n",arr_size,iter);
         printf("***********************************************************************\n");
         
         for(int k = 1; k <= iter; k++)
         {
             clock_gettime(CLOCK_MONOTONIC, &start);
             res = bdp(arr_size, arr_1, arr_2);
             clock_gettime(CLOCK_MONOTONIC, &end);
             
             time_per_iter[k] =(((double)end.tv_sec - (float)start.tv_sec)
             + (((double)end.tv_nsec / 1000000000) - ((float)start.tv_nsec / 1000000000)));
             
             double bw_per_iter = (((double)(arr_size * 2 * 4) / (double)(1024 * 1024 * 1024)) / time_per_iter[k]);
             
             double thrpt_per_iter = (arr_size * 2) / (time_per_iter[k] * 1000000000);
             
             // Print following for every iteration
             if(iter > 999)
                 printf("Iteration: %4d ~ ", k);
             else if(iter > 99)
                 printf("Iteration: %3d ~ ", k);
             else
                 printf("Iteration: %2d ~ ", k);
 
             printf("R: %.6f, T: %.6f sec, B: %.3lf GB/sec, F: %.3f GFLOP/sec\n",res, time_per_iter[k], bw_per_iter, thrpt_per_iter);
         }
         
         double time_sum = 0.0;
         for(int m = iter/2; m < iter; m++)
         {
             time_sum += time_per_iter[m];
         }
         
         // Average computation time
         float avg_comp_time = (time_sum / (iter / 2));
         
         // Bandwith calculation
         float bw = ((double)(arr_size * 2 * 4) / (double)(1024 * 1024 * 1024 * avg_comp_time));
         
         // FLOPS
         float prg_thrpt = (arr_size * 2) / (avg_comp_time * 1000000000);
         
         printf("\n");
         printf("Average readings for the second half of iterations\n");
         printf("N: %ld, T: %.6f sec, B: %.3f GB/sec, F: %.3f GFLOP/sec\n",arr_size, avg_comp_time, bw, prg_thrpt);
         printf("\n");
     }
     else
     {
         printf("Can't allocate sufficient dynamic memory");
     }
     
     free(arr_1);
     free(arr_2);
     free(time_per_iter);
     
     return 0;
 }

