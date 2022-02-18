//
//  main.cpp
//  HPML_Assignment_1
//
//  Created by Kaushik Pobbi Setty Venkatesh on 2/13/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Added below line for debugging purposes
// static long float_ops;

float dp(long N, float *pA, float *pB)
{
    float R = 0.0;
    for(long j = 0; j < N; j++)
    {
        R += pA[j] * pB[j];
        // Added below line for debugging purposes
        // float_ops = float_ops + 2;
    }
    return R;
}

int main(int argc, const char * argv[]) {
    
    long arr_size = atol(argv[1]);
    int iter = atoi(argv[2]);
    
    struct timespec start, end;
    double time_per_iter[iter];
    
    float *arr_1 = (float*)malloc(arr_size * sizeof(float));
    float *arr_2 = (float*)malloc(arr_size * sizeof(float));
    
    if((arr_1 != NULL)&&(arr_2 != NULL))
    {
        for(long i = (arr_size - 1); i >= 0; i--)
        {
            arr_1[i] = arr_2[i] = 1.0;
        }
        
        float res;
        
        for(int k = 1; k <= iter; k++)
        {
            clock_gettime(CLOCK_MONOTONIC, &start);
            res = dp(arr_size, arr_1, arr_2);
            clock_gettime(CLOCK_MONOTONIC, &end);
            
            time_per_iter[k] =(((double)end.tv_sec - (float)start.tv_sec)
            + (((double)end.tv_nsec / 1000000000) + ((float)start.tv_nsec / 1000000000)));
            
            double bw_per_iter = (((double)(arr_size * 2 * 4) / (double)(1024 * 1024 * 1024)) / time_per_iter[k]);
            
            float thrpt_per_iter = (arr_size * 2) / (time_per_iter[k] * 1000000000);
            
            // Print following for every iteration
            printf("R: %.6f, T: %.6f sec, B: %.3lf GB/sec, F: %.3f GLOP/sec\n",res, time_per_iter[k], bw_per_iter, thrpt_per_iter);
        }
        
        double time_sum = 0.0;
        for(int m = iter/2; m < iter; m++)
        {
            time_sum += time_per_iter[m];
        }
        
        // Average computation time
        float avg_comp_time = (time_sum / (iter / 2));
        
        // Bandwith calculation
        float bw = (((double)(arr_size * 2 * 4) / (double)(1024 * 1024 * 1024)) / avg_comp_time);
        
        // FLOPS
        // Added below line for debugging purposes
        // printf("\nNumber of floating point operations is %ld",float_ops);
        float prg_thrpt = (arr_size * 2) / (avg_comp_time * 1000000000);
        
        printf("\n\n");
        printf("N: %ld, T: %.6f sec, B: %.3f GB/sec, F: %.3f GFLOP/sec\n",arr_size, avg_comp_time, bw, prg_thrpt);
        
        free(arr_1);
        free(arr_2);
    }
    return 0;
}
