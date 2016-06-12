#!/usr/bin/python
import csv
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math


def getItemsForAirport(anioInicial,cantAnios,airport,mes,cantMesesTrain,mesesTrain):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
	print "Abriendo base " + str(filename) + ".."
	ifile  = open(str(filename)+".csv", "rb")
	reader = csv.reader(ifile)

	for row in reader:
            if row[15]!="NA" and row[16]==airport and row[25]!="NA" and int(row[15])>15 and row[16]==airport and int(row[25])>0:
                result.append(list(row))

	ifile.close()
	filename+=1

    print "termino de leer"
    countAnios= 0
    anioActual= int(result[0][0])
    for item in result:
        if anioActual < int(item[0]):
            countAnios+=1
            anioActual = int(item[0])
        mes[int(item[1])+(12*countAnios)-1]+=1

    x = []
    for i in range(0, cantMesesTrain):
        mesesTrain[i]=mes[i]
        x.append(math.sin(i+1))
        
    A = np.vstack([x, np.ones(len(x))]).T
    m, c = np.linalg.lstsq(A, mesesTrain)[0]
    return m , c

#  print jfkfiltered
#  creo el array con todos los meses que voy a graficar
cantAnios = 1
cantMesesTrain = 12
mesesTrain = np.zeros(cantMesesTrain, dtype=np.int)
mes = np.zeros((cantAnios+1)*12, dtype=np.int)
m,c = getItemsForAirport(2007,1,"JFK",mes,cantMesesTrain,mesesTrain)
ejeXMeses= []
for i in range(1,(cantAnios+1)*12+1):
    ejeXMeses.append(i)

plt.plot(ejeXMeses,mes)
for i in range(0,12):
    plt.plot(i+1,mesesTrain[i],'bs')

for i in range(12,24):
    plt.plot(i+1,m*math.sin(i)+c,'bs')

plt.show()
