#!/bin/bash

for i in `seq 1 30`;
do
    echo "corriendo test " $i
    ./tp experimentos/knn/test$i.in experimentos/knn/results/test$i.out 0
done
