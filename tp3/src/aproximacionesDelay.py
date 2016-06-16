import math
import numpy as np
import random as rd


def getTrainSet(datos,cantMesesTrain):
    mesesTrain = np.zeros(len(datos), dtype=np.int)
    countMeses = 0
    while countMeses<cantMesesTrain:
        mes = rd.randint(0,len(datos)-1)
        if(not mesesTrain[mes]==1):
            print "mes tomados: "
            print mes
            countMeses+=1
            mesesTrain[mes]=1

    return mesesTrain

def prediccionSeno(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(math.sin(i))
            x1.append(math.cos(i))
            x2.append(math.sin(2*i))
            x3.append(math.sin(3*i))
            x4.append(math.cos(2*i))

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a[0],a[1],a[2],a[3],a[4],a[5]


def prediccionPolinomio(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    x5 = []
    x6 = []
    x7 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(i)
            x1.append(i**2)
            x2.append(i**3)
            x3.append(i**4)
            x4.append(i**5)
            #  x5.append(i**6)
            #  x6.append(i**7)
            #  x7.append(i**8)

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x4,x3,x2,x1,x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    #  print a[0],a[1],a[2],a[3]
    return a[0],a[1],a[2],a[3],a[4],a[5]
