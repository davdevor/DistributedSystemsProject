#!/bin/bash
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=3
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=4
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=6
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=8
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 12
export OMP_NUM_THREADS=3
./openmp -n 12500 -c 12
export OMP_NUM_THREADS=4
./openmp -n 15000 -c 12
export OMP_NUM_THREADS=6
./openmp -n 17500 -c 12
export OMP_NUM_THREADS=8
./openmp -n 20000 -c 12
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=3
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=4
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=6
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=8
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 13
export OMP_NUM_THREADS=3
./openmp -n 12500 -c 13
export OMP_NUM_THREADS=4
./openmp -n 15000 -c 13
export OMP_NUM_THREADS=6
./openmp -n 17500 -c 13
export OMP_NUM_THREADS=8
./openmp -n 20000 -c 13
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=3
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=4
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=6
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=8
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 14
export OMP_NUM_THREADS=3
./openmp -n 12500 -c 14
export OMP_NUM_THREADS=4
./openmp -n 15000 -c 14
export OMP_NUM_THREADS=6
./openmp -n 17500 -c 14
export OMP_NUM_THREADS=8
./openmp -n 20000 -c 14


