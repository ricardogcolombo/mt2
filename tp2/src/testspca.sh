#!/bin/bash

for i in `seq 1 10`;
do
    echo "corriendo test " $i
    ./tp experimentos/pca/test$i.in experimentos/pca/results/test$i.out 0
done
