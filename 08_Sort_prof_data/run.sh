#!/bin/bash

list="heap_sort bubble_sort selection_sort insertion_sort binary_insertion_sort shell_sort quick_sort bucket_sort merge_sort lsd_radix_sort msd_radix_sort"


for s in $list
do
    cat run_test.txt | sed "s|SED_HERE|$s|g" > tmp.cpp
    g++ tmp.cpp -o tmp.out
    {
        for i in $(ls ./test_inputs/*.in) 
        do
            echo CASE $i
            ./tmp.out < $i
        done
    } > result_$s.txt
    echo DONE $s !
    rm tmp.out tmp.cpp
done