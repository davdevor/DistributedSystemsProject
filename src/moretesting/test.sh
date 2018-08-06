#!/bin/bash
./serial -n 10000 -c 29 > serial-10000-29.out
./serial -n 15000 -c 29 > serial-15000-29.out
./serial -n 20000 -c 29 > serial-20000-29.out
./serial -n 10000 -c 52 > serial-10000-52.out
./serial -n 15000 -c 52 > serial-15000-52.out
./serial -n 20000 -c 52 > serial-20000-52.out
export OMP_NUM_THREADS=8
./openmp -n 15000 -c 29 > openmp.out
