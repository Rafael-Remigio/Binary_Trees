#!/bin/bash

for i in {5310003..10000000..100000}
do
    for n in {999990..999999}
    do
        ./remigio $n $i >> leaf_nodes.txt 
    done
done
