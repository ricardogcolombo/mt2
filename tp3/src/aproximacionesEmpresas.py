import math
import numpy as np
import random as rd
from fileManagment import *

#  JFK DL 

def getCalculadaSeno(mes,coef):
    #  return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*(mes)+coef[3]*(mes**2)
    return  coef[0]*math.cos(2*math.pi*mes/36)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*math.sin(2*math.pi*mes/11)+coef[3]

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
            x.append(math.cos(2*math.pi*i/36))
            x1.append(math.cos(2*math.pi*i/6))
            x2.append(math.sin(2*math.pi*i/11))
    #  aca obtengo una matriz A ( funcion(x), 1)
    #  A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    A = np.vstack([x,x1,x2,np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

#  JFK AA
p1 = 36
p2 = 5
p3 =5 
def getCalculadaaa(mes,coef):
    #  return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*(mes)+coef[3]*(mes**2)
    return  coef[0]*math.cos(2*math.pi*mes/p1)+coef[1]*math.cos(2*math.pi*mes/p2)+coef[2]*math.cos(2*math.pi*mes/p3)+coef[3]

def prediccionSenoaa(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(math.cos(2*math.pi*i/p1))
            x1.append(math.cos(2*math.pi*i/p2))
            x2.append(math.cos(2*math.pi*i/p3))
    #  aca obtengo una matriz A ( funcion(x), 1)
    #  A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    A = np.vstack([x,x1,x2,np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

#  MIA AA
miaaap1 = 12
miaaap2 = 6

def getCalculadaaaMIA(mes,coef):
    #  return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*(mes)+coef[3]*(mes**2)
    return  coef[0]*math.cos(2*math.pi*mes/miaaap1)+coef[1]*math.cos(2*math.pi*mes/miaaap2)+coef[2]

def prediccionSenoaaMIA(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(math.cos(2*math.pi*i/miaaap1))
            x1.append(math.cos(2*math.pi*i/miaaap2))
    #  aca obtengo una matriz A ( funcion(x), 1)
    #  A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    A = np.vstack([x,x1,np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

miadlp1 = 3
miadlp2 = 3

#  MIA dl
def getCalculadadlMIA(mes,coef):
    #  return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*(mes)+coef[3]*(mes**2)
    return  coef[0]*math.cos(2*math.pi*mes/miadlp1)+coef[1]*math.cos(2*math.pi*mes/miadlp2)+coef[2]

def prediccionSenodlMIA(datosFiles,mesesParaTrain):
    x = []
    x1 = []
    x2 = []
    x3 = []
    x4 = []
    b= []
    for i in range(0, len(datosFiles)):
        if(mesesParaTrain[i]==1):
            b.append(datosFiles[i])
            x.append(math.cos(2*math.pi*i/miadlp1))
            x1.append(math.cos(2*math.pi*i/miadlp2))
    #  aca obtengo una matriz A ( funcion(x), 1)
    #  A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    A = np.vstack([x,x1,np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a
