#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=1:00:00
#SBATCH --mem=32GB

module purge
gcc -O3 -Wall -o dp2 dp2.c
./dp2 300000000 20
./dp2 1000000 1000
