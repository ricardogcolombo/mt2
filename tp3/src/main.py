#!/usr/bin/python
import csv
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt
import math

#  esta funcion obtiene los datos ya filtrados
#  anioInicial es el nombre del archivo +.csv que se agrega en la funcion para obtener los datos
#  cantAnios es la cantidad de archivos + anios que se obtienen
def getDataFromFiles(anioInicial,cantAnios,airport):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        try:
            print "Abriendo base " + str(filename) + ".."
            #  leo archivo, los archivos se nombran por anio.csv
            ifile  = open(str(filename)+".csv", "rb")
            reader = csv.reader(ifile)
        except:
            print "Error abriendo el archivo"


        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            if row[15]!="NA" and row[16]==airport and row[25]!="NA" and int(row[15])>15 and row[16]==airport and int(row[25])>0:
                result.append(list(row))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    print "termino de leer"

    datosFiles= np.zeros((cantAnios+1)*12, dtype=np.int)
    countAnios= 0

    #  tomo el anioo del primer elemento como referencia, estan ordenados por ser una lectura ordenada
    anioActual= int(result[0][0])

    #  voy guardando mes a mes segun el anio para ejecutarlo
    for item in result:
        if anioActual < int(item[0]):
            countAnios+=1
            anioActual = int(item[0])
        datosFiles[int(item[1])+(12*countAnios)-1]+=1

    return datosFiles

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



print "metodos disponibles"
#  agregar numero de metodos aca
print "1 - Hacer prediccion en base a un airopuerto y delays "
metodo = raw_input('cual metodo desea ejecutar? ')

#  aproximaciones
print "aproximar por "
print "1 - Funcion Seno"
aprximacion = raw_input('cual aproximacion desea ejecutar? ')

#  creo el array con todos los meses que voy a graficar
cantAniosArchivos = 4
cantMesesTrain = 24

mesesRestantes =(cantAniosArchivos+1)*12-(cantMesesTrain*12)
anioInicial = 2004
if(cantAniosArchivos+1)*12>cantMesesTrain:
    #  lectura de datos
    datosFiles= getDataFromFiles(anioInicial,cantAniosArchivos,"JFK")
else:
    print "La cantidad de meses para train es menor a los que se obtienen en los archivos"

m,c,mesesTrain = prediccionSeno(datosFiles,cantMesesTrain)

ejeXMeses= []
for i in range(1,(cantAniosArchivos+1)*12+1):
    ejeXMeses.append(i)

plt.plot(ejeXMeses,datosFiles)
for i in range(0,cantMesesTrain):
    plt.plot(i+1,mesesTrain[i],'bs')

for i in range(cantMesesTrain,(cantAniosArchivos+1)*12):
    plt.plot(i+1,m*math.sin(i)+c,'bs')

plt.show()
