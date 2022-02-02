#!/bin/bash

for i in {3..10000..100}
do
    for n in {999000..999999}
    do
        ./remigio $n $i >> file 
    done
done        