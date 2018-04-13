#!/bin/bash
./serial -n 15000 -c 29 < serial.out

export OMP_NUM_THREADS=8
./openmp -n 15000 -c 29 < openmp.out
