#! /usr/bin/env python

from random import randint
import numpy as np


print("GENERANDO CASOS DE TEST...")


k = 30
alfa =10 
gamma = 50
K = 10
totalTest = 4200
for j in range(1,alfa+1):
    fo = open("pca/test"+str(j)+".in", "wb")

    print "Generando archivo " + str(j)
    fo.write("./data/" + " " + str(k) + " " + str(alfa)+ " " + str(j)+ " " + str(K))
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
