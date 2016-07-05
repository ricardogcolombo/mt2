#! /usr/bin/env python

from random import randint
import numpy as np


print("GENERANDO CASOS DE TEST...")


alfa = 10
gamma = 10
K = 5
totalTest = 4200

for n in range(4,15):
	for j in range(1,alfa+1):
	    fo = open("pca"+str(n)+"/test"+str(j)+".in", "wb")

	    print "Generando archivo " + str(j)
	    fo.write("./data/" + " " + str(n) + " " + str(j)+ " " + str(gamma)+ " " + str(K))
	    fo.write("\n")
	    for i in range(0,K):
		actual = 0
		salida =np.ones((42000,), dtype=np.int)
		while actual<totalTest :
		    pos = randint(0,41999)
		    if(salida[pos]==1):
			salida[pos]=0
			actual+=1

		for i in range(0,42000):
		    if(i==41999):
			fo.write(str(salida[i]))
		    else:
			fo.write(str(salida[i])+ " ")

		fo.write("\n")
	    fo.close()
