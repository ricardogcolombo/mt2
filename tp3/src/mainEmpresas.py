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
    #  cantEjecuciones=12
    #  if empresa=="Dl":
    cantEjecuciones=35
    #  elif empresa=="AA":
        #  cantEjecuciones=12
    #  creo el array con todos los meses que voy a graficar
    datosFiles= fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,empresa)

    a=0
    a1=0

    sumaErrores=-1
    for n in range(0,cantEjecuciones):
        rd.seed(n)
        #  cantMesesTrain = rd.randint(1,(cantAniosArchivos+1)*12-1)
        #  cantMesesTrain=10
        #  if empresa=="Dl":
        cantMesesTrain =39
        #  elif empresa=="AA":
            #  cantMesesTrain =12
        #  aca es el cross validation obtengo el set de datos
        mesesParaTrain= getTrainSet(datosFiles,cantMesesTrain)
        #  hago cuadrados inimos
        #  a= prediccionSeno(datosFiles,mesesParaTrain)
        #  a= prediccionPolinomio(datosFiles,mesesParaTrain)
        #  a= prediccionPolinomioPar(datosFiles,mesesParaTrain)
        #  if empresa=="AA":
            #  a= prediccionPolinomioSCAA(datosFiles,mesesParaTrain)
        #  elif empresa=="DL":
        a= prediccionPolinomioSCDL(datosFiles,mesesParaTrain)
        #  aca calculo el error
        datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
        error = 0
        for j in range(0,len(datosFiles)):
            if mesesParaTrain[j]==0:
                #  datosObtenidos[j]= getCalculadaSeno(j,a)
                #  datosObtenidos[j]=getCalculadaPolinomioPar(j,a) 
                #  datosObtenidos[j]=getCalculadaPolinomio(j,a) 


                #  if empresa=="AA":
                #  datosObtenidos[j]=getCalculadaPolinomioSCAA(j,a) 
                #  elif empresa=="DL":
                datosObtenidos[j]=getCalculadaPolinomioSCDL(j,a) 

                error += math.pow(datosFiles[j]-datosObtenidos[j],2)

        error=error/cantMesesTrain
        if sumaErrores<0 or error<sumaErrores:
            sumaErrores =error
            a1=a
    
    return a1





anioInicial = 2004
cantAniosArchivos = 4
a = getSolutionEmpresa(anioInicial,cantAniosArchivos-1,"AA")
b = getSolutionEmpresa(anioInicial,cantAniosArchivos-1,"DL")
#  print a
datosAA = fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,"AA")
#  datosTOTALES= fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,"TODOS")
datosDL= fm.getDataEmpresaProcesada(anioInicial,cantAniosArchivos,"DL")
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)


#  #  print "Ahora ploteo"
#  res = []
res2 = []
#  for i in range(0,len(datosAA)):
    #  val = getCalculadaSeno(i,a)
    #  val = getCalculadaPolinomio(i,a)
    #  val = getCalculadaPolinomioPar(i,a)
    #  val = getCalculadaPolinomioSCAA(i,a)
    #  res.append(val)

for i in range(0,len(datosDL)):
    #  val = getCalculadaSeno(i,a)
    #  val = getCalculadaPolinomio(i,a)
    #  val = getCalculadaPolinomioPar(i,a)
    val = getCalculadaPolinomioSCDL(i,b)
    #  print "mes i - " + str(val)

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
#  #  datos len tiene los datos mes a mes
#  plt.subplot(3, 1, 1)
#  lineTOTALES = plt.plot(ejeXMeses,datosTOTALES,"yo")
#  plt.subplot(2, 1, 1)
#  lineAA = plt.plot(ejeXMeses,datosAA,"r")
#  lineAproximacion = plt.plot(ejeXMeses,res,'b')
#  plt.subplot(2, 1, 2)
lineDL = plt.plot(ejeXMeses,datosDL,"g")
lineAproximacion = plt.plot(ejeXMeses,res2,'r')
#  lineAA[0].set_label("Datos Reales de la aerolinea AA")
lineDL[0].set_label("Datos Reales de la aerolinea DL")
lineAproximacion[0].set_label("Aproximacion con una combinacion de senos y polinomio") 
#  plt.legend(handles=[lineAA[0],lineAproximacion[0]])
plt.legend(handles=[lineDL[0],lineAproximacion[0]])
plt.show()
