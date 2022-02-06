#!/bin/bash

for i in {1730803..10000000..50000}
do
    ./remigio 102435 $i >> avl_search.txt 
done
