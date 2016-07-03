#! /usr/bin/env python

from random import randint
import numpy as np


print("GENERANDO CASOS DE TEST...")
fo = open("test3.in", "wb")


k = 10
alfa = 10
gamma = 10
K = 10
totalTest = 7000
fo.write("./data/" + " " + str(k)+ " " + str(alfa)+ " " + str(gamma)+ " " + str(K))
fo.write("\n")
for i in range(0,K):
    actual = 0
    salida =np.ones((42000,), dtype=np.int)
    print salida
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
