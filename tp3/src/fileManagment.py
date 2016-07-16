import csv
import numpy as np
import classEmpresa as emp
from fileManagment import *


def getTrainSet(datos,init,fin):
    mesesTrain = np.zeros(len(datos), dtype=np.int)
    countMeses = 0
    for i in range(init,fin):
        mesesTrain[i]=1

    return mesesTrain



#  esta funcion obtiene los datos ya filtrados
#  anioInicial es el nombre del archivo +.csv que se agrega en la funcion para obtener los datos
#  cantAnios es la cantidad de archivos + anios que se obtienen
def procesarData(anioInicial,cantAnios,airport):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../data/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            if row[15]!="NA" and row[16]==airport and row[25]!="NA" and int(row[15])>15 and row[16]==airport and int(row[25])>0:
                #  if row[16]==airport:
                result.append(list(row))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"

    datosFiles= np.zeros((cantAnios+1)*12, dtype=np.int)
    countAnios= 0
    if(len(result)>0):
        #  tomo el anioo del primer elemento como referencia, estan ordenados por ser una lectura ordenada
        anioActual= int(result[0][0])

        #  voy guardando mes a mes segun el anio para ejecutarlo
        for item in result:
            if anioActual < int(item[0]):
                countAnios+=1
                anioActual = int(item[0])
            datosFiles[int(item[1])+(12*countAnios)-1]+=1
    return datosFiles

def procesarDataEmpresaAirport(anioInicial,cantAnios,empresa,airport):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../data/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        f = open(str(filename)+".csv", "wb")
        writer = csv.writer(f)
        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            if row[15]!="NA" and row[8]!="NA" and row[8]==empresa and row[16]==airport and row[25]!="NA" and int(row[15])>15 and row[16]==airport and int(row[25])>0:
                #  if row[16]==airport:
                result.append(list(row))
                writer.writerow(row)

        #  cierro el archivo
        ifile.close()
        f.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"

    datosFiles= np.zeros((cantAnios+1)*12, dtype=np.int)
    countAnios= 0
    if(len(result)>0):
        #  tomo el anioo del primer elemento como referencia, estan ordenados por ser una lectura ordenada
        anioActual= int(result[0][0])

        #  voy guardando mes a mes segun el anio para ejecutarlo
        for item in result:
            if anioActual < int(item[0]):
                countAnios+=1
                anioActual = int(item[0])
            datosFiles[int(item[1])+(12*countAnios)-1]+=1
    return datosFiles

def getDataDelayProcesadaAirportCompany(anioInicial,cantAnios,company,airport):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../"+airport+"/"+company+"/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        for row in reader:
            result.append(int(row[0]))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"
    countAnios= 0
    #  print result
    return result



def getDataDelayProcesada(anioInicial,cantAnios):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../delay/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        for row in reader:
            result.append(int(row[0]))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"
    countAnios= 0
    #  print result
    return result


def getDataEmpresaProcesada(anioInicial,cantAnios,empresa):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../vuelos/vuelos"+empresa+"/"+str(filename)+"-" +empresa+".csv", "rb")
        reader = csv.reader(ifile)

        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            result.append(int(row[0]))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"
    countAnios= 0
    #  print result
    return result

def getDataEmpresaProcesadaMIA(anioInicial,cantAnios,empresa):
    #  leo el csv
    result= []
    filename = anioInicial
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../MIA/"+empresa+"/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)

        #  ACA SE APLICA EL FILTRO SI SE QUIERE USAR OTRO FILTRO CAMBIAR EL IF DENTRO DEL FOR
        # columna 15 es Delay
        # columna 16 es el nombre del aeropuerto
        # columna 25 es Delay por causas de clima
        #  revisamos que las columnas que necesitamos cumplan:
        #  - delay y weather delay !=NA y delay > 15 minutos ademas que el delayPorClima >0
        #  los que cumplen las condiciones quedan apendeados en results
        for row in reader:
            result.append(list(row))

        #  cierro el archivo
        ifile.close()
        #  aumento el numero de anio para leer el sieguiente archivo
        filename+=1

    #  print "termino de leer"
    datosFiles= np.zeros((cantAnios+1)*12, dtype=np.int)
    countAnios= 0
    if(len(result)>0):
        #  tomo el anioo del primer elemento como referencia, estan ordenados por ser una lectura ordenada
        anioActual= int(result[0][0])

        #  voy guardando mes a mes segun el anio para ejecutarlo
        for item in result:
            if anioActual < int(item[0]):
                countAnios+=1
                anioActual = int(item[0])
            datosFiles[int(item[1])+(12*countAnios)-1]+=1
    return datosFiles

def getDataByEmpresa(anioInicial,empresa,airport):
    result= []
    filename = anioInicial
    ifile  = open("../data/"+str(filename)+".csv", "rb")
    reader = csv.reader(ifile)

    for row in reader:
        if row[8]==empresa and row[16]==airport:
            result.append(list(row))
    ifile.close()

    datosFiles= np.zeros(12, dtype=np.int)
    for item in result:
        datosFiles[int(item[1])-1]+=1

    return datosFiles

def getTotalMarket(anioInicial,cantAnios,nameEmpresa="ALL"):
    empresas = []
    filename = anioInicial

    names = getCarrierNames()
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../data/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)
        #  esto es horrendo
        line = 0
        for row in reader:
            if line != 0:
                isInList = 0
                for empresa in empresas:
                    if empresa.name == row[8]:
                        isInList = 1
                        emp.empresa.addVenta(empresa,row)

                if(not isInList):
                    empresa =emp.empresa()
                    name = row[8]
                    emp.empresa.setName(empresa,name,anioInicial,cantAnios)
                    emp.empresa.addVenta(empresa,row)
                    empresas.append(empresa)
            line+=1
        filename+=1

    return empresas;


def getMarketAAandDL(anioInicial,cantAnios,nameEmpresa="ALL"):
    empresas = []
    filename = anioInicial

    names = getCarrierNames()
    for i in range (0,cantAnios+1):
        #  print "Abriendo base " + str(filename) + ".."
        #  leo archivo, los archivos se nombran por anio.csv
        ifile  = open("../data/"+str(filename)+".csv", "rb")
        reader = csv.reader(ifile)
        #  esto es horrendo
        line = 0
        for row in reader:
            if line != 0:
                isInList = 0
                for empresa in empresas:
                    if "AA"==row[8] or "DL" ==row[8]:
                        if empresa.name == row[8]:
                            isInList = 1
                            emp.empresa.addVenta(empresa,row)

                if(not isInList):
                    empresa =emp.empresa()
                    name = row[8]
                    emp.empresa.setName(empresa,name,anioInicial,cantAnios)
                    emp.empresa.addVenta(empresa,row)
                    empresas.append(empresa)
            line+=1
        filename+=1

    return empresas;
