#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=1:00:00
#SBATCH --mem=32GB

module purge
gcc -O3 -Wall -o dp1 dp1.c
./dp1 300000000 20
./dp1 1000000 1000
