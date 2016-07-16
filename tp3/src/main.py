import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
import json
from sys import argv
import classEmpresa
#  from aproximacionesEmpresas import *
from aproximacionesDelay import *
from fileManagment import *

def getSolution(anioInicial,cantAniosArchivos):
    metodo = 1
    #  cantAniosArchivos =0
    #  cantMesesTrain = 6
    #  anioInicial = 2004
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataDelayProcesada(anioInicial,cantAniosArchivos)
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
        print a,error

        initMesesTrain =(initMesesTrain+k)
        finMesesTrain =(finMesesTrain+k)
        #  corrijo set a agarrar

        if sumaErrores<0 or error<sumaErrores:
            sumaErrores =error
            a1=a

    #  print a1
    return a1,errores

anioInicial = 2004
cantAniosArchivos = 4
labels = []
meses = ["Ene","Feb","Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]

a,errores = getSolution(anioInicial,cantAniosArchivos-1)
#  print a
#  print errores
datosFiles = fm.getDataDelayProcesada(anioInicial,cantAniosArchivos)
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)
    labels.append(meses[i%12])


#  print "Ahora ploteo"
res = []
for i in range(0,len(datosFiles)):
    val = getCalculadaSeno(i,a)
    #  val = getCalculadaPolinomio(i,a)
    #  val = getCalculadaPolinomioPar(i,a)
    #  val = getCalculadaPolinomioSC(i,a)

    res.append(val)


font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 9,
        }

#  ploteo
fig, ax = plt.subplots(1, 1, figsize=(5, 5))

plt.xlim(-0.1, 12*(cantAniosArchivos+1))
# Remove the plot frame lines. They are unnecessary here.
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

fig.set_size_inches(18.5, 10.5)
#  #  dibujo los datos reales
#  #  datos len tiene los datos mes a mes
lineReal = plt.plot(ejeXMeses,datosFiles,"r")
lineReal[0].set_label("Datos Reales")
lineAproximacion = plt.plot(ejeXMeses,res)

# labels ,legend and title
plt.title('Datos Reales demoras por clima (2004-2008)', fontsize=11, ha='center')
plt.xlabel('meses', fontdict=font)
plt.ylabel('Cantidad de Delays', fontdict=font)

lineAproximacion[0].set_label("Aproximacion con una suma de senos ")
plt.legend(handles=[lineReal[0],lineAproximacion[0]])

ax.set_xticks(range(len(labels)))
ax.set_xticklabels(labels,rotation='vertical')

#  save image
plt.savefig('delaySeno.png')
#  plt.sho()
