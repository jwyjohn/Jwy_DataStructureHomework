#!/bin/bash

g++ run_test.cpp -o run_test.out


for i in $(ls ./test_inputs/*.in) 
do
    echo ======================================
    echo $i
    ./run_test.out < $i
done
rm run_test.out
