import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
import json
from aproximacionesEmpresas  import *

def getSolutionEmpresa(anioInicial,cantAniosArchivos,empresa):
    metodo = 1
    #  cantAniosArchivos =0
    #  cantMesesTrain = 6
    cantEjecuciones=35
    #  anioInicial = 2004
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataEmpresaProcesadaMIA(anioInicial,cantAniosArchivos,empresa)
    errores = []
    a=0
    a1=0
    k=3

    sumaErrores=-1

    #  esto es para parcear grupos
    initMesesTrain = 0
    finMesesTrain =k
    totalMeses = (cantAniosArchivos+1)*12/k
    #  print "total", totalMeses

    for n in range(0,totalMeses):
        rd.seed(n)
        #  aca es el cross validation obtengo el set de datos
        mesesParaTrain= getTrainSet(datosFiles,initMesesTrain,finMesesTrain)
        #  hago cuadrados minimos
        a= prediccionSenodlMIA(datosFiles,mesesParaTrain)
        #  aca calculo el error
        datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
        error = 0
        for j in range(0,len(datosFiles)):
            if mesesParaTrain[j]==0:
                datosObtenidos[j]= getCalculadadlMIA(j,a)
                error += math.pow(datosFiles[j]-datosObtenidos[j],2)
        #  errores.append([a,error])
        #  errores.append([error])
        #  print error
        error=error/(finMesesTrain-initMesesTrain)
        #  print error
        #  print a

        initMesesTrain =(initMesesTrain+k)
        finMesesTrain =(finMesesTrain+k)
        #  corrijo set a agarrar

        if sumaErrores<0 or error<sumaErrores:
            sumaErrores =error
            a1=a

    #  print a1
    return a1,errores




anioInicial = 2005
cantAniosArchivos = 3

b = getSolutionEmpresa(anioInicial,cantAniosArchivos-1,"DL")
#  print a
datosDL= fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,"DL")


labels = []
meses = ["Ene","Feb","Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)
    labels.append(meses[i%12])


fig, ax = plt.subplots(1, 1, figsize=(5, 5))
res2 = []
print b
for i in range(0,len(datosDL)):
    val = getCalculadadlMIA(i,b[0])

    res2.append(val)

font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 9,
        }

plt.title('Prediccion con funcion que combina senos y polinomios para la cantidad\n'
             'de vuelos que parten desde el aeropuerto JFK de la compania DL (2008)', fontsize=11, ha='center')

plt.xlabel('meses', fontdict=font)
plt.ylabel('Cantidad de vuelos desde JFK', fontdict=font)

#  #  dibujo los datos reales

lineDL = plt.plot(ejeXMeses,datosDL,"g")
lineAproximacion = plt.plot(ejeXMeses,res2,'r')
#  lineAA[0].set_label("Datos Reales de la aerolinea AA")
lineDL[0].set_label("Datos Reales de la aerolinea DL")
ax.set_xticks(range(len(labels)))
ax.set_xticklabels(labels,rotation='vertical')
fig.set_size_inches(8.5, 6.5)
#  plt.legend(handles=[lineAA[0],lineAproximacion[0]])
#  plt.legend(handles=[lineDL[0],lineAproximacion[0]])
#  plt.show()
plt.savefig('MIADLCantSeno.png')
