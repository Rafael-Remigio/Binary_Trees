#!/bin/bash

for i in {3..10000000..10000}
do
    for n in {999990..999999}
    do
        ./remigio $n $i >> leaf_nodes.txt 
    done
done        
