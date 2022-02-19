#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=2:00:00
#SBATCH --mem=32GB
#SBATCH --job-name=HpmlAssignment1
#SBATCH --output=HpmlAssignment1_kpv222.out
#SBATCH --mail-type=END
#SBATCH --mail-user=kpv222@nyu.edu

module purge
gcc -O3 -Wall -o dp1 dp1.c
./dp1 300000000 20
./dp1 1000000 1000
gcc -O3 -Wall -o dp2 dp2.c
./dp2 300000000 20
./dp2 1000000 1000
module load python/intel/3.8.6
g++ -O3 -Wall -I /share/apps/intel/19.1.2/mkl/include/ -L /share/apps/intel/19.1.2/mkl/lib/intel64/ -o dp3 dp3.c -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm
./dp2 300000000 20
./dp3 1000000 1000
python dp4.py 300000000 20
python dp3.py 1000000 1000
python dp5.py 300000000 20
python dp5/py 1000000 1000
