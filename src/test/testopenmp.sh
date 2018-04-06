#!/bin/bash
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 12 -g 821
export OMP_NUM_THREADS=3
./openmp -n 10000 -c 12 -g 821
export OMP_NUM_THREADS=4
./openmp -n 10000 -c 12 -g 821
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 12 -g 821
export OMP_NUM_THREADS=3
./openmp -n 15000 -c 12 -g 821
export OMP_NUM_THREADS=4
./openmp -n 20000 -c 12 -g 821
