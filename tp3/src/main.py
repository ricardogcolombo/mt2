import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
import json
from aproximacionesDelay import *

def getSolution(anioInicial,cantAniosArchivos):
    metodo = 1
    #  cantAniosArchivos =0
    #  cantMesesTrain = 6
    #  anioInicial = 2004
    cantEjecuciones =100
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataDelayProcesada(anioInicial,cantAniosArchivos)

    a=0
    a1=0

    sumaErrores=-1
    for n in range(0,cantEjecuciones):
        rd.seed(n)
        #  cantMesesTrain = rd.randint(1,(cantAniosArchivos+1)*12-1)
        cantMesesTrain =36
        #  aca es el cross validation obtengo el set de datos
        mesesParaTrain= getTrainSet(datosFiles,cantMesesTrain)
        #  hago cuadrados minimos
        #  a= prediccionSeno(datosFiles,mesesParaTrain)
        a= prediccionPolinomio(datosFiles,mesesParaTrain)
        #  a= prediccionPolinomioPar(datosFiles,mesesParaTrain)
        #  a= prediccionPolinomioSC(datosFiles,mesesParaTrain)
        #  aca calculo el error
        datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
        error = 0
        for j in range(0,len(datosFiles)):
            if mesesParaTrain[j]==0:
                #  datosObtenidos[j]= getCalculadaSeno(j,a)
                #  datosObtenidos[j]=getCalculadaPolinomioPar(j,a) 
                datosObtenidos[j]=getCalculadaPolinomio(j,a) 
                #  datosObtenidos[j]=getCalculadaPolinomioSC(j,a) 
                error += math.pow(datosFiles[j]-datosObtenidos[j],2)

        error=error/cantMesesTrain
        if sumaErrores<0 or error<sumaErrores:
            #  sumaErrores =error
            a1=a
    
    return a1



anioInicial = 2004
cantAniosArchivos = 4
a = getSolution(anioInicial,cantAniosArchivos)
print a
datosFiles = fm.getDataDelayProcesada(anioInicial,cantAniosArchivos)
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)



#  #  dibujo los datos reales
#  #  datos len tiene los datos mes a mes
plt.plot(ejeXMeses,datosFiles,"r")
#  print "Ahora ploteo"
res = []
for i in range(0,len(datosFiles)):
    #  plt.plot(i, getCalculadaSeno(i,a),'bs')
    #  res.append(getCalculadaSeno(i,a))
    res.append(getCalculadaPolinomio(i,a))
    #  res.append(getCalculadaPolinomioPar(i,a))
    #  res.append(getCalculadaPolinomioSC(i,a))
    #  plt.plot(i,getCalculadaPolinomio(i,a) ,"d")


font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 9,
        }
plt.title('Desempeno en el training con polinomio de grado 5 de Delays por mes de vuelos (2004-2008)\n', fontsize=11, ha='center')
plt.xlabel('meses', fontdict=font)
plt.ylabel('Cantidad de Delays', fontdict=font)
plt.plot(ejeXMeses,res)

plt.show()
