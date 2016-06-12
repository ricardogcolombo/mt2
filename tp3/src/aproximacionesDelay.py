import math
import numpy as np

def prediccionSeno(datosFiles,cantMesesTrain):
    mesesTrain = np.zeros(cantMesesTrain, dtype=np.int)
    x = []
    for i in range(0, cantMesesTrain):
        mesesTrain[i]=datosFiles[i]
        x.append(math.sin(i+1))

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x, np.ones(len(x))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    m, c = np.linalg.lstsq(A, mesesTrain)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return m , c,mesesTrain



def prediccionPolinomio(datosFiles,cantMesesTrain):
    mesesTrain = np.zeros(cantMesesTrain, dtype=np.int)
    x1 = []
    x2 = []
    x3 = []
    for i in range(0, cantMesesTrain):
        mesesTrain[i]=datosFiles[i]
        x1.append(i+1)
        x2.append(math.pow(i+1,2))
        x3.append(math.pow(i+1,3))

    #  aca obtengo una matriz A ( funcion(x), 1)
    A = np.vstack([x1,x2,x3, np.ones(len(x1))]).T
    #  llamo a cuadrados minimos con la matriz A y los meses de datos que yo cnozco
    a,b,c,d = np.linalg.lstsq(A, mesesTrain)[0]
    #  devuelvo los valores que me sirven para mi prediccion
    return a,b,c,d,mesesTrain
