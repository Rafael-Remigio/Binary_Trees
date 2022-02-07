#!/bin/bash

for i in {4880003..10000000..100000}
do
    ./remigio 102435 $i >> avl_search.txt 
done
