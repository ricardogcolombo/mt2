import math
import numpy as np
import random as rd


def getTrainSet(datos,cantMesesTrain):
    mesesTrain = np.zeros(len(datos), dtype=np.int)
    rd.seed(rd.randint(0,99999))
    countMeses = 0
    while countMeses<cantMesesTrain:
        mes = rd.randint(0,len(datos)-1)
        if(not mesesTrain[mes]==1):
            countMeses+=1
            mesesTrain[mes]=1

    return mesesTrain

def getCalculadaSeno(mes,coef):
    return   coef[0]*((math.sin(mes)*math.cos(mes))**4)+coef[1]*mes+coef[2]

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
            x.append(i)
            x1.append((math.sin(i)*math.cos(i))**2)
            #  x2.append(math.sin(2*i))
            #  x3.append(math.sin(3*i))
            #  x4.append(math.cos(2*i))

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x1,x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

def getCalculadaPolinomio(mes,coef):
    return  coef[0]*(mes**5)+coef[1]*(mes**4)+coef[2]*(mes**3)+coef[3]*(mes**2)+coef[4]*mes+coef[5]

def prediccionPolinomio(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
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
    return a

def getCalculadaPolinomioPar(mes,coef):
    return  coef[0]*(mes**6)+coef[1]*(mes**5)+coef[2]*(mes**4)+coef[3]*(mes**3)+coef[4]*(mes**2)+coef[5]*mes+coef[6]

def prediccionPolinomioPar(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    x5 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(i)
            x1.append(i**2)
            x2.append(i**3)
            x3.append(i**4)
            x4.append(i**5)
            x5.append(i**6)
            #  x6.append(i**7)
            #  x7.append(i**8)

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x5,x4,x3,x2,x1,x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

def getCalculadaPolinomioSCAA(mes,coef):
    return  coef[0]*(math.sin(mes)**5)+coef[1]*(math.sin(mes**2)**4)+coef[2]*(math.sin(mes**2)**3)+coef[3]*(math.sin(mes**2)**2)+coef[4]*mes+coef[5]

def prediccionPolinomioSCAA(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(i)
            x1.append(math.sin(i**2)**2)
            x2.append(math.sin(i**2)**3)
            x3.append(math.sin(i**2)**4)
            x4.append(math.sin(i**2)**5)

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x4,x3,x2,x1,x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a


def getCalculadaPolinomioSCDL(mes,coef):
    return  coef[0]*(math.atan(mes**6)**4)+coef[1]*(math.sin(mes**8))+coef[2]*(math.sin(mes)**2)+coef[3]*(mes)+coef[4]


def prediccionPolinomioSCDL(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(i)
            x1.append(math.sin(i)**2)
            x2.append(math.sin(i**8))
            x3.append(math.atan(i**6)**4)

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x3,x2,x1,x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

