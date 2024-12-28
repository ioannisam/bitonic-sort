#!/bin/bash
#SBATCH --partitoion=rome
#SBATCH --ntasks-per-node=64
#SBATCH --nodes=1
#SBATCH --time=0:05:00

cd /home/c/ioannisam/

make clean
make

touch test/p6_q21.txt

srun -n 64 ./bin/distributed 21 6 > p6_q21.txt

make clean
