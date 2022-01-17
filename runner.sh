#!/bin/bash

for n in {1..1000..100}
do
    ./teles $n 3 >> file $n
done        