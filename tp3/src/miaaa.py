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
    #  anioInicial = 2004
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataEmpresaProcesadaMIA(anioInicial,cantAniosArchivos,empresa)
    errores = []
    a=0
    a1=0
    k=4

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
        a= prediccionSenoaaMIA(datosFiles,mesesParaTrain)
        #  aca calculo el error
        datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
        error = 0
        for j in range(0,len(datosFiles)):
            if mesesParaTrain[j]==0:
                datosObtenidos[j]= getCalculadaaaMIA(j,a)
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

a = getSolutionEmpresa(anioInicial,cantAniosArchivos-1,"AA")
#  print a
datosAA = fm.getDataEmpresaProcesadaMIA(anioInicial,cantAniosArchivos,"AA")

labels = []
meses = ["Ene","Feb","Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)
    labels.append(meses[i%12])

fig, ax = plt.subplots(1, 1, figsize=(5, 5))
#  #  print "Ahora ploteo"
res = []
for i in range(0,len(datosAA)):
    val = getCalculadaaaMIA(i,a[0])
    res.append(val)


font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 9,
        }

plt.title('Prediccion con funcion que combina senos \n'
             'desde el aeropuerto MIA de la compania AA (2008)', fontsize=11, ha='center')

plt.xlabel('meses', fontdict=font)
plt.ylabel('Cantidad de vuelos desde MIA', fontdict=font)

#  #  dibujo los datos reales
#  #  datos len tiene los datos mes a mes
lineAA = plt.plot(ejeXMeses,datosAA,"r")
lineAproximacion = plt.plot(ejeXMeses,res,'b')
lineAA[0].set_label("Datos Reales de la aerolinea AA")



ax.set_xticks(range(len(labels)))
ax.set_xticklabels(labels,rotation='vertical')
fig.set_size_inches(8.5, 6.5)
lineAproximacion[0].set_label("Aproximacion con una combinacion de cosenos ") 
plt.legend(handles=[lineAA[0],lineAproximacion[0]])


#  plt.show()
plt.savefig('AAMIACantSeno.png')
