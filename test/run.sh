#!/bin/bash

#SBATCH --partition=rome
#SBATCH --ntasks-per-node=128
#SBATCH --nodes=1
#SBATCH --time=4:00:00

cd /home/i/ioannisam/bitonic-sort

module load gcc/9.2.0

make clean
make

rm test/results.txt
touch test/results.txt

for p in {1..7};
do
  echo -e "WHEN p = $p\n\n" >> ./test/results.txt
  for q in {20..27};
  do
    echo -e "q = $q\n" >> ./test/results.txt
    ./bin/serial $q $p >> ./test/results.txt  
  done
done

make clean
