#!/bin/bash
./serial -n 10000 -c 29 > serial-10000-29.out
./serial -n 15000 -c 29 > serial-15000-29.out
./serial -n 20000 -c 29 > serial-20000-29.out
./serial -n 10000 -c 52 > serial-10000-52.out
./serial -n 15000 -c 52 > serial-15000-52.out
./serial -n 20000 -c 52 > serial-20000-52.out
./serial -n 10000 -c 280 > serial-10000-280.out
./serial -n 15000 -c 280 > serial-15000-280.out
./serial -n 20000 -c 280 > serial-20000-280.out
export OMP_NUM_THREADS=2
./openmp -n 10000 -c 29 > openmp-2-10000-29.out
./openmp -n 15000 -c 29 > openmp-2-15000-29.out
./openmp -n 20000 -c 29 > openmp-2-20000-29.out
./openmp -n 10000 -c 52 > openmp-2-10000-52.out
./openmp -n 15000 -c 52 > openmp-2-15000-52.out
./openmp -n 20000 -c 52 > openmp-2-20000-52.out
./openmp -n 10000 -c 280 > openmp-2-10000-280.out
./openmp -n 15000 -c 280 > openmp-2-15000-280.out
./openmp -n 20000 -c 280 > openmp-2-20000-280.out
export OMP_NUM_THREADS=4
./openmp -n 10000 -c 29 > openmp-4-10000-29.out
./openmp -n 15000 -c 29 > openmp-4-15000-29.out
./openmp -n 20000 -c 29 > openmp-4-20000-29.out
./openmp -n 10000 -c 52 > openmp-4-10000-52.out
./openmp -n 15000 -c 52 > openmp-4-15000-52.out
./openmp -n 20000 -c 52 > openmp-4-20000-52.out
./openmp -n 10000 -c 280 > openmp-4-10000-280.out
./openmp -n 15000 -c 280 > openmp-4-15000-280.out
./openmp -n 20000 -c 280 > openmp-4-20000-280.out
export OMP_NUM_THREADS=8
./openmp -n 10000 -c 29 > openmp-8-10000-29.out
./openmp -n 15000 -c 29 > openmp-8-15000-29.out
./openmp -n 20000 -c 29 > openmp-8-20000-29.out
./openmp -n 10000 -c 52 > openmp-8-10000-52.out
./openmp -n 15000 -c 52 > openmp-8-15000-52.out
./openmp -n 20000 -c 52 > openmp-8-20000-52.out
./openmp -n 10000 -c 280 > openmp-8-10000-280.out
./openmp -n 15000 -c 280 > openmp-8-15000-280.out
./openmp -n 20000 -c 280 > openmp-8-20000-280.out
