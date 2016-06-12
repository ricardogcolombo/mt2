import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
from aproximacionesDelay import *

metodo = 1
aproximacion = 2
cantAniosArchivos =0
cantMesesTrain = 6
anioInicial = 2008

#  creo el array con todos los meses que voy a graficar
mesesRestantes =(cantAniosArchivos+1)*12-(cantMesesTrain)
if(cantAniosArchivos+1)*12>=cantMesesTrain:
    #  lectura de datos
    datosFiles= fm.getDataFromFiles(anioInicial,cantAniosArchivos,"JFK")
else:
    print "La cantidad de meses para train es mayora los que se obtienen en los archivos"

m,c,mesesTrain = prediccionSeno(datosFiles,cantMesesTrain)
#  a,b,c,d,mesesTrain = prediccionPolinomio(datosFiles,cantMesesTrain)

print "cant Datos" +  str(len(datosFiles))
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)

plt.plot(ejeXMeses,datosFiles)
for i in range(0,cantMesesTrain):
    plt.plot(i,mesesTrain[i],'bs')

for i in range(cantMesesTrain,(cantAniosArchivos+1)*12):
    plt.plot(i,m*math.sin(i)+c,'bs')
    #  t = a*math.pow(i,3)+b*math.pow(i,2)+c*i+d
    #  print t
    #  plt.plot(i,t,'bs')

plt.show()
