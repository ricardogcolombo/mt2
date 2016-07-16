import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
import json
from aproximacionesEmpresas  import *

def getSolutionEmpresa(anioInicial,cantAniosArchivos,empresa):
    metodo = 1
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,empresa)
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
        a= prediccionSeno(datosFiles,mesesParaTrain)
        #  aca calculo el error
        datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
        error = 0
        for j in range(0,len(datosFiles)):
            if mesesParaTrain[j]==0:
                datosObtenidos[j]= getCalculadaSeno(j,a)
                error += math.pow(datosFiles[j]-datosObtenidos[j],2)
        #  errores.append([a,error])
        #  errores.append([error])
        #  print error
        error=error/(finMesesTrain-initMesesTrain)
        #  print error
        #  print a
        print a, error
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
#  #  print "Ahora ploteo"
res2 = []
for i in range(0,len(datosDL)):
    val = getCalculadaSeno(i,b[0])

    res2.append(val)

font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 9,
        }

plt.title('Grafico de vuelos que parten desde el aeropuerto JFK de la compania DL (2004-2008)', fontsize=11, ha='center')

plt.xlabel('meses', fontdict=font)
plt.ylabel('Cantidad de vuelos desde JFK', fontdict=font)

#  #  dibujo los datos reales
#  #  datos len tiene los datos mes a mes
#  plt.subplot(3, 1, 1)
#  lineTOTALES = plt.plot(ejeXMeses,datosTOTALES,"yo")
#  plt.subplot(2, 1, 1)
#  lineAA = plt.plot(ejeXMeses,datosAA,"r")
#  lineAproximacion = plt.plot(ejeXMeses,res,'b')
#  plt.subplot(2, 1, 2)
lineDL = plt.plot(ejeXMeses,datosDL,"g")
lineAproximacion = plt.plot(ejeXMeses,res2,'r')
lineDL[0].set_label("Datos Reales de la aerolinea DL")

fig.set_size_inches(8.5, 6.5)

ax.set_xticks(range(len(labels)))
ax.set_xticklabels(labels,rotation='vertical')

lineAproximacion[0].set_label("Aproximacion con una combinacion de senos") 
plt.legend(handles=[lineDL[0],lineAproximacion[0]])
#  plt.show()
plt.savefig('DLCantSeno.png')
