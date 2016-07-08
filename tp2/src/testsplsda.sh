#!/bin/bash

for j in `seq 5 7`;
do
	for i in `seq 1 10`;
	do
	    echo "corriendo test " $i
	    ./tp experimentos/plsda/plsda$j/test$i.in experimentos/plsda/plsda$j/results/test$i.out 0
	done
done
