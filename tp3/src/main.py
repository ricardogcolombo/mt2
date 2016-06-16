import fileManagment as fm
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math
from aproximacionesDelay import *

#  def getSolution():
metodo = 1
cantAniosArchivos =3
#  cantMesesTrain = 6
anioInicial = 2004
cantEjecuciones =6
#  creo el array con todos los meses que voy a graficar
datosFiles= fm.getDataFromFiles(anioInicial,cantAniosArchivos,"JFK")

a=0
b=0
c=0
d=0
e=0
f=0

a1=0
b1=0
c1=0
d1=0
e1=0
f1=0


sumaErrores=-1
for n in range(0,cantEjecuciones):
    rd.seed(n)
    #  cantMesesTrain = rd.randint(1,(cantAniosArchivos+1)*12-1)
    cantMesesTrain = 24
    #  aca es el cross validation obtengo el set de datos
    mesesParaTrain= getTrainSet(datosFiles,cantMesesTrain)
    #  hago cuadrados minimos
    #  a,b,c,d,e,f= prediccionSeno(datosFiles,mesesParaTrain)
    a,b,c,d,e,f= prediccionPolinomio(datosFiles,mesesParaTrain)
    #  aca calculo el error
    datosObtenidos= np.zeros(len(datosFiles), dtype=np.int)
    error = 0
    for j in range(0,len(datosFiles)):
        if mesesParaTrain[j]==0:
            #  datosObtenidos[j]= a*math.sin(j)+ b*math.cos(j)+ c*math.sin(2*j)+ d*math.sin(3*j)+ e*math.cos(2*j)+f
            datosObtenidos[j]= a*(j**5)+b*(j**4)+c*(j**3)+d*(j**2)+e*j+f

            error += math.pow(datosFiles[j]-datosObtenidos[j],2)
   
    error=error/cantMesesTrain
    if sumaErrores<0 or error<sumaErrores:
        #  sumaErrores =error
        a1=a
        b1=b
        c1=c
        d1=d
        e1=e
        f1=f
     
ejeXMeses= []
for i in range(0,(cantAniosArchivos+1)*12):
    ejeXMeses.append(i)
    #  return ejeXMeses,datosFiles,a1,b1,d1,c1,d1,e1,f1


#  dibujo los datos reales
#  datos len tiene los datos mes a mes
plt.plot(ejeXMeses,datosFiles)
print "Ahora ploteo"
for i in range(0,len(datosFiles)):
    #  plt.plot(i, a1*math.sin(i)+ b1*math.cos(i)+ c1*math.sin(2*i)+ d1*math.sin(3*i)+ e1*math.cos(2*i)+f1,'d')
    plt.plot(i,a1*(i**5)+b1*(i**4)+c1*(i**3)+d1*(i**2)+e1*i+f1 ,"d")

plt.show()
