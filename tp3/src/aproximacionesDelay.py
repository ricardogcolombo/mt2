import math
import numpy as np
import random as rd

def getCalculadaSeno(mes,coef):
    #  return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*(mes)+coef[3]*(mes**2)
    return  coef[0]*math.sin(2*math.pi*mes/12)+coef[1]*math.cos(2*math.pi*mes/6)+coef[2]*math.sin(2*math.pi*mes/8)+coef[3]

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
            x.append(math.sin(2*math.pi*i/12))
            x1.append(math.cos(2*math.pi*i/6))
            x2.append(math.sin(2*math.pi*i/8))
    #  aca obtengo una matriz A ( funcion(x), 1)
    #  A = np.vstack([x,x1,x2,x3,x4, np.ones(len(x))]).T
    A = np.vstack([x,x1,x2,np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a= np.linalg.lstsq(A, b)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a

