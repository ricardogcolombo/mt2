#!/bin/bash

for i in `seq 1 10`;
do
    echo "corriendo test " $i
    ./tp experimentos/plsda/plsda6/test$i.in experimentos/plsda/plsda6/results/test$i.out 0
done
