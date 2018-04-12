#!/bin/bash
./serial -n 10000 -c 29

export OMP_NUM_THREADS=8
./openmp -n 10000 -c 29
